#include "HDRScene.h"

namespace HDR {
	//
	// Private Functions and Variables
	//
	bool isEnable, isAdaptorSupported;

	HRESULT initTemporaryResources()
	{
		HRESULT hr;
		// Setup screen dimensions
		IDirect3DSurface9* t_pSurface;
		m_pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &t_pSurface);
		D3DSURFACE_DESC t_Desc;
		t_pSurface->GetDesc(&t_Desc);	// this would actually increase the reference count on backbuffer by 1
		g_deviceWidth = t_Desc.Width;
		g_deviceHeight = t_Desc.Height;
		SAFE_RELEASE(t_pSurface);

		// Create HDR texture
		hr = m_pDevice->CreateTexture(g_deviceWidth, g_deviceHeight, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A16B16G16R16F, D3DPOOL_DEFAULT, &g_pHDRTexture, NULL);
		if (FAILED(hr))
		{
			MessageBox(NULL, "Fail to create texture!", "Error", MB_OK);
			return hr;
		}
		g_pHDRTexture->GetSurfaceLevel(0, &g_pHDRSurface);
		return D3D_OK;
	}
	HRESULT releaseTemporaryResources()
	{
		SAFE_RELEASE(g_pBackBuffer);
		SAFE_RELEASE(g_pHDRTexture);
		SAFE_RELEASE(g_pHDRSurface);
		return D3D_OK;
	}
	// Detour the later rendering into a HDR texture
	void setHDRRenderTarget()
	{
		m_pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &g_pBackBuffer);
		m_pDevice->SetRenderTarget(NULL, g_pHDRSurface);
		//m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 64, 64, 128), 1.0f, 0); // purple
		m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
	}
	// Restore the original backbuffer as the render target
	void restoreBackBuffer()
	{
		m_pDevice->StretchRect(g_pHDRSurface, NULL, g_pBackBuffer, NULL, D3DTEXF_NONE);
		m_pDevice->SetRenderTarget(NULL, g_pBackBuffer);
		g_pBackBuffer->Release();
	}


	//
	// Public Functions and Variables
	//
	IDirect3DDevice9* m_pDevice = NULL;
	IDirect3DTexture9* g_pHDRTexture = NULL;
	IDirect3DSurface9* g_pHDRSurface = NULL;
	IDirect3DSurface9* g_pBackBuffer = NULL;
	UINT g_deviceWidth = 800;
	UINT g_deviceHeight = 600;
	
	bool isUsable()
	{
		return (isEnable && isAdaptorSupported);
	}


	//
	// Standard Procedure Functions
	//
	void onCreateDevice(IDirect3DDevice9* pd3dDevice)
	{
		m_pDevice = pd3dDevice;

		// TODO: Check device capabilities
		isEnable = true;
		isAdaptorSupported = true;

		if (isUsable())
		{
			initTemporaryResources();
		}
	}
	void onBeginScene()
	{
		if (isUsable())
		{
			setHDRRenderTarget();
		}
	}
	void onEndScene()
	{
		if (isUsable())
		{
			restoreBackBuffer();
		}
	}
	void onLostDevice()
	{
		if (isUsable())
		{
			releaseTemporaryResources();
		}
	}
	void onResetDevice(IDirect3DDevice9* pd3dDevice)
	{
		if (isUsable())
		{
			initTemporaryResources();
		}
	}
}