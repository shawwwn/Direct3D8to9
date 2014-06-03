#include "PostProcessHDR.h"

namespace PP {
	PostProcessHDR::PostProcessHDR() {}
	PostProcessHDR::~PostProcessHDR() {}
	HRESULT PostProcessHDR::initPermanentResources(IDirect3DDevice9* pDevice, UINT width, UINT height)
	{
		m_pDevice = pDevice;

		HRESULT hr;
		hr = D3DXCreateEffectFromResource(pDevice, GetCurrentModule(), "PP_ColorToneMap.fx", NULL, NULL, 0, NULL, &m_pEffect, NULL);
		if(FAILED(hr))
			return hr;
		
		m_hTPostProcess = m_pEffect->GetTechniqueByName("PostProcess");
		m_hTexScene = m_pEffect->GetParameterByName(NULL, "g_txSceneColor");
		m_hTexSource = m_pEffect->GetParameterByName(NULL, "g_txSrcColor");

		return D3D_OK;
	}
	HRESULT PostProcessHDR::setupTexture(IDirect3DDevice9* pDevice, UINT width, UINT height)
	{
		return D3D_OK;
	}
	HRESULT PostProcessHDR::releaseTemporaryResources()
	{
		SAFE_RELEASE(m_pVertDeclPP);
		SAFE_RELEASE(m_pVB);
		return D3D_OK;
	}

	#pragma region Standard Procedure Functions
	HRESULT PostProcessHDR::Render(IDirect3DTexture9* pSrcColorTexture, IDirect3DSurface9* pDstSurface)
	{
		//	Set Vertex Decl & Set Stream Source
		m_pDevice->SetVertexDeclaration(m_pVertDeclPP);	// Set the vertex declaration
		m_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(PPVERT));

		//if(SUCCEEDED(m_pDevice->BeginScene()))
		{
			if (CTRL::g_EnableHDR)
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
			}
			else
			{
				IDirect3DSurface9* tSrcSurface = NULL;
				pSrcColorTexture->GetSurfaceLevel(0, &tSrcSurface);
				m_pDevice->StretchRect(tSrcSurface, NULL, pDstSurface, NULL, D3DTEXF_NONE);
				SAFE_RELEASE(tSrcSurface);
			}
			//m_pDevice->EndScene(); // End the scene
			return D3D_OK;
		}
		return D3DERR_INVALIDCALL;
	}
	void PostProcessHDR::onCreateDevice(IDirect3DDevice9* pd3dDevice, UINT width, UINT height)
	{
		initPermanentResources(pd3dDevice, width, height);
		initTemporaryResources(pd3dDevice, width, height);
	}
	void PostProcessHDR::onLostDevice()
	{
		m_pEffect->OnLostDevice();
		releaseTemporaryResources();
	}
	void PostProcessHDR::onResetDevice(IDirect3DDevice9* pd3dDevice, UINT width, UINT height)
	{
		m_pEffect->OnResetDevice();
		initTemporaryResources(pd3dDevice, width, height);
	}
	void PostProcessHDR::onDestroy(IDirect3DDevice9* pd3dDevice)
	{
		releasePermanentResources();
		releaseTemporaryResources();
	}
	#pragma endregion
}