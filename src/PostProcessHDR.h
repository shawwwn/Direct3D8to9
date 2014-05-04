#pragma once

#include "PostProcess.h"

namespace PP {
	struct PostProcessHDR: public PostProcess
	{
		protected:
			HRESULT initPermanentResources(IDirect3DDevice9* pDevice, UINT width, UINT height);
			HRESULT setupTexture(IDirect3DDevice9* pDevice, UINT width, UINT height);
			HRESULT releaseTemporaryResources();
		public:
			PostProcessHDR();
			~PostProcessHDR();

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