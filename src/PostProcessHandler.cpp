#include "PostProcessHandler.h"

#include <stdio.h>
#include <stdlib.h>

namespace PP{
	#pragma region Variables Definition

	DWORD dwZEnable=0;
	DWORD dwZWriteEnable=0;
	DWORD dwLocalViewer=0;
	DWORD dwAlphaTestEnable=0;
	DWORD dwCullMode=0;
	DWORD dwAlphaBlendEnable=0;
	DWORD dwZFunc=0;
	DWORD dwSrcBlend=0;
	DWORD dwDestBlend=0;
	DWORD dwFogEnable=0;
	DWORD dwLighting=0;
	
	IDirect3DDevice9* m_pDevice=NULL;
	UINT g_deviceWidth=0;
	UINT g_deviceHeight=0;

	IDirect3DTexture9* g_pSourceRT_Texture=NULL;
	IDirect3DSurface9* g_pSourceRT_Surface=NULL;
	IDirect3DTexture9* g_pTargetRT_Texture=NULL;
	IDirect3DSurface9* g_pTargetRT_Surface=NULL;

	PostProcess* g_pPostProcessChain[MAX_POST_PROCESS_COUNT];
	int g_post_process_count = 0;

	bool g_presented = false;

	#pragma endregion

	#pragma region Function Defintions

	/**
	*	Initialize temporary D3D resources
	*	(Resources that need to be re-created after device has been lost)
	*/
	HRESULT initTemporaryResources(IDirect3DDevice9* pd3dDevice)
	{
		HRESULT hr;

		// Create textures for rendering
		hr = pd3dDevice->CreateTexture(g_deviceWidth, g_deviceHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A16B16G16R16F, D3DPOOL_DEFAULT, &g_pSourceRT_Texture, NULL);
		if (FAILED(hr))
		{
			MessageBox(NULL, "Fail to create texture!", "Error", MB_OK);
			return hr;
		}
		g_pSourceRT_Texture->GetSurfaceLevel(0, &g_pSourceRT_Surface);
		pd3dDevice->CreateTexture(g_deviceWidth, g_deviceHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A16B16G16R16F, D3DPOOL_DEFAULT, &g_pTargetRT_Texture, NULL);
		g_pTargetRT_Texture->GetSurfaceLevel(0, &g_pTargetRT_Surface);
		return hr;
	}

	/**
	*	Initialize permanent D3D resources
	*	(Resources that persist even after device has been lost)
	*/
	HRESULT initPermanentResources(IDirect3DDevice9* pd3dDevice)
	{
		//init effect chain
		// TODO: Use vector on effect chain
		g_post_process_count = 3;
		g_pPostProcessChain[0] = new PostProcessHDR();
		g_pPostProcessChain[0]->onCreateDevice(pd3dDevice, g_deviceWidth, g_deviceHeight);
		g_pPostProcessChain[1] = new PostProcessSMAA();
		g_pPostProcessChain[1]->onCreateDevice(pd3dDevice, g_deviceWidth, g_deviceHeight);
		g_pPostProcessChain[2] = new PostProcessBloom();
		g_pPostProcessChain[2]->onCreateDevice(pd3dDevice, g_deviceWidth, g_deviceHeight);
		return D3D_OK;
	}

	/**
	*	Release/Destroy all global temporary D3D resources
	*/
	HRESULT releaseTemporaryResources()
	{
		SAFE_RELEASE(g_pSourceRT_Texture);
		SAFE_RELEASE(g_pSourceRT_Surface);
		SAFE_RELEASE(g_pTargetRT_Texture);
		SAFE_RELEASE(g_pTargetRT_Surface);
		return D3D_OK;
	}

	/**
	*	Release/Destroy all global permanent D3D resources
	*/
	HRESULT releasePermanentResources()
	{
		for (int i=0; i<g_post_process_count; i++)
		{
			g_pPostProcessChain[i]->onDestroy(m_pDevice);
			delete g_pPostProcessChain[i];
		}
		// For releasing pre-loaded textures
		return D3D_OK;
	}

	/**
	*	Retrieve and save screen dimensions,
	*	must be called each time screen resolution changes.
	*/
	void setupScreenDimensions(IDirect3DDevice9* pd3dDevice)
	{
		// Get screen dimensions
		IDirect3DSurface9* t_pSurface = NULL;
		D3DSURFACE_DESC t_Desc;
		pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &t_pSurface);
		t_pSurface->GetDesc(&t_Desc);
		g_deviceWidth = t_Desc.Width;
		g_deviceHeight = t_Desc.Height;
		t_pSurface->Release();
	}

	/**
	*	Swap g_pTargetRT_Texture/g_pSourceRT_Texture
	*/
	void swapTextures()
	{
		IDirect3DTexture9* pTempTexture = g_pTargetRT_Texture;
		g_pTargetRT_Texture = g_pSourceRT_Texture;
		g_pSourceRT_Texture = pTempTexture;
		pTempTexture = NULL;

		IDirect3DSurface9* pTempSurface = g_pTargetRT_Surface;
		g_pTargetRT_Surface = g_pSourceRT_Surface;
		g_pSourceRT_Surface = pTempSurface;
		pTempSurface = NULL;
	}

	/**
	*	Perform Post Process on a device
	*/
	HRESULT PerformPostProcess(IDirect3DDevice9* pd3dDevice)
	{
		//
		// Preparation
		//
		IDirect3DSurface9* pOldRT_Surface = NULL;				// original render target(backbuffer)
		pd3dDevice->GetRenderTarget(0, &pOldRT_Surface);		// save the original render target
		IDirect3DSurface9* pRT_Surface = NULL;					// current render target
		backupStates(pd3dDevice);								// backup render states

		#ifndef RENDER_TO_BACK_BUFFER
		// Copy backbuffer to target texture since we are going to swap the source and target textures
		pd3dDevice->StretchRect(pOldRT_Surface, NULL, g_pTargetRT_Surface, NULL, D3DTEXF_NONE);
		#endif

		//
		// Post Process Loop
		//
		for (int i=0; i<g_post_process_count; i++)
		{
			PostProcess* pPProcess = g_pPostProcessChain[i];

			//
			//	Initialize soure/target
			//
			#ifndef RENDER_TO_BACK_BUFFER
			// Swap the target texture with the source texture
			swapTextures();
			// Set texture surface as new render target
			pRT_Surface = g_pTargetRT_Surface;
			pd3dDevice->SetRenderTarget(0, pRT_Surface);
			#else
			// Release the backbuffer surface from last render
			SAFE_RELEASE(pRT_Surface);
			// We dont need to set render target here because backbuffer is already the default render target.
			pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pRT_Surface);
			// Copy back buffer to source texture (g_pSourceRT_Texture)
			pd3dDevice->StretchRect(pRT_Surface, NULL, g_pSourceRT_Surface, NULL, D3DTEXF_NONE);
			#endif

			//
			// Render the quad
			//
			pPProcess->Render(g_pSourceRT_Texture, pRT_Surface);

		}


		//
		// Restore render states
		//
		restoreStates(pd3dDevice);


		//
		// Output render result to the screen(not needed in RENDER_TO_BACKBUFFER)
		//
		#ifndef RENDER_TO_BACK_BUFFER
		pd3dDevice->SetRenderTarget(0, pOldRT_Surface);
		pd3dDevice->StretchRect(pRT_Surface, 0, pOldRT_Surface, 0, D3DTEXF_NONE);
		#else
		SAFE_RELEASE(pRT_Surface);
		#endif
		SAFE_RELEASE(pOldRT_Surface);
		return D3D_OK;
	}

	/**
	*	Backup render states
	*/
	void backupStates(IDirect3DDevice9* pd3dDevice)
	{
		pd3dDevice->GetRenderState(D3DRS_ZENABLE, &dwZEnable);
		pd3dDevice->SetRenderState(D3DRS_ZENABLE, 1);

		pd3dDevice->GetRenderState(D3DRS_LOCALVIEWER, &dwLocalViewer);
		pd3dDevice->SetRenderState(D3DRS_LOCALVIEWER, 1);

		pd3dDevice->GetRenderState(D3DRS_ZWRITEENABLE, &dwZWriteEnable);
		pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1);

		pd3dDevice->GetRenderState(D3DRS_ALPHATESTENABLE, &dwAlphaTestEnable);
		pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);

		pd3dDevice->GetRenderState(D3DRS_CULLMODE, &dwCullMode);
		pd3dDevice->SetRenderState(D3DRS_CULLMODE, 3); //1

		pd3dDevice->GetRenderState(D3DRS_ALPHABLENDENABLE, &dwAlphaBlendEnable);
		pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);	//1

		pd3dDevice->GetRenderState(D3DRS_ZFUNC, &dwZFunc);
		pd3dDevice->SetRenderState(D3DRS_ZFUNC, 4);

		pd3dDevice->GetRenderState(D3DRS_DESTBLEND, &dwDestBlend);
		//pd3dDevice->SetRenderState(D3DRS_DESTBLEND, 6);
		pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

		pd3dDevice->GetRenderState(D3DRS_SRCBLEND, &dwSrcBlend);
		pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);

		pd3dDevice->GetRenderState(D3DRS_FOGENABLE, &dwFogEnable);
		pd3dDevice->SetRenderState(D3DRS_FOGENABLE, 0);
	
		pd3dDevice->GetRenderState(D3DRS_LIGHTING, &dwLighting);
		pd3dDevice->SetRenderState(D3DRS_LIGHTING, 0);
	}

	/**
	*	Restore render states
	*/
	void restoreStates(IDirect3DDevice9* pd3dDevice)
	{
		pd3dDevice->SetRenderState(D3DRS_ZENABLE, dwZEnable);
		pd3dDevice->SetRenderState(D3DRS_LOCALVIEWER, dwLocalViewer);
		pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, dwZWriteEnable);
		pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, dwAlphaTestEnable);
		pd3dDevice->SetRenderState(D3DRS_CULLMODE, dwCullMode);
		pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, dwAlphaBlendEnable);
		pd3dDevice->SetRenderState(D3DRS_ZFUNC, dwZFunc);
		pd3dDevice->SetRenderState(D3DRS_DESTBLEND, dwDestBlend);
		pd3dDevice->SetRenderState(D3DRS_SRCBLEND, dwSrcBlend);
		pd3dDevice->SetRenderState(D3DRS_FOGENABLE, dwFogEnable);
		pd3dDevice->SetRenderState(D3DRS_LIGHTING, dwLighting);
	}
	#pragma endregion

	#pragma region Standard Procedure Functions
	void onCreateDevice(IDirect3DDevice9* pd3dDevice)
	{
		m_pDevice = pd3dDevice;
		setupScreenDimensions(pd3dDevice);
		initTemporaryResources(pd3dDevice);
		initPermanentResources(pd3dDevice);
	}

	void onLostDevice()
	{
		releaseTemporaryResources();
		for (int i=0; i<g_post_process_count; i++)
		{
			g_pPostProcessChain[i]->onLostDevice();
		}
	}

	void onResetDevice(IDirect3DDevice9* pd3dDevice)
	{
		setupScreenDimensions(pd3dDevice);
		initTemporaryResources(pd3dDevice);
		for (int i=0; i<g_post_process_count; i++)
		{
			g_pPostProcessChain[i]->onResetDevice(pd3dDevice, g_deviceWidth, g_deviceHeight);
		}
		
	}

	void onDestroy(IDirect3DDevice9* pd3dDevice)
	{
		releaseTemporaryResources();
		releasePermanentResources();
	}
	#pragma endregion
}