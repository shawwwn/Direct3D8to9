//========================================
//
//	Base class of post process
//	
//========================================

#include "PostProcess.h"

namespace PP {
	// Vertex declaration for post-processing
	const D3DVERTEXELEMENT9 PPVERT::PPDecl[4] = {
		{ 0, 0,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 },
		{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  0 },
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  1 },
		D3DDECL_END()
	};

	// struct definition
	PostProcess::PostProcess()
	{
		m_pDevice=NULL;
		m_pEffect=NULL;
		m_hTexSource=NULL;
		m_hTexScene=NULL;
		m_pVB=NULL;
		m_pVertDeclPP=NULL;
	}
	PostProcess::~PostProcess() {}

	/**
	*	Initialize permanent D3D resources
	*	(Resources that persist even after device has been lost)
	*/
	HRESULT PostProcess::initPermanentResources(IDirect3DDevice9* pDevice, UINT resourceRef, UINT width, UINT height)
	{
		m_pDevice = pDevice;

		HRESULT hr;
		hr = D3DXCreateEffectFromResource(pDevice, GetCurrentModule(), MAKEINTRESOURCE(resourceRef), NULL, NULL, 0, NULL, &m_pEffect, NULL);
		if(FAILED(hr))
			return hr;
		
		// Get the PostProcess technique handle
		m_hTPostProcess = m_pEffect->GetTechniqueByName("TechniqueName");

		// Obtain the handles to all texture objects in the effect
		m_hTexScene = m_pEffect->GetParameterByName(NULL, "ParameterName1");
		m_hTexSource = m_pEffect->GetParameterByName(NULL, "ParameterName2");

		return D3D_OK;
	}

	/**
	*	Initialize temporary D3D resources
	*	(Resources that need to be re-created after device has been lost)
	*/
	HRESULT PostProcess::initTemporaryResources(IDirect3DDevice9* pDevice, UINT width, UINT height)
	{
		m_deviceWidth = width;
		m_deviceHeight = height;

		HRESULT hr;
		if(FAILED(hr = pDevice->CreateVertexDeclaration(PPVERT::PPDecl, &m_pVertDeclPP)))
		{
			MessageBox(NULL, "Create Vertex Declaration Fail!", "Error", MB_OK);
			return hr;
		}

		// Set up our quad
		PPVERT Quad[4] =
		{
			{ -0.5f,				-0.5f,				1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f },
			{ m_deviceWidth-0.5f,	-0.5f,				1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f },
			{ -0.5f,				m_deviceHeight-0.5f,1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f },
			{ m_deviceWidth-0.5f,	m_deviceHeight-0.5f,1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }
		};

		// Create a vertex buffer out of the quad
		hr = pDevice->CreateVertexBuffer(sizeof(PPVERT)*4, D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, 0, D3DPOOL_DEFAULT, &m_pVB, NULL);
		if(FAILED(hr))
			return hr;

		// Fill the vertex buffer
		LPVOID pVBData;
		if(SUCCEEDED(m_pVB->Lock(0, 0, &pVBData, D3DLOCK_DISCARD)))
		{
			CopyMemory(pVBData, Quad, sizeof(Quad));
			m_pVB->Unlock();
		}
		else
			return D3DERR_INVALIDCALL;
		return D3D_OK;
	}

	/**
	*	Release/Destroy temporary D3D resources
	*/
	HRESULT PostProcess::releaseTemporaryResources()
	{
		SAFE_RELEASE(m_pVertDeclPP);
		SAFE_RELEASE(m_pVB);
		return D3D_OK;
	}

	/**
	*	Release/Destroy permanent D3D resources
	*/
	HRESULT PostProcess::releasePermanentResources()
	{
		SAFE_RELEASE(m_pEffect);
		return D3D_OK;
	}

	#pragma region Standard Procedure Functions
	HRESULT PostProcess::Render(IDirect3DTexture9* pSrcColorTexture, IDirect3DSurface9* pDstSurface)
	{
		//	Set Vertex Decl & Set Stream Source
		m_pDevice->SetVertexDeclaration(m_pVertDeclPP);	// Set the vertex declaration
		m_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(PPVERT));

		if(SUCCEEDED(m_pDevice->BeginScene()))
		{
			// Set Technique
			m_pEffect->SetTechnique(m_hTPostProcess);
			// Draw the quad
			UINT cPasses, p;
			m_pEffect->Begin(&cPasses, 0);
			m_pEffect->SetTexture(m_hTexScene, pSrcColorTexture); 
			m_pEffect->SetTexture(m_hTexSource, pSrcColorTexture);
			m_pEffect->CommitChanges();
			// Clear the previous screen
			m_pDevice->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0L);
			// Render
			for(p = 0; p < cPasses; ++p)
			{
				m_pEffect->BeginPass(p);
				m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
				m_pEffect->EndPass();
			}
			m_pEffect->End();
			m_pDevice->EndScene(); // End the scene
			return D3D_OK;
		}
		return D3DERR_INVALIDCALL;
	}
	void PostProcess::onCreateDevice(IDirect3DDevice9* pd3dDevice, UINT width, UINT height)
	{
		initPermanentResources(pd3dDevice, SHADER_SAMPLE_H, width, height);
		initTemporaryResources(pd3dDevice, width, height);
	}
	void PostProcess::onLostDevice()
	{
		releaseTemporaryResources();
		m_pEffect->OnLostDevice();
	}
	void PostProcess::onResetDevice(IDirect3DDevice9* pd3dDevice, UINT width, UINT height)
	{
		initTemporaryResources(pd3dDevice, width, height);
		m_pEffect->OnResetDevice();
	}
	void PostProcess::onDestroy(IDirect3DDevice9* pd3dDevice)
	{
		releasePermanentResources();
		releaseTemporaryResources();
	}
	#pragma endregion
}