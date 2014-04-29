#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "PostPRocess.h"
#include "PostProcessBloom.h"

namespace PP{
	#define MAX_POST_PROCESS_COUNT 5
	enum RenderMenthod { RENDER_TO_TEXTURE, RENDER_TO_BACKBUFFER };
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

	extern IDirect3DVertexBuffer9* g_pVB;

	extern IDirect3DVertexDeclaration9* g_pVertDeclPP;
	extern IDirect3DTexture9* g_pSourceRT_Texture;
	extern IDirect3DTexture9* g_pTargetRT_Texture;

	extern PostProcess* g_pPostProcessChain[MAX_POST_PROCESS_COUNT];
	extern int g_post_process_count;

	extern bool g_presented;

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
	HRESULT Init(IDirect3DDevice9* pd3dDevice);
	HRESULT SetupVertexBuffer(IDirect3DDevice9* pd3dDevice);
	HRESULT PerformPostProcess(IDirect3DDevice9* pd3dDevice, RenderMenthod method);
	IDirect3DSurface9* RenderToTexture(IDirect3DDevice9* pd3dDevice, IDirect3DTexture9* pTexture);
	IDirect3DSurface9* RenderToBackBuffer(IDirect3DDevice9* pd3dDevice);
	// backup & set necessary render states for post process
	void backupStates(IDirect3DDevice9* pd3dDevice);
	// restore previous render states
	void restoreStates(IDirect3DDevice9* pd3dDevice);

	//
	// Standard Procedure Functions
	//
	void onCreateDevice(IDirect3DDevice9* pd3dDevice);
	void onLostDevice();
	void onResetDevice(IDirect3DDevice9* pd3dDevice);
	void onDestroy(IDirect3DDevice9* pd3dDevice);
}