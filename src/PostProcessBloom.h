#pragma once

#include "PostProcess.h"

namespace PP {
	struct PostProcessBloom: public PostProcess
	{
		protected:
			HRESULT initPermanentResources(IDirect3DDevice9* pDevice, UINT width, UINT height);
			HRESULT setupTexture(IDirect3DDevice9* pDevice, UINT width, UINT height);
			HRESULT releaseTemporaryResources();
		public:
			PostProcessBloom();
			~PostProcessBloom();

			IDirect3DTexture9* m_pBrightPassTexture;
			IDirect3DSurface9* m_pBrightPassSurface;
			IDirect3DTexture9* m_pDownsize2xTexture;
			IDirect3DSurface9* m_pDownsize2xSurface;
			IDirect3DTexture9* m_pDownsize4xTexture;
			IDirect3DSurface9* m_pDownsize4xSurface;
			IDirect3DTexture9* m_pBloomHTexture;
			IDirect3DSurface9* m_pBloomHSurface;
			IDirect3DTexture9* m_pBloomVTexture;
			IDirect3DSurface9* m_pBloomVSurface;

			ID3DXEffect* m_pEffectBrightPass;				// bright pass
			D3DXHANDLE   m_hTPostProcessBP;
			D3DXHANDLE   m_hTexSourceBP;
			ID3DXEffect* m_pEffectDownSize2x;				// down size - 2x
			D3DXHANDLE   m_hTPostProcessD2;
			D3DXHANDLE   m_hTexSourceD2;
			ID3DXEffect* m_pEffectDownSize4x;				// down size - 4x
			D3DXHANDLE   m_hTPostProcessD4;
			D3DXHANDLE   m_hTexSourceD4;
			ID3DXEffect* m_pEffectBloomH;					// bloom effect - honrizontal
			D3DXHANDLE   m_hTPostProcessBH;
			D3DXHANDLE   m_hTexSourceBH;
			ID3DXEffect* m_pEffectBloomV;					// bloom effect - vertical
			D3DXHANDLE   m_hTPostProcessBV;
			D3DXHANDLE   m_hTexSourceBV;
			ID3DXEffect* m_pEffectGBlurH;					// gaussian blur - honrizontal
			D3DXHANDLE   m_hTPostProcessGBH;
			D3DXHANDLE   m_hTexSourceGBH;
			ID3DXEffect* m_pEffectGBlurV;					// gaussian blur - vertical
			D3DXHANDLE   m_hTPostProcessGBV;
			D3DXHANDLE   m_hTexSourceGBV;
			//
			// Standard Procedure Functions
			//
			HRESULT Render(IDirect3DTexture9* pSrcColorTexture, IDirect3DSurface9* pDstSurface);
			void onCreateDevice(IDirect3DDevice9* pd3dDevice, UINT width, UINT height);
			void onLostDevice();
			void onResetDevice(IDirect3DDevice9* pd3dDevice, UINT width, UINT height);
			void onDestroy(IDirect3DDevice9* pd3dDevice);
	};
}