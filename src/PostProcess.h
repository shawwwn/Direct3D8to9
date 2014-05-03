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
	// This is the vertex format used with the quad during post-process.
	struct PPVERT
	{
		float x, y, z, rhw;
		float tu, tv;       // Texcoord for post-process source
		float tu2, tv2;     // Texcoord for the original scene

		const static D3DVERTEXELEMENT9 PPDecl[4];
	};

	struct PostProcess
	{
		protected:
			virtual HRESULT initPermanentResources(IDirect3DDevice9* pDevice, UINT width, UINT height);
			virtual HRESULT initTemporaryResources(IDirect3DDevice9* pDevice, UINT width, UINT height);
			virtual	HRESULT setupShader(ID3DXEffect* pEffect);
			virtual HRESULT setupTexture(IDirect3DDevice9* pDevice, UINT width, UINT height);
			virtual HRESULT releaseTemporaryResources();
			virtual HRESULT releasePermanentResources();

		public:
			PostProcess();
			~PostProcess();

			UINT m_deviceWidth;						// Device width
			UINT m_deviceHeight;					// Device height
			IDirect3DDevice9* m_pDevice;			// Device pointer
			ID3DXEffect* m_pEffect;					// Effect object for this technique
			D3DXHANDLE   m_hTPostProcess;			// PostProcess technique handle
			D3DXHANDLE   m_hTexSource;				// Handle to the post-process source textures
			D3DXHANDLE   m_hTexScene;				// Handle to the saved scene texture
			IDirect3DVertexBuffer9* m_pVB;
			IDirect3DVertexDeclaration9* m_pVertDeclPP;

			//
			// Standard Procedure Functions
			//
			virtual HRESULT Render(IDirect3DTexture9* pSrcColorTexture, IDirect3DSurface9* pDstSurface);
			virtual void onCreateDevice(IDirect3DDevice9* pd3dDevice, UINT width, UINT height);
			virtual void onLostDevice();
			virtual void onResetDevice(IDirect3DDevice9* pd3dDevice, UINT width, UINT height);
			virtual void onDestroy(IDirect3DDevice9* pd3dDevice);
	};


}