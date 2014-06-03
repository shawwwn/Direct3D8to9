#include "PostProcessBloom.h"

namespace PP {
	PostProcessBloom::PostProcessBloom() {}
	PostProcessBloom::~PostProcessBloom() {}
	HRESULT PostProcessBloom::initPermanentResources(IDirect3DDevice9* pDevice, UINT width, UINT height)
	{
		m_pDevice = pDevice;

		HRESULT hr;
		HMODULE currentModule = GetCurrentModule();
		// main shader - combine 2x
		hr = D3DXCreateEffectFromResource(pDevice, currentModule, "PP_ColorCombine2.fx", NULL, NULL, 0, NULL, &m_pEffect, NULL);
		if(FAILED(hr))
			return hr;
		m_hTPostProcess = m_pEffect->GetTechniqueByName("PostProcess");
		m_hTexScene = m_pEffect->GetParameterByName(NULL, "g_txSceneColor");
		m_hTexSource = m_pEffect->GetParameterByName(NULL, "g_txSrcColor");

		// 1st shader - bright pass
		hr = D3DXCreateEffectFromResource(pDevice, currentModule, "PP_ColorBrightPass.fx", NULL, NULL, 0, NULL, &m_pEffectBrightPass, NULL);
		m_hTPostProcessBP = m_pEffectBrightPass->GetTechniqueByName("PostProcess");
		m_hTexSourceBP = m_pEffectBrightPass->GetParameterByName(NULL, "g_txSrcColor");

		// 2nd shader - down size 2x
		hr = D3DXCreateEffectFromResource(pDevice, currentModule, "PP_ColorDownFilter2.fx", NULL, NULL, 0, NULL, &m_pEffectDownSize2x, NULL);
		m_hTPostProcessD2 = m_pEffectDownSize2x->GetTechniqueByName("PostProcess");
		m_hTexSourceD2 = m_pEffectDownSize2x->GetParameterByName(NULL, "g_txSrcColor");

		// 3rd shader - down size 4x
		hr = D3DXCreateEffectFromResource(pDevice, currentModule, "PP_ColorDownFilter4.fx", NULL, NULL, 0, NULL, &m_pEffectDownSize4x, NULL);
		m_hTPostProcessD4 = m_pEffectDownSize4x->GetTechniqueByName("PostProcess");
		m_hTexSourceD4 = m_pEffectDownSize4x->GetParameterByName(NULL, "g_txSrcColor");

		// 4th shader - bloom horizontal
		hr = D3DXCreateEffectFromResource(pDevice, currentModule, "PP_ColorBloomH.fx", NULL, NULL, 0, NULL, &m_pEffectBloomH, NULL);
		m_hTPostProcessBH = m_pEffectBloomH->GetTechniqueByName("PostProcess");
		m_hTexSourceBH = m_pEffectBloomH->GetParameterByName(NULL, "g_txSrcColor");

		// 5th shader - bloom vertical
		hr = D3DXCreateEffectFromResource(pDevice, currentModule, "PP_ColorBloomV.fx", NULL, NULL, 0, NULL, &m_pEffectBloomV, NULL);
		m_hTPostProcessBV = m_pEffectBloomV->GetTechniqueByName("PostProcess");
		m_hTexSourceBV = m_pEffectBloomV->GetParameterByName(NULL, "g_txSrcColor");

		// 6th shader - gaussian blur horizontal
		hr = D3DXCreateEffectFromResource(pDevice, currentModule, "PP_ColorGBlurH.fx", NULL, NULL, 0, NULL, &m_pEffectGBlurH, NULL);
		m_hTPostProcessGBH = m_pEffectGBlurH->GetTechniqueByName("PostProcess");
		m_hTexSourceGBH = m_pEffectGBlurH->GetParameterByName(NULL, "g_txSrcColor");

		// 7th shader - gaussian blur vertical
		hr = D3DXCreateEffectFromResource(pDevice, currentModule, "PP_ColorGBlurV.fx", NULL, NULL, 0, NULL, &m_pEffectGBlurV, NULL);
		m_hTPostProcessGBV = m_pEffectGBlurV->GetTechniqueByName("PostProcess");
		m_hTexSourceGBV = m_pEffectGBlurV->GetParameterByName(NULL, "g_txSrcColor");
		return D3D_OK;
	}
	HRESULT PostProcessBloom::setupTexture(IDirect3DDevice9* pDevice, UINT width, UINT height)
	{
		setupShader(m_pEffectBrightPass);
		setupShader(m_pEffectDownSize2x);
		setupShader(m_pEffectDownSize4x);
		setupShader(m_pEffectBloomH);
		setupShader(m_pEffectBloomV);
		setupShader(m_pEffectGBlurH);
		setupShader(m_pEffectGBlurV);

		pDevice->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pBrightPassTexture, NULL);
		m_pBrightPassTexture->GetSurfaceLevel(0, &m_pBrightPassSurface);
		pDevice->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pDownsize2xTexture, NULL);
		m_pDownsize2xTexture->GetSurfaceLevel(0, &m_pDownsize2xSurface);
		pDevice->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pDownsize4xTexture, NULL);
		m_pDownsize4xTexture->GetSurfaceLevel(0, &m_pDownsize4xSurface);
		pDevice->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pBloomHTexture, NULL);
		m_pBloomHTexture->GetSurfaceLevel(0, &m_pBloomHSurface);
		pDevice->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pBloomVTexture, NULL);
		m_pBloomVTexture->GetSurfaceLevel(0, &m_pBloomVSurface);
		return D3D_OK;
	}
	HRESULT PostProcessBloom::releaseTemporaryResources()
	{
		SAFE_RELEASE(m_pVertDeclPP);
		SAFE_RELEASE(m_pVB);

		SAFE_RELEASE(m_pBrightPassTexture);
		SAFE_RELEASE(m_pBrightPassSurface);
		SAFE_RELEASE(m_pDownsize2xTexture);
		SAFE_RELEASE(m_pDownsize2xSurface);
		SAFE_RELEASE(m_pDownsize4xTexture);
		SAFE_RELEASE(m_pDownsize4xSurface);
		SAFE_RELEASE(m_pBloomHTexture);
		SAFE_RELEASE(m_pBloomHSurface);
		SAFE_RELEASE(m_pBloomVTexture);
		SAFE_RELEASE(m_pBloomVSurface);
		return D3D_OK;
	}

	#pragma region Standard Procedure Functions
	HRESULT PostProcessBloom::Render(IDirect3DTexture9* pSrcColorTexture, IDirect3DSurface9* pDstSurface)
	{
		//	Set Vertex Decl & Set Stream Source
		m_pDevice->SetVertexDeclaration(m_pVertDeclPP);	// Set the vertex declaration
		m_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(PPVERT));

		//if(SUCCEEDED(m_pDevice->BeginScene()))
		{
			UINT cPasses;
			// Bright pass
			m_pDevice->SetRenderTarget(NULL, m_pBrightPassSurface);
			m_pEffectBrightPass->SetTechnique(m_hTPostProcessBP);
			m_pEffectBrightPass->Begin(&cPasses, 0);
			m_pEffectBrightPass->SetTexture(m_hTexSourceBP, pSrcColorTexture);
			m_pEffectBrightPass->CommitChanges();
			m_pDevice->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0L);
			m_pEffectBrightPass->BeginPass(0);
			m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			m_pEffectBrightPass->EndPass();
			m_pEffectBrightPass->End();

			// Downsize 2x on the bright pass surface
			m_pDevice->SetRenderTarget(NULL, m_pDownsize2xSurface);
			m_pEffectDownSize2x->SetTechnique(m_hTPostProcessD2);
			m_pEffectDownSize2x->Begin(&cPasses, 0);
			m_pEffectDownSize2x->SetTexture(m_hTexSourceD2, m_pBrightPassTexture);
			m_pEffectDownSize2x->CommitChanges();
			m_pDevice->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0L);
			m_pEffectDownSize2x->BeginPass(0);
			m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			m_pEffectDownSize2x->EndPass();
			m_pEffectDownSize2x->End();

			// Downsize 4x on the bright pass surface
			m_pDevice->SetRenderTarget(NULL, m_pDownsize4xSurface);
			m_pEffectDownSize4x->SetTechnique(m_hTPostProcessD4);
			m_pEffectDownSize4x->Begin(&cPasses, 0);
			m_pEffectDownSize4x->SetTexture(m_hTexSourceD4, m_pBrightPassTexture);
			m_pEffectDownSize4x->CommitChanges();
			m_pDevice->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0L);
			m_pEffectDownSize4x->BeginPass(0);
			m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			m_pEffectDownSize4x->EndPass();
			m_pEffectDownSize4x->End();

			// horizontal bloom on 2x surface
			m_pDevice->SetRenderTarget(NULL, m_pBloomHSurface);
			m_pEffectBloomH->SetTechnique(m_hTPostProcessBH);
			m_pEffectBloomH->Begin(&cPasses, 0);
			m_pEffectBloomH->SetTexture(m_hTexSourceBH, m_pDownsize2xTexture);
			m_pEffectBloomH->CommitChanges();
			m_pDevice->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0L);
			m_pEffectBloomH->BeginPass(0);
			m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			m_pEffectBloomH->EndPass();
			m_pEffectBloomH->End();

			// vertical bloom on 2x surface
			m_pDevice->SetRenderTarget(NULL, m_pBloomVSurface);
			m_pEffectBloomV->SetTechnique(m_hTPostProcessBV);
			m_pEffectBloomV->Begin(&cPasses, 0);
			m_pEffectBloomV->SetTexture(m_hTexSourceBV, m_pBloomHTexture);
			m_pEffectBloomV->CommitChanges();
			m_pDevice->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0L);
			m_pEffectBloomV->BeginPass(0);
			m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			m_pEffectBloomV->EndPass();
			m_pEffectBloomV->End();

			// combine 2x, reuse bright pass texture
			m_pDevice->SetRenderTarget(NULL, m_pBrightPassSurface);
			m_pEffect->SetTechnique(m_hTPostProcess);
			m_pEffect->Begin(&cPasses, 0);
			m_pEffect->SetTexture(m_hTexScene, pSrcColorTexture);		// original image
			m_pEffect->SetTexture(m_hTexSource, m_pBloomVTexture);		// source image
			m_pEffect->CommitChanges();
			m_pDevice->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0L);
			m_pEffect->BeginPass(0);
			m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			m_pEffect->EndPass();
			m_pEffect->End();

			// horizontal blur on 4x surface
			m_pDevice->SetRenderTarget(NULL, m_pBloomHSurface);
			m_pEffectGBlurH->SetTechnique(m_hTPostProcessGBH);
			m_pEffectGBlurH->Begin(&cPasses, 0);
			m_pEffectGBlurH->SetTexture(m_hTexSourceGBH, m_pDownsize4xTexture);
			m_pEffectGBlurH->CommitChanges();
			m_pDevice->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0L);
			m_pEffectGBlurH->BeginPass(0);
			m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			m_pEffectGBlurH->EndPass();
			m_pEffectGBlurH->End();

			// vertical blur on 4x surface
			m_pDevice->SetRenderTarget(NULL, m_pBloomVSurface);
			m_pEffectGBlurV->SetTechnique(m_hTPostProcessGBV);
			m_pEffectGBlurV->Begin(&cPasses, 0);
			m_pEffectGBlurV->SetTexture(m_hTexSourceGBV, m_pBloomHTexture);
			m_pEffectGBlurV->CommitChanges();
			m_pDevice->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0L);
			m_pEffectGBlurV->BeginPass(0);
			m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			m_pEffectGBlurV->EndPass();
			m_pEffectGBlurV->End();

			// combine 4x
			m_pDevice->SetRenderTarget(NULL, pDstSurface);
			m_pEffect->SetTechnique(m_hTPostProcess);
			m_pEffect->Begin(&cPasses, 0);
			m_pEffect->SetTexture(m_hTexScene, m_pBrightPassTexture);	// original image
			m_pEffect->SetTexture(m_hTexSource, m_pBloomVTexture);		// source image
			m_pEffect->CommitChanges();
			m_pDevice->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0L);
			m_pEffect->BeginPass(0);
			m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
			m_pEffect->EndPass();
			m_pEffect->End();

			//m_pDevice->EndScene(); // End the scene
			return D3D_OK;
		}
		return D3DERR_INVALIDCALL;
	}
	void PostProcessBloom::onCreateDevice(IDirect3DDevice9* pd3dDevice, UINT width, UINT height)
	{
		initPermanentResources(pd3dDevice, width, height);
		initTemporaryResources(pd3dDevice, width, height);
	}
	void PostProcessBloom::onLostDevice()
	{
		m_pEffect->OnLostDevice();
		m_pEffectBrightPass->OnLostDevice();
		m_pEffectDownSize2x->OnLostDevice();
		m_pEffectDownSize4x->OnLostDevice();
		m_pEffectBloomH->OnLostDevice();
		m_pEffectBloomV->OnLostDevice();
		m_pEffectGBlurH->OnLostDevice();
		m_pEffectGBlurV->OnLostDevice();
		releaseTemporaryResources();
	}
	void PostProcessBloom::onResetDevice(IDirect3DDevice9* pd3dDevice, UINT width, UINT height)
	{
		m_pEffect->OnResetDevice();
		m_pEffectBrightPass->OnResetDevice();
		m_pEffectDownSize2x->OnResetDevice();
		m_pEffectDownSize4x->OnResetDevice();
		m_pEffectBloomH->OnResetDevice();
		m_pEffectBloomV->OnResetDevice();
		m_pEffectGBlurH->OnResetDevice();
		m_pEffectGBlurV->OnResetDevice();
		initTemporaryResources(pd3dDevice, width, height);
	}
	void PostProcessBloom::onDestroy(IDirect3DDevice9* pd3dDevice)
	{
		releasePermanentResources();
		releaseTemporaryResources();
	}
	#pragma endregion
}