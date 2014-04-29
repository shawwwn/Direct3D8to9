#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "SysUtils.h"

#define IS_INTRESOURCE(_r) ((((ULONG_PTR)(_r)) >> 16) == 0)
#define MAKEINTRESOURCEA(i) ((LPSTR)((ULONG_PTR)((WORD)(i))))
#define MAKEINTRESOURCEW(i) ((LPWSTR)((ULONG_PTR)((WORD)(i))))
#ifdef UNICODE
#define MAKEINTRESOURCE  MAKEINTRESOURCEW
#else
#define MAKEINTRESOURCE  MAKEINTRESOURCEA
#endif // !UNICODE

#define SHADER_BLOOM_H 101      // reference from resource.h

namespace PP{
	struct PostProcess
	{
		ID3DXEffect* m_pEffect;					// Effect object for this technique
		D3DXHANDLE   m_hTPostProcess;			// PostProcess technique handle
		D3DXHANDLE   m_hTexSource;				// Handle to the post-process source textures
		D3DXHANDLE   m_hTexScene;				// Handle to the saved scene texture

		protected:
			HRESULT Init(IDirect3DDevice9* pDevice, UINT resourceRef);
			HRESULT Cleanup();

		public:
			PostProcess();
			~PostProcess();

			//
			// Standard Procedure Functions
			//
			void onCreateDevice(IDirect3DDevice9* pd3dDevice);
			void onLostDevice();
			void onResetDevice(IDirect3DDevice9* pd3dDevice);
			void onDestroy(IDirect3DDevice9* pd3dDevice);
	};


}