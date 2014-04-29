#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "TextureTable.h"
#include "NormalMapExceptionHandler.h"

namespace NP {
	#define NORMAL_AMPLITUDE -100
	extern TextureTable g_texTable;
	extern DWORD g_AlphaValue;
	extern DWORD g_NormalTextureAlpha;

	extern DWORD g_pColorArg1_0;
	extern DWORD g_pColorOp_0;
	extern DWORD g_pColorArg2_0;
	extern DWORD g_pAlphaOp_0;
	extern DWORD g_pAlphaArg1_0;
	extern DWORD g_pAlphaArg2_0;
	extern DWORD g_pTexCoordIndex_0;

	extern DWORD g_AlphaTestEnable;
	extern DWORD g_AlphaBlendEnable;
	extern DWORD g_SrcBlend;
	extern DWORD g_DestBlend;
	extern DWORD g_TextureFactor;


	// Init global settings
	void initialize(IDirect3DDevice9* pd3dDevice);
	void onCreateDevice(IDirect3DDevice9* pd3dDevice);
	void onLostDevice();
	void onResetDevice(IDirect3DDevice9* pd3dDevice);
	void onDestroy(IDirect3DDevice9* pd3dDevice);
	// Query texture and perform normal mapping
	HRESULT PerformNormalMappping(IDirect3DDevice9* pd3dDevice, IDirect3DBaseTexture9* pBaseTexture,
                                  D3DPRIMITIVETYPE Type, UINT baseVertexIndex, UINT minIndex, UINT startIndex,
                                  UINT Stride, UINT NumVertices, UINT primCount, DWORD AlphaRef, DWORD TransformStateType);
	// Backup TextureStageStates
	void backupTextureStageStates(IDirect3DDevice9* pd3dDevice);
	// Restore TextureStageStates
	void restoreTextureStageStates(IDirect3DDevice9* pd3dDevice);
	// Backup RenderStates
	void backupRenderStates(IDirect3DDevice9* pd3dDevice);
	// Restore RenderStates
	void restoreRenderStates(IDirect3DDevice9* pd3dDevice);
}