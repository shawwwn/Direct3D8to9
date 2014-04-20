#pragma once

#include <d3d9.h>
#include <d3dx9.h>

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
			HRESULT Init(LPDIRECT3DDEVICE9 pDevice, LPCTSTR pSrcFile);
			HRESULT Cleanup();
	};


}