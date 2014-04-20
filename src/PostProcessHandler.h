#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "PostProcess.h"

namespace PP{
	extern DWORD dwZEnable;
	extern DWORD dwZWriteEnable;
	extern DWORD dwLocalViewer;
	extern DWORD dwAlphaTestEnable;
	extern DWORD dwCullMode;
	extern DWORD dwAlphaBlendEnable;
	extern DWORD dwZFunc;
	extern DWORD dwSrcBlend;
	extern DWORD dwDestBlend;
	extern DWORD dwFogEnable;
	extern DWORD dwLighting;

	extern UINT g_deviceWidth;
	extern UINT g_deviceHeight;

	extern IDirect3DVertexDeclaration9* g_pVertDeclPP;
	extern IDirect3DTexture9* g_pSourceRT_Texture;
	extern IDirect3DTexture9* g_pTargetRT_Texture;

	extern PostProcess g_PostProcessChain[1];

	// This is the vertex format used with the quad during post-process.
	struct PPVERT
	{
		float x, y, z, rhw;
		float tu, tv;       // Texcoord for post-process source
		float tu2, tv2;     // Texcoord for the original scene

		const static D3DVERTEXELEMENT9 Decl[4];
	};

	//
	// Function Declaration
	//

	HRESULT InitGobals(IDirect3DDevice9* pd3dDevice);
	HRESULT PerformPostProcess(IDirect3DDevice9* pd3dDevice);
	IDirect3DSurface9* RenderToTexture(IDirect3DDevice9* pd3dDevice, IDirect3DTexture9* pTexture);
	IDirect3DSurface9* RenderToBackBuffer(IDirect3DDevice9* pd3dDevice);

	// backup & set necessary render states for post process
	void backupStates(IDirect3DDevice9* pd3dDevice);
	// restore previous render states
	void restoreStates(IDirect3DDevice9* pd3dDevice);
}