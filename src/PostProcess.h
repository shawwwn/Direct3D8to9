//========================================
//
//	Base class of post process
//	
//========================================

#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "ShaderResource.h"
#include "SysUtils.h"

namespace PP{
	struct PostProcess
	{
		ID3DXEffect* m_pEffect;					// Effect object for this technique
		D3DXHANDLE   m_hTPostProcess;			// PostProcess technique handle
		D3DXHANDLE   m_hTexSource;				// Handle to the post-process source textures
		D3DXHANDLE   m_hTexScene;				// Handle to the saved scene texture

		protected:
			virtual HRESULT Init(IDirect3DDevice9* pDevice, UINT resourceRef);
			virtual HRESULT Cleanup();

		public:
			PostProcess();
			~PostProcess();

			//
			// Standard Procedure Functions
			//
			virtual void onCreateDevice(IDirect3DDevice9* pd3dDevice);
			virtual void onLostDevice();
			virtual void onResetDevice(IDirect3DDevice9* pd3dDevice);
			virtual void onDestroy(IDirect3DDevice9* pd3dDevice);
	};


}