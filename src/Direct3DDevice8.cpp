#include "Direct3DDevice8.h"
#include "Direct3DBaseTexture8.h"
#include "Direct3DCubeTexture8.h"
#include "Direct3DIndexBuffer8.h"
#include "Direct3DSurface8.h"
#include "Direct3DSwapChain8.h"
#include "Direct3DTexture8.h"
#include "Direct3DVertexBuffer8.h"
#include "Direct3DVolumeTexture8.h"

#if defined(_DEBUG) || defined(NORMALD3D)
#include "debug/RenderStageController.h"
#else
#include "RenderStageController.h"
#endif

#include "EffectController.h"		// external...
#include "PostProcessHandler.h"		// external...
#include "NormalMapHandler.h"		// external...
#include "HDRScene.h"				// external...
#include "DebugUtils.h"				// external...
#include "ShadowVolumeHandler.h"	// external...
#include "ShadowType.h"

CDirect3DDevice8::CDirect3DDevice8(IDirect3DDevice9* device, CDirect3D8* d3d)
: pDevice9(device)
, pDirect3D8(d3d)
, zBufferDiscardingEnabled(FALSE)
, g_baseVertexIndex(0)
{
	pDevice9->GetCreationParameters(&deviceCreationParameters);

#ifndef NORMALD3D
	// initialize effect controller
	CTRL::InitController();
#endif
	// initialize effect handler
	HDR::onCreateDevice(pDevice9);
	PP::onCreateDevice(pDevice9);
	NP::onCreateDevice(pDevice9);
	SV::onCreateDevice(pDevice9);
}

CDirect3DDevice8::~CDirect3DDevice8()
{
	// destroy effect handler
	HDR::onDestroy(pDevice9);
	NP::onDestroy(pDevice9);
	PP::onDestroy(pDevice9);
	SV::onDestroy(pDevice9);

	pDirect3D8->DevicePool.Destory(pDevice9);
	pDevice9 = NULL;
}

HRESULT WINAPI CDirect3DDevice8::QueryInterface(THIS_ REFIID riid, void** ppvObj)
{
	if (riid == IID_IUnknown
		|| riid == IID_IDirect3DDevice8)
	{
		AddRef();
		*ppvObj = this;
		return D3D_OK;
	}

	*ppvObj = NULL;
	return E_NOINTERFACE;
}

ULONG WINAPI CDirect3DDevice8::AddRef(THIS)
{
	return pDevice9->AddRef();
}

ULONG WINAPI CDirect3DDevice8::Release(THIS)
{
	ComptrGurad<IDirect3DDevice9> gurad(pDevice9);
	DWORD count = pDevice9->Release();
	if (1 == count)
	{
		delete this;
	}
	return count - 1;
}

HRESULT CDirect3DDevice8::SetZBufferDiscarding(bool IsEnabled)
{
	zBufferDiscardingEnabled = !!IsEnabled;
	return S_OK;
}

STDMETHODIMP CDirect3DDevice8::TestCooperativeLevel(THIS)
{
	return pDevice9->TestCooperativeLevel();
}

STDMETHODIMP_(UINT) CDirect3DDevice8::GetAvailableTextureMem(THIS)
{
	return pDevice9->GetAvailableTextureMem();
}

STDMETHODIMP CDirect3DDevice8::ResourceManagerDiscardBytes(THIS_ DWORD Bytes)
{
	return pDevice9->EvictManagedResources();
}

STDMETHODIMP CDirect3DDevice8::GetDirect3D(THIS_ IDirect3D8** ppD3D8)
{
	if (pDirect3D8 == NULL)
		return D3DERR_INVALIDCALL;
	pDirect3D8->AddRef();
	*ppD3D8 = pDirect3D8;
	return D3D_OK;
}

STDMETHODIMP CDirect3DDevice8::GetDeviceCaps(THIS_ D3DCAPS8* pCaps)
{
	D3DCAPS9 D3DCaps9;
	HRESULT result = pDevice9->GetDeviceCaps(&D3DCaps9);
	memcpy(pCaps, &D3DCaps9, sizeof(D3DCAPS8));
	return result;
}

STDMETHODIMP CDirect3DDevice8::GetDisplayMode(THIS_ D3DDISPLAYMODE* pMode)
{
	return pDevice9->GetDisplayMode(deviceCreationParameters.AdapterOrdinal, pMode);
}

STDMETHODIMP CDirect3DDevice8::GetCreationParameters(THIS_ D3DDEVICE_CREATION_PARAMETERS *pParameters)
{
	return pDevice9->GetCreationParameters(pParameters);
}

STDMETHODIMP CDirect3DDevice8::SetCursorProperties(THIS_ UINT XHotSpot, UINT YHotSpot, IDirect3DSurface8* pCursorBitmap)
{
	IDirect3DSurface9* pCursorBitmap9 = ((CDirect3DSurface8*)pCursorBitmap)->ToNine();
	return pDevice9->SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap9);
}

STDMETHODIMP_(void) CDirect3DDevice8::SetCursorPosition(THIS_ int X, int Y, DWORD Flags)
{
	pDevice9->SetCursorPosition(X, Y, Flags);
}

STDMETHODIMP_(BOOL) CDirect3DDevice8::ShowCursor(THIS_ BOOL bShow)
{
	return pDevice9->ShowCursor(bShow);
}

STDMETHODIMP CDirect3DDevice8::CreateAdditionalSwapChain(THIS_ D3D8PRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain8** pSwapChain)
{
	IDirect3D9* pDirect3D9 = NULL;
	HRESULT hr = pDevice9->GetDirect3D(&pDirect3D9);
	if (SUCCEEDED(hr))
	{
		D3DPRESENT_PARAMETERS D3DPresentationParameters9;
		ZeroMemory(&D3DPresentationParameters9, sizeof(D3DPresentationParameters9));
		D3DPresentationParameters9.AutoDepthStencilFormat = D3DFMT_D24S8; //pPresentationParameters->AutoDepthStencilFormat;
		D3DPresentationParameters9.BackBufferCount = pPresentationParameters->BackBufferCount;
		D3DPresentationParameters9.BackBufferFormat = pPresentationParameters->BackBufferFormat;
		D3DPresentationParameters9.BackBufferHeight = pPresentationParameters->BackBufferHeight;
		D3DPresentationParameters9.BackBufferWidth = pPresentationParameters->BackBufferWidth;
		D3DPresentationParameters9.EnableAutoDepthStencil = pPresentationParameters->EnableAutoDepthStencil;
		D3DPresentationParameters9.Flags = pPresentationParameters->Flags;
		D3DPresentationParameters9.FullScreen_RefreshRateInHz = pPresentationParameters->FullScreen_RefreshRateInHz;
		D3DPresentationParameters9.hDeviceWindow = pPresentationParameters->hDeviceWindow;
		D3DPresentationParameters9.MultiSampleQuality = 0;
		D3DPresentationParameters9.MultiSampleType = pPresentationParameters->MultiSampleType;
		D3DPresentationParameters9.PresentationInterval = pPresentationParameters->FullScreen_PresentationInterval;
		D3DPresentationParameters9.SwapEffect = pPresentationParameters->SwapEffect;
		D3DPresentationParameters9.Windowed = pPresentationParameters->Windowed;

		IDirect3DSwapChain9* pSwapChain9 = NULL;
		hr = pDevice9->CreateAdditionalSwapChain(&D3DPresentationParameters9, &pSwapChain9);
		if (SUCCEEDED(hr))
		{
			*pSwapChain = SwapChainPool.Create(pSwapChain9, this);
		}
		pDirect3D9->Release();
	}

	return hr;
}

STDMETHODIMP CDirect3DDevice8::Reset(THIS_ D3D8PRESENT_PARAMETERS* pPresentationParameters)
{
	// Lost device handling
	HDR::onLostDevice();
	PP::onLostDevice();
	NP::onLostDevice();
	SV::onLostDevice();

	IDirect3D9* pDirect3D9 = NULL;
	HRESULT hr = pDevice9->GetDirect3D(&pDirect3D9);
	if (SUCCEEDED(hr))
	{
		D3DPRESENT_PARAMETERS D3DPresentationParameters9;
		ZeroMemory(&D3DPresentationParameters9, sizeof(D3DPresentationParameters9));
		D3DPresentationParameters9.AutoDepthStencilFormat = D3DFMT_D24S8; //pPresentationParameters->AutoDepthStencilFormat;
		D3DPresentationParameters9.BackBufferCount = pPresentationParameters->BackBufferCount;
		D3DPresentationParameters9.BackBufferFormat = pPresentationParameters->BackBufferFormat;
		D3DPresentationParameters9.BackBufferHeight = pPresentationParameters->BackBufferHeight;
		D3DPresentationParameters9.BackBufferWidth = pPresentationParameters->BackBufferWidth;
		D3DPresentationParameters9.EnableAutoDepthStencil = pPresentationParameters->EnableAutoDepthStencil;
		D3DPresentationParameters9.Flags = pPresentationParameters->Flags;
		D3DPresentationParameters9.FullScreen_RefreshRateInHz = pPresentationParameters->FullScreen_RefreshRateInHz;
		D3DPresentationParameters9.hDeviceWindow = pPresentationParameters->hDeviceWindow;
		D3DPresentationParameters9.MultiSampleQuality = 0;
		D3DPresentationParameters9.MultiSampleType = pPresentationParameters->MultiSampleType;
		D3DPresentationParameters9.PresentationInterval = pPresentationParameters->FullScreen_PresentationInterval;
		D3DPresentationParameters9.SwapEffect = pPresentationParameters->SwapEffect;
		D3DPresentationParameters9.Windowed = pPresentationParameters->Windowed;
		hr = pDevice9->Reset(&D3DPresentationParameters9);
		pDirect3D9->Release();

		// Reset device handling
		HDR::onResetDevice(pDevice9);
		PP::onResetDevice(pDevice9);
		NP::onResetDevice(pDevice9);
		SV::onResetDevice(pDevice9);
	}

	return hr;
}

STDMETHODIMP CDirect3DDevice8::Present(THIS_ CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
#ifdef _DEBUG
	// Enable debug flag for PostProcess
	if (GetAsyncKeyState(VK_F11))
	{
		DB::g_dbDebugOn = true;
		MessageBox(NULL, "Capturing render sequence, please be patient...", "info", MB_OK);
	}
	else
		DB::g_dbDebugOn = false;
	DB::restDrawPrimitiveCount();

	// Enable/Disable Unit Shadow
	if (GetAsyncKeyState(VK_F9))
	{
		CTRL::g_DisableUnitShadow = !CTRL::g_DisableUnitShadow;
		if (CTRL::g_DisableUnitShadow)
			MessageBox(NULL, "Default unit shadow has been disabled!", "info", MB_OK);
		else
			MessageBox(NULL, "Default unit shadow has been enabled!", "info", MB_OK);
	}

	// Enable/Disable ShadowVolume
	if (GetAsyncKeyState(VK_F8))
	{
		CTRL::g_EnableSV = !CTRL::g_EnableSV;
		if (CTRL::g_EnableSV)
			MessageBox(NULL, "ShadowVolume has been enabled!", "info", MB_OK);
		else
			MessageBox(NULL, "ShadowVolume has been disabled!", "info", MB_OK);
	}

	// Enable/Disable NormalMap
	if (GetAsyncKeyState(VK_F7))
	{
		CTRL::g_EnableNP = !CTRL::g_EnableNP;
		if (CTRL::g_EnableNP)
			MessageBox(NULL, "NormalMap has been enabled!", "info", MB_OK);
		else
			MessageBox(NULL, "NormalMap has been disabled!", "info", MB_OK);
	}

	// Enable/Disable PostProcess
	if (GetAsyncKeyState(VK_F6))
	{
		CTRL::g_EnablePP = !CTRL::g_EnablePP;
		if (CTRL::g_EnablePP)
			MessageBox(NULL, "PostProcess has been enabled!", "info", MB_OK);
		else
			MessageBox(NULL, "PostProcess has been disabled!", "info", MB_OK);
	}

	// Enable/Disable HDR
	if (GetAsyncKeyState(VK_F5))
	{
		CTRL::g_EnableHDR = !CTRL::g_EnableHDR;
		if (CTRL::g_EnableHDR)
			MessageBox(NULL, "HDR has been enabled!", "info", MB_OK);
		else
			MessageBox(NULL, "HDR has been disabled!", "info", MB_OK);
	}
#endif

	resetRenderStage();
	PP::g_presented = false;
	SV::g_rendered = false;
	NP::EXCP::CheckAll();	// check exception list
	return pDevice9->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

STDMETHODIMP CDirect3DDevice8::GetBackBuffer(THIS_ UINT BackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface8** ppBackBuffer)
{
	IDirect3DSurface9* pBackBuffer9 = NULL;
	HRESULT hr = pDevice9->GetBackBuffer(deviceCreationParameters.AdapterOrdinal, BackBuffer, Type, &pBackBuffer9);
	if (SUCCEEDED(hr))
	{
		*ppBackBuffer = SurfacePool.Create(pBackBuffer9, this);
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::GetRasterStatus(THIS_ D3DRASTER_STATUS* pRasterStatus)
{
	return pDevice9->GetRasterStatus(deviceCreationParameters.AdapterOrdinal, pRasterStatus);
}

STDMETHODIMP_(void) CDirect3DDevice8::SetGammaRamp(THIS_ DWORD Flags, CONST D3DGAMMARAMP* pRamp)
{
	pDevice9->SetGammaRamp(deviceCreationParameters.AdapterOrdinal, Flags, pRamp);
}

STDMETHODIMP_(void) CDirect3DDevice8::GetGammaRamp(THIS_ D3DGAMMARAMP* pRamp)
{
	pDevice9->GetGammaRamp(deviceCreationParameters.AdapterOrdinal, pRamp);
}

STDMETHODIMP CDirect3DDevice8::CreateTexture(THIS_ UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture8** ppTexture)
{
	IDirect3DTexture9* pTexture9 = NULL;
	HRESULT hr = pDevice9->CreateTexture(Width, Height, Levels, Usage, Format, Pool, &pTexture9, NULL);
	if (SUCCEEDED(hr))
	{
		*ppTexture = TexturePool.Create(pTexture9, this);
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::CreateVolumeTexture(THIS_ UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture8** ppVolumeTexture)
{
	IDirect3DVolumeTexture9* pVolumeTexture9 = NULL;
	HRESULT hr = pDevice9->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, &pVolumeTexture9, NULL);
	if (SUCCEEDED(hr))
	{
		*ppVolumeTexture = VolumeTexturePool.Create(pVolumeTexture9, this);
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::CreateCubeTexture(THIS_ UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture8** ppCubeTexture)
{
	IDirect3DCubeTexture9* pCubeTexture9 = NULL;
	HRESULT hr = pDevice9->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, &pCubeTexture9, NULL);
	if (SUCCEEDED(hr))
	{
		*ppCubeTexture = CubeTexturePool.Create(pCubeTexture9, this);
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::CreateVertexBuffer(THIS_ UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer8** ppVertexBuffer)
{
	IDirect3DVertexBuffer9* pVertexBuffer9 = NULL;
	HRESULT hr = pDevice9->CreateVertexBuffer(Length, Usage, FVF, Pool, &pVertexBuffer9, NULL);
	if (SUCCEEDED(hr))
	{
		*ppVertexBuffer = VertexBufferPool.Create(pVertexBuffer9, this);
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::CreateIndexBuffer(THIS_ UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer8** ppIndexBuffer)
{
	IDirect3DIndexBuffer9* pIndexBuffer9 = NULL;
	HRESULT hr = pDevice9->CreateIndexBuffer(Length, Usage, Format, Pool, &pIndexBuffer9, NULL);
	if (SUCCEEDED(hr))
	{
		*ppIndexBuffer = IndexBufferPool.Create(pIndexBuffer9, this);
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::CreateRenderTarget(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, BOOL Lockable, IDirect3DSurface8** ppSurface)
{
	IDirect3D9* pDirect3D9 = NULL;
	HRESULT hr = pDevice9->GetDirect3D(&pDirect3D9);
	if (SUCCEEDED(hr))
	{
		DWORD multiSampleQuality;
		hr = pDirect3D9->CheckDeviceMultiSampleType(deviceCreationParameters.AdapterOrdinal, deviceCreationParameters.DeviceType, Format, TRUE, MultiSample, &multiSampleQuality);
		if (SUCCEEDED(hr))
		{
			IDirect3DSurface9* pSurface9 = NULL;
			hr = pDevice9->CreateRenderTarget(Width, Height, Format, MultiSample, multiSampleQuality, Lockable, &pSurface9, NULL);
			if (SUCCEEDED(hr))
			{
				*ppSurface = SurfacePool.Create(pSurface9, this);
			}
		}

		pDirect3D9->Release();
	}

	return hr;
}

STDMETHODIMP CDirect3DDevice8::CreateDepthStencilSurface(THIS_ UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, IDirect3DSurface8** ppSurface)
{
	IDirect3D9* pDirect3D9 = NULL;
	HRESULT hr = pDevice9->GetDirect3D(&pDirect3D9);
	if (SUCCEEDED(hr))
	{
		DWORD multiSampleQuality;
		hr = pDirect3D9->CheckDeviceMultiSampleType(deviceCreationParameters.AdapterOrdinal, deviceCreationParameters.DeviceType, Format, TRUE, MultiSample, &multiSampleQuality);
		if (SUCCEEDED(hr))
		{
			IDirect3DSurface9* pSurface9 = NULL;
			hr = pDevice9->CreateDepthStencilSurface(Width, Height, Format, MultiSample, multiSampleQuality, zBufferDiscardingEnabled, &pSurface9, NULL);
			if (SUCCEEDED(hr))
			{
				*ppSurface = SurfacePool.Create(pSurface9, this);
			}
		}

		pDirect3D9->Release();
	}

	return hr;
}

STDMETHODIMP CDirect3DDevice8::CreateImageSurface(THIS_ UINT Width, UINT Height, D3DFORMAT Format, IDirect3DSurface8** ppSurface)
{
	IDirect3DSurface9* pSurface9 = NULL;
	HRESULT hr = pDevice9->CreateOffscreenPlainSurface(Width, Height, Format, D3DPOOL_SCRATCH, &pSurface9, NULL);
	if (SUCCEEDED(hr))
	{
		*ppSurface = SurfacePool.Create(pSurface9, this);
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::CopyRects(THIS_ IDirect3DSurface8* pSourceSurface, CONST RECT* pSourceRectsArray, UINT cRects, IDirect3DSurface8* pDestinationSurface, CONST POINT* pDestPointsArray)
{
	HRESULT result = D3DERR_INVALIDCALL;

	IDirect3DSurface9* pSourceSurface9 = ((CDirect3DSurface8*)pSourceSurface)->ToNine();
	IDirect3DSurface9* pDestinationSurface9 = ((CDirect3DSurface8*)pDestinationSurface)->ToNine();

	if (pSourceRectsArray == NULL)
	{
		if (pDestPointsArray == NULL)
		{
			POINT pt = { 0, 0 };
			result = pDevice9->UpdateSurface(pSourceSurface9, NULL, pDestinationSurface9, &pt);
		}
		else
		{
			result = pDevice9->UpdateSurface(pSourceSurface9, NULL, pDestinationSurface9, pDestPointsArray);
		}
	}
	else
	{
		if (pDestPointsArray == NULL)
		{
			POINT pt = { 0, 0 };
			for (UINT i = 0; i < cRects; i++)
			{
				result = pDevice9->UpdateSurface(pSourceSurface9, &pSourceRectsArray[i], pDestinationSurface9, &pt);
				if (!SUCCEEDED(result))
				{
					break;
				}
			}
		}
		else
		{
			for (UINT i = 0; i < cRects; i++)
			{
				result = pDevice9->UpdateSurface(pSourceSurface9, &pSourceRectsArray[i], pDestinationSurface9, &pDestPointsArray[i]);
				if (!SUCCEEDED(result))
				{
					break;
				}
			}
		}
	}

	return result;
}

STDMETHODIMP CDirect3DDevice8::UpdateTexture(THIS_ IDirect3DBaseTexture8* pSourceTexture, IDirect3DBaseTexture8* pDestinationTexture)
{
	IDirect3DBaseTexture9* pSourceTexture9 = ((CDirect3DBaseTexture8*)pSourceTexture)->ToNine();
	IDirect3DBaseTexture9* pDestinationTexture9 = ((CDirect3DBaseTexture8*)pDestinationTexture)->ToNine();
	return pDevice9->UpdateTexture(pSourceTexture9, pDestinationTexture9);
}

STDMETHODIMP CDirect3DDevice8::GetFrontBuffer(THIS_ IDirect3DSurface8* pDestSurface)
{
	IDirect3DSurface9* pDestSurface9 = ((CDirect3DSurface8*)pDestSurface)->ToNine();
	return pDevice9->GetFrontBufferData(deviceCreationParameters.AdapterOrdinal, pDestSurface9);
}

STDMETHODIMP CDirect3DDevice8::SetRenderTarget(THIS_ IDirect3DSurface8* pRenderTarget, IDirect3DSurface8* pNewZStencil)
{
	if (pRenderTarget == NULL)
	{
		IDirect3DSurface9* pNewZStencil9 = ((CDirect3DSurface8*)pNewZStencil)->ToNine();
		return pDevice9->SetDepthStencilSurface(pNewZStencil9);
	}

	IDirect3DSurface9* pRenderTarget9 = ((CDirect3DSurface8*)pRenderTarget)->ToNine();
	HRESULT hr = pDevice9->SetRenderTarget(0, pRenderTarget9);
	if (pNewZStencil != NULL)
	{
		IDirect3DSurface9* pNewZStencil9 = ((CDirect3DSurface8*)pNewZStencil)->ToNine();
		hr = pDevice9->SetDepthStencilSurface(pNewZStencil9);
	}

	return hr;
}

STDMETHODIMP CDirect3DDevice8::GetRenderTarget(THIS_ IDirect3DSurface8** ppRenderTarget)
{
	IDirect3DSurface9* pSurface9 = NULL;
	HRESULT hr = pDevice9->GetRenderTarget(0, &pSurface9);
	if (SUCCEEDED(hr))
	{
		*ppRenderTarget = SurfacePool.Create(pSurface9, this);
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::GetDepthStencilSurface(THIS_ IDirect3DSurface8** ppZStencilSurface)
{
	IDirect3DSurface9* pSurface9 = NULL;
	HRESULT hr = pDevice9->GetDepthStencilSurface(&pSurface9);
	if (SUCCEEDED(hr))
	{
		*ppZStencilSurface = SurfacePool.Create(pSurface9, this);
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::BeginScene(THIS)
{
	HRESULT hr = pDevice9->BeginScene();
	
	if (CTRL::g_EnableEffect)
	{
		if (CTRL::g_EnableHDR)
			HDR::onBeginScene();
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::EndScene(THIS)
{
	if (CTRL::g_EnableEffect)
	{
		if (CTRL::g_EnableHDR)
			HDR::onEndScene();

		if (CTRL::g_EnableSV)
			pDevice9->Clear( 0L, NULL, D3DCLEAR_STENCIL, 0xff00bfff, 1.0f, 0L );
	}
	return pDevice9->EndScene();
}

STDMETHODIMP CDirect3DDevice8::Clear(THIS_ DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
	return pDevice9->Clear(Count, pRects, Flags, Color, Z, Stencil);
}

STDMETHODIMP CDirect3DDevice8::SetTransform(THIS_ D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
	g_State=State;
	return pDevice9->SetTransform(State, pMatrix);
}

STDMETHODIMP CDirect3DDevice8::GetTransform(THIS_ D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix)
{
	return pDevice9->GetTransform(State, pMatrix);
}

STDMETHODIMP CDirect3DDevice8::MultiplyTransform(THIS_ D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
	return pDevice9->MultiplyTransform(State, pMatrix);
}

STDMETHODIMP CDirect3DDevice8::SetViewport(THIS_ CONST D3DVIEWPORT8* pViewport)
{
	return pDevice9->SetViewport(pViewport);
}

STDMETHODIMP CDirect3DDevice8::GetViewport(THIS_ D3DVIEWPORT8* pViewport)
{
	return pDevice9->GetViewport(pViewport);
}

STDMETHODIMP CDirect3DDevice8::SetMaterial(THIS_ CONST D3DMATERIAL8* pMaterial)
{
	return pDevice9->SetMaterial(pMaterial);
}

STDMETHODIMP CDirect3DDevice8::GetMaterial(THIS_ D3DMATERIAL8* pMaterial)
{
	return pDevice9->GetMaterial(pMaterial);
}

STDMETHODIMP CDirect3DDevice8::SetLight(THIS_ DWORD Index, CONST D3DLIGHT8* pLight)
{
	return pDevice9->SetLight(Index, pLight);
}

STDMETHODIMP CDirect3DDevice8::GetLight(THIS_ DWORD Index, D3DLIGHT8* pLight)
{
	return pDevice9->GetLight(Index, pLight);
}

STDMETHODIMP CDirect3DDevice8::LightEnable(THIS_ DWORD Index, BOOL Enable)
{
	return pDevice9->LightEnable(Index, Enable);
}

STDMETHODIMP CDirect3DDevice8::GetLightEnable(THIS_ DWORD Index, BOOL* pEnable)
{
	return pDevice9->GetLightEnable(Index, pEnable);
}

STDMETHODIMP CDirect3DDevice8::SetClipPlane(THIS_ DWORD Index, CONST float* pPlane)
{
	return pDevice9->SetClipPlane(Index, pPlane);
}

STDMETHODIMP CDirect3DDevice8::GetClipPlane(THIS_ DWORD Index, float* pPlane)
{
	return pDevice9->GetClipPlane(Index, pPlane);
}

STDMETHODIMP CDirect3DDevice8::SetRenderState(THIS_ D3DRENDERSTATETYPE State, DWORD Value)
{
	g_DRS[State] = Value;	// record

	if (State == 153)
	{
		return pDevice9->SetSoftwareVertexProcessing(!!Value);
	}
	return pDevice9->SetRenderState(State, Value);
}

STDMETHODIMP CDirect3DDevice8::GetRenderState(THIS_ D3DRENDERSTATETYPE State, DWORD* pValue)
{
	if (State == 153/*D3DRS_SOFTWAREVERTEXPROCESSING*/)
	{
		*pValue = pDevice9->GetSoftwareVertexProcessing()? 1: 0;
		return D3D_OK;
	}
	return pDevice9->GetRenderState(State, pValue);
}

STDMETHODIMP CDirect3DDevice8::BeginStateBlock(THIS)
{
	return pDevice9->BeginStateBlock();
}

STDMETHODIMP CDirect3DDevice8::EndStateBlock(THIS_ DWORD* pToken)
{
	return pDevice9->EndStateBlock((IDirect3DStateBlock9**)pToken);
}

STDMETHODIMP CDirect3DDevice8::ApplyStateBlock(THIS_ DWORD Token)
{
	IDirect3DStateBlock9* pBlock = (IDirect3DStateBlock9*)Token;
	return pBlock->Apply();
}

STDMETHODIMP CDirect3DDevice8::CaptureStateBlock(THIS_ DWORD Token)
{
	IDirect3DStateBlock9* pBlock = (IDirect3DStateBlock9*)Token;
	return pBlock->Capture();
}

STDMETHODIMP CDirect3DDevice8::DeleteStateBlock(THIS_ DWORD Token)
{
	IDirect3DStateBlock9* pBlock = (IDirect3DStateBlock9*)Token;
	pBlock->Release();
	return D3D_OK;
}

STDMETHODIMP CDirect3DDevice8::CreateStateBlock(THIS_ D3DSTATEBLOCKTYPE Type, DWORD* pToken)
{
	return pDevice9->CreateStateBlock(Type, (IDirect3DStateBlock9**)pToken);
}

STDMETHODIMP CDirect3DDevice8::SetClipStatus(THIS_ CONST D3DCLIPSTATUS8* pClipStatus)
{
	return pDevice9->SetClipStatus(pClipStatus);
}

STDMETHODIMP CDirect3DDevice8::GetClipStatus(THIS_ D3DCLIPSTATUS8* pClipStatus)
{
	return pDevice9->GetClipStatus(pClipStatus);
}

STDMETHODIMP CDirect3DDevice8::GetTexture(THIS_ DWORD Stage, IDirect3DBaseTexture8** ppTexture)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::SetTexture(THIS_ DWORD Stage, IDirect3DBaseTexture8* pTexture)
{
	IDirect3DBaseTexture9* pTexture9 = ((CDirect3DBaseTexture8*)pTexture)->ToNine();
	g_Stage=Stage;
	g_pTexture9=pTexture9;
	return pDevice9->SetTexture(Stage, pTexture9);
}

STDMETHODIMP CDirect3DDevice8::GetTextureStageState(THIS_ DWORD Stage, D3D8TEXTURESTAGESTATETYPE Type, DWORD* pValue)
{
	switch (Type)
	{
	case D3D8TSS_COLOROP:
	case D3D8TSS_COLORARG1:
	case D3D8TSS_COLORARG2:
	case D3D8TSS_ALPHAOP:
	case D3D8TSS_ALPHAARG1:
	case D3D8TSS_ALPHAARG2:
	case D3D8TSS_BUMPENVMAT00:
	case D3D8TSS_BUMPENVMAT01:
	case D3D8TSS_BUMPENVMAT10:
	case D3D8TSS_BUMPENVMAT11:
	case D3D8TSS_TEXCOORDINDEX:
	case D3D8TSS_BUMPENVLSCALE:
	case D3D8TSS_BUMPENVLOFFSET:
	case D3D8TSS_TEXTURETRANSFORMFLAGS:
	case D3D8TSS_COLORARG0:
	case D3D8TSS_ALPHAARG0:
	case D3D8TSS_RESULTARG:
		return pDevice9->GetTextureStageState(Stage, (D3DTEXTURESTAGESTATETYPE)Type, pValue);
	case D3D8TSS_ADDRESSU:
		return pDevice9->GetSamplerState(Stage, D3DSAMP_ADDRESSU, pValue);
	case D3D8TSS_ADDRESSV:
		return pDevice9->GetSamplerState(Stage, D3DSAMP_ADDRESSV, pValue);
	case D3D8TSS_BORDERCOLOR:
		return pDevice9->GetSamplerState(Stage, D3DSAMP_BORDERCOLOR, pValue);
	case D3D8TSS_MAGFILTER:
		return pDevice9->GetSamplerState(Stage, D3DSAMP_MAGFILTER, pValue);
	case D3D8TSS_MINFILTER:
		return pDevice9->GetSamplerState(Stage, D3DSAMP_MINFILTER, pValue);
	case D3D8TSS_MIPFILTER:
		return pDevice9->GetSamplerState(Stage, D3DSAMP_MIPFILTER, pValue);
	case D3D8TSS_MIPMAPLODBIAS:
		return pDevice9->GetSamplerState(Stage, D3DSAMP_MIPMAPLODBIAS, pValue);
	case D3D8TSS_MAXMIPLEVEL:
		return pDevice9->GetSamplerState(Stage, D3DSAMP_MAXMIPLEVEL, pValue);
	case D3D8TSS_MAXANISOTROPY:
		return pDevice9->GetSamplerState(Stage, D3DSAMP_MAXANISOTROPY, pValue);
	case D3D8TSS_ADDRESSW:
		return pDevice9->GetSamplerState(Stage, D3DSAMP_ADDRESSW, pValue);
	}
	return D3DERR_INVALIDCALL;
}

STDMETHODIMP CDirect3DDevice8::SetTextureStageState(THIS_ DWORD Stage, D3D8TEXTURESTAGESTATETYPE Type, DWORD Value)
{
	switch (Type)
	{
	case D3D8TSS_COLOROP:
	case D3D8TSS_COLORARG1:
	case D3D8TSS_COLORARG2:
	case D3D8TSS_ALPHAOP:
	case D3D8TSS_ALPHAARG1:
	case D3D8TSS_ALPHAARG2:
	case D3D8TSS_BUMPENVMAT00:
	case D3D8TSS_BUMPENVMAT01:
	case D3D8TSS_BUMPENVMAT10:
	case D3D8TSS_BUMPENVMAT11:
	case D3D8TSS_TEXCOORDINDEX:
	case D3D8TSS_BUMPENVLSCALE:
	case D3D8TSS_BUMPENVLOFFSET:
	case D3D8TSS_TEXTURETRANSFORMFLAGS:
	case D3D8TSS_COLORARG0:
	case D3D8TSS_ALPHAARG0:
	case D3D8TSS_RESULTARG:
		return pDevice9->SetTextureStageState(Stage, (D3DTEXTURESTAGESTATETYPE)Type, Value);
	case D3D8TSS_ADDRESSU:
		return pDevice9->SetSamplerState(Stage, D3DSAMP_ADDRESSU, Value);
	case D3D8TSS_ADDRESSV:
		return pDevice9->SetSamplerState(Stage, D3DSAMP_ADDRESSV, Value);
	case D3D8TSS_BORDERCOLOR:
		return pDevice9->SetSamplerState(Stage, D3DSAMP_BORDERCOLOR, Value);
	case D3D8TSS_MAGFILTER:
		return pDevice9->SetSamplerState(Stage, D3DSAMP_MAGFILTER, Value);
	case D3D8TSS_MINFILTER:
		return pDevice9->SetSamplerState(Stage, D3DSAMP_MINFILTER, Value);
	case D3D8TSS_MIPFILTER:
		return pDevice9->SetSamplerState(Stage, D3DSAMP_MIPFILTER, Value);
	case D3D8TSS_MIPMAPLODBIAS:
		return pDevice9->SetSamplerState(Stage, D3DSAMP_MIPMAPLODBIAS, Value);
	case D3D8TSS_MAXMIPLEVEL:
		return pDevice9->SetSamplerState(Stage, D3DSAMP_MAXMIPLEVEL, Value);
	case D3D8TSS_MAXANISOTROPY:
		return pDevice9->SetSamplerState(Stage, D3DSAMP_MAXANISOTROPY, Value);
	case D3D8TSS_ADDRESSW:
		return pDevice9->SetSamplerState(Stage, D3DSAMP_ADDRESSW, Value);
	}
	return D3DERR_INVALIDCALL;
}

STDMETHODIMP CDirect3DDevice8::ValidateDevice(THIS_ DWORD* pNumPasses)
{
	return pDevice9->ValidateDevice(pNumPasses);
}

STDMETHODIMP CDirect3DDevice8::GetInfo(THIS_ DWORD DevInfoID, void* pDevInfoStruct, DWORD DevInfoStructSize)
{
	// see http://msdn.microsoft.com/en-us/library/ms889650.aspx
	return S_FALSE;
}

STDMETHODIMP CDirect3DDevice8::SetPaletteEntries(THIS_ UINT PaletteNumber, CONST PALETTEENTRY* pEntries)
{
	return pDevice9->SetPaletteEntries(PaletteNumber, pEntries);
}

STDMETHODIMP CDirect3DDevice8::GetPaletteEntries(THIS_ UINT PaletteNumber, PALETTEENTRY* pEntries)
{
	return pDevice9->GetPaletteEntries(PaletteNumber, pEntries);
}

STDMETHODIMP CDirect3DDevice8::SetCurrentTexturePalette(THIS_ UINT PaletteNumber)
{
	return pDevice9->SetCurrentTexturePalette(PaletteNumber);
}

STDMETHODIMP CDirect3DDevice8::GetCurrentTexturePalette(THIS_ UINT *PaletteNumber)
{
	return pDevice9->GetCurrentTexturePalette(PaletteNumber);
}

STDMETHODIMP CDirect3DDevice8::DrawPrimitive(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	return pDevice9->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

// A curde fix
inline bool isComplexMesh(D3DTRANSFORMSTATETYPE transState, UINT numVertices, UINT primCount)
{
	if (transState==2)
		return (numVertices>128 && primCount>64);
	return true;
}

STDMETHODIMP CDirect3DDevice8::DrawIndexedPrimitive(THIS_ D3DPRIMITIVETYPE Type, UINT minIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	// Disable all Effects
	if (!CTRL::g_EnableEffect)
		return pDevice9->DrawIndexedPrimitive(Type, g_baseVertexIndex, minIndex, NumVertices, startIndex, primCount);

	DWORD alphaRef;
	pDevice9->GetRenderState(D3DRS_ALPHAREF, &alphaRef);

	// invisible models..
	if (g_pTexture9==NULL)
	{
		return pDevice9->DrawIndexedPrimitive(Type, g_baseVertexIndex, minIndex, NumVertices, startIndex, primCount);
	}

#ifdef _DEBUG
	if (DB::g_dbDebugOn)
	{
		DB::saveRenderStatesUsingDrawPrimitiveCount(pDevice9);
		DB::savePrimitiveStatesUsingDrawPrimitiveCount(pDevice9, Type, minIndex, NumVertices, startIndex, primCount, 
														g_StreamNumber, g_Stride, g_Stage, g_State, g_FVFHandle,
														g_baseVertexIndex, zBufferDiscardingEnabled, g_pTexture9, g_pStreamData9, g_pIndexData9);
		DB::saveBackBufferToImage(pDevice9, false);
		DB::logTextureUsingDrawPrimitiveCount(pDevice9, (IDirect3DTexture9*)g_pTexture9);
		DB::logTextureDescUsingDrawPrimitiveCount(pDevice9, (IDirect3DTexture9*)g_pTexture9);
		DB::increaseDrawPrimitiveCount();
		//return pDevice9->DrawIndexedPrimitive(Type, g_baseVertexIndex, minIndex, NumVertices, startIndex, primCount);
	}
#endif

	bool restore = false;
	int currentRenderStage=checkRenderStage(g_Stride, Type, g_FVFHandle, g_State, NumVertices, primCount, (IDirect3DTexture9*)g_pTexture9);
	switch (currentRenderStage)
	{
	case STAGE_UNIT_SHADOW:
		{
			// Disable default unit shadows
			if (CTRL::g_DisableUnitShadow)
			{
				if (CTRL::g_EnableSV)	// If shadowVolume is enabled, keep the original shadow for special models (performance reason).
				{
					if (!SV::IsHeroShadow(pDevice9, g_pStreamData9, g_pIndexData9, startIndex, primCount, g_baseVertexIndex))
						return D3D_OK;
				}
				else
					return D3D_OK;
			}
		}
		break;
	case STAGE_UNIT:
		{
			if (g_Stride == 32 && Type == 4 && g_FVFHandle == 274 && ((DWORD)g_State == 256  || (DWORD)g_State == 17 || (DWORD)g_State == 16 || isComplexMesh(g_State, NumVertices, primCount))) //&& g_DRS[D3DRS_DESTBLEND]!=2)	// filter out non-unit meshes
			{
				HRESULT hr = D3DERR_INVALIDCALL;
				// Render Normal Map
				if (CTRL::g_EnableNP)
				{
					hr = NP::PerformNormalMappping(pDevice9, g_pTexture9, Type, g_baseVertexIndex, minIndex, startIndex,
													g_Stride, NumVertices, primCount, alphaRef, (DWORD)g_State);
				}
				if (CTRL::g_EnableSV && g_DRS[D3DRS_ZWRITEENABLE]==1)	// We only need the solid color mesh, so filter out the rest
				{
					// TODO: Wrap belows inside ShadowVolumeController
					int shwParam = -1;
					shwParam = SV::g_shwTable.getShadowParam(NumVertices, primCount);
					if (shwParam != -1)
					{
						if (FAILED(hr))	// If NormalMapHandler hasn't rendered an object, render it here.
							pDevice9->DrawIndexedPrimitive(Type, g_baseVertexIndex, minIndex, NumVertices, startIndex, primCount);
						SV::GenerateShadow(pDevice9, g_pStreamData9, g_pIndexData9, g_baseVertexIndex, startIndex, NumVertices, primCount, shwParam);
						pDevice9->SetTexture(g_Stage, NULL);
						//SV::RenderShadowVolume(pDevice9);	// for debug...	
						SV::RenderShadow(pDevice9);
						pDevice9->SetTexture(g_Stage, g_pTexture9);								// restore texture
						pDevice9->SetStreamSource(g_StreamNumber, g_pStreamData9, 0, g_Stride);	// restore stream source
						pDevice9->SetFVF(g_FVFHandle);											// restore vertex shader
						hr = D3D_OK;
					}
				}
				// Return if the object has already been rendered
				if (SUCCEEDED(hr))
					return hr;
			}			
		}
		break;
	case STAGE_UI:
		{
			// Draw shadow volume
			if (!SV::g_rendered && CTRL::g_EnableSV)
			{
				SV::g_rendered = true;
				SV::DrawShadow(pDevice9);
				restore = true;
			}
			// Perform Post Process
			if (!PP::g_presented && CTRL::g_EnablePP)
			{
				PP::g_presented = true;
				//pDevice9->EndScene(); // end the scene first
				//pDevice9->BeginScene();
				PP::PerformPostProcess(pDevice9);
				//pDevice9->EndScene();
				//pDevice9->BeginScene();	
				restore = true;
			}
		}
		break;
	default:
		break;
	}

	// Restore
	if (restore)
	{
		pDevice9->SetTexture(g_Stage, g_pTexture9);								// restore texture
		pDevice9->SetStreamSource(g_StreamNumber, g_pStreamData9, 0, g_Stride);	// restore stream source
		pDevice9->SetIndices(g_pIndexData9);									// restore indices
		pDevice9->SetFVF(g_FVFHandle);											// restore vertex shader
	}
	return pDevice9->DrawIndexedPrimitive(Type, g_baseVertexIndex, minIndex, NumVertices, startIndex, primCount);
}

STDMETHODIMP CDirect3DDevice8::DrawPrimitiveUP(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return pDevice9->DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

STDMETHODIMP CDirect3DDevice8::DrawIndexedPrimitiveUP(THIS_ D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertexIndices, UINT PrimitiveCount, CONST void* pIndexData, D3DFORMAT IndexDataFormat, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return pDevice9->DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertexIndices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

STDMETHODIMP CDirect3DDevice8::ProcessVertices(THIS_ UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer8* pDestBuffer, DWORD Flags)
{
	IDirect3DVertexBuffer9* pDestBuffer9 = ((CDirect3DVertexBuffer8*)pDestBuffer)->ToNine();
	return pDevice9->ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer9, NULL, Flags);
}

STDMETHODIMP CDirect3DDevice8::CreateVertexShader(THIS_ CONST DWORD* pDeclaration, CONST DWORD* pFunction, DWORD* pHandle, DWORD Usage)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::SetVertexShader(THIS_ DWORD Handle)
{
	if (Handle & D3DFVF_RESERVED0)
	{
		return E_NOTIMPL;
	}

	HRESULT hr = pDevice9->SetVertexShader(NULL);
	if (SUCCEEDED(hr))
	{
		g_FVFHandle = Handle;
		hr = pDevice9->SetFVF(Handle);
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::GetVertexShader(THIS_ DWORD* pHandle)
{
	return pDevice9->GetFVF(pHandle);
}

STDMETHODIMP CDirect3DDevice8::DeleteVertexShader(THIS_ DWORD Handle)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::SetVertexShaderConstant(THIS_ DWORD Register, CONST void* pConstantData, DWORD ConstantCount)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::GetVertexShaderConstant(THIS_ DWORD Register, void* pConstantData, DWORD ConstantCount)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::GetVertexShaderDeclaration(THIS_ DWORD Handle, void* pData, DWORD* pSizeOfData)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::GetVertexShaderFunction(THIS_ DWORD Handle, void* pData, DWORD* pSizeOfData)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::SetStreamSource(THIS_ UINT StreamNumber, IDirect3DVertexBuffer8* pStreamData, UINT Stride)
{
	IDirect3DVertexBuffer9* pStreamData9 = ((CDirect3DVertexBuffer8*)pStreamData)->ToNine();
	g_Stride=Stride;
	g_StreamNumber=StreamNumber;
	g_pStreamData9=pStreamData9;
	return pDevice9->SetStreamSource(StreamNumber, pStreamData9, 0, Stride);
}

STDMETHODIMP CDirect3DDevice8::GetStreamSource(THIS_ UINT StreamNumber, IDirect3DVertexBuffer8** ppStreamData, UINT* pStride)
{
	IDirect3DVertexBuffer9* pStreamData9 = NULL;
	HRESULT hr = pDevice9->GetStreamSource(StreamNumber, &pStreamData9, NULL, pStride);
	if (SUCCEEDED(hr))
	{
		*ppStreamData = VertexBufferPool.Create(pStreamData9, this);
	}
	return hr;
}


STDMETHODIMP CDirect3DDevice8::SetIndices(THIS_ IDirect3DIndexBuffer8* pIndexData, UINT BaseVertexIndex)
{
	if (BaseVertexIndex > 0x7FFFFFFF) return D3DERR_INVALIDCALL;
	IDirect3DIndexBuffer9* pIndexData9 = ((CDirect3DIndexBuffer8*)pIndexData)->ToNine();
	HRESULT hr = pDevice9->SetIndices(pIndexData9);
	if (SUCCEEDED(hr))
	{
		g_pIndexData9 = pIndexData9;
		g_baseVertexIndex = BaseVertexIndex;
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::GetIndices(THIS_ IDirect3DIndexBuffer8** ppIndexData, UINT* pBaseVertexIndex)
{
	IDirect3DIndexBuffer9* pIndexData9 = NULL;
	HRESULT hr = pDevice9->GetIndices(&pIndexData9);
	if (SUCCEEDED(hr))
	{
		*ppIndexData = IndexBufferPool.Create(pIndexData9, this);
		if (pBaseVertexIndex) *pBaseVertexIndex = g_baseVertexIndex;
	}
	return hr;
}

STDMETHODIMP CDirect3DDevice8::CreatePixelShader(THIS_ CONST DWORD* pFunction, DWORD* pHandle)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::SetPixelShader(THIS_ DWORD Handle)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::GetPixelShader(THIS_ DWORD* pHandle)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::DeletePixelShader(THIS_ DWORD Handle)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::SetPixelShaderConstant(THIS_ DWORD Register, CONST void* pConstantData, DWORD ConstantCount)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::GetPixelShaderConstant(THIS_ DWORD Register, void* pConstantData, DWORD ConstantCount)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::GetPixelShaderFunction(THIS_ DWORD Handle, void* pData, DWORD* pSizeOfData)
{
	return E_NOTIMPL;
}

STDMETHODIMP CDirect3DDevice8::DrawRectPatch(THIS_ UINT Handle, CONST float* pNumSegs, CONST D3DRECTPATCH_INFO* pRectPatchInfo)
{
	return pDevice9->DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

STDMETHODIMP CDirect3DDevice8::DrawTriPatch(THIS_ UINT Handle, CONST float* pNumSegs, CONST D3DTRIPATCH_INFO* pTriPatchInfo)
{
	return pDevice9->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

STDMETHODIMP CDirect3DDevice8::DeletePatch(THIS_ UINT Handle)
{
	return pDevice9->DeletePatch(Handle);
}
