//========================================
//
//	Base class of post process
//	
//========================================

#include "PostProcess.h"

namespace PP {
	// struct definition
	PostProcess::PostProcess()
	{
		m_pDevice=NULL;
		m_pEffect=NULL;
		m_hTexSource=NULL;
		m_hTexScene=NULL;
	}
	PostProcess::~PostProcess() {}
	HRESULT PostProcess::Init(IDirect3DDevice9* pDevice, UINT resourceRef)
	{
		m_pDevice = pDevice;
		HRESULT hr;
		hr = D3DXCreateEffectFromResource(m_pDevice, GetCurrentModule(), MAKEINTRESOURCE(resourceRef), 
											NULL, NULL, 0, NULL, &m_pEffect, NULL);
		if(FAILED(hr))
			return hr;
		
		// Get the PostProcess technique handle
		m_hTPostProcess = m_pEffect->GetTechniqueByName("TechniqueName");

		// Obtain the handles to all texture objects in the effect
		m_hTexScene = m_pEffect->GetParameterByName(NULL, "ParameterName1");
		m_hTexSource = m_pEffect->GetParameterByName(NULL, "ParameterName2");

		return D3D_OK;
	}
	HRESULT PostProcess::Cleanup()
	{
		m_pEffect->Release();
		return D3D_OK;
	}


	#pragma region Standard Procedure Functions
	HRESULT PostProcess::Render(IDirect3DTexture9* pSrcColorTexture)
	{
		if(SUCCEEDED(m_pDevice->BeginScene()))
		{
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
	void PostProcess::onCreateDevice(IDirect3DDevice9* pd3dDevice)
	{
		Init(pd3dDevice, SHADER_SAMPLE_H);
	}
	void PostProcess::onLostDevice()
	{
		m_pEffect->OnLostDevice();
	}
	void PostProcess::onResetDevice(IDirect3DDevice9* pd3dDevice)
	{
		m_pEffect->OnResetDevice();
	}
	void PostProcess::onDestroy(IDirect3DDevice9* pd3dDevice)
	{
		Cleanup();
	}
	#pragma endregion
}