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
		LPD3DXEFFECT m_pEffect;					// Effect object for this technique
		D3DXHANDLE  m_hTPostProcess;			// PostProcess technique handle
		D3DXHANDLE  m_hTexSource;				// Handle to the post-process source textures
		D3DXHANDLE  m_hTexScene;				// Handle to the saved scene texture

		public:
			PostProcess();
			~PostProcess();
			HRESULT Init(LPDIRECT3DDEVICE9 pDevice, UINT resourceRef);
			HRESULT Cleanup();
	};


}