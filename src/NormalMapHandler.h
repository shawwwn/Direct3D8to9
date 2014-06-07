#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "NormalTable.h"
#include "DxUtils.h"
#include "ExceptionalMeshTable.h"
#include "NormalMapExceptionHandler.h"

namespace NP {
	#define NORMAL_AMPLITUDE -100
	#define MAX_EXCEPTIONAL_MESH_COUNT 10
	extern TextureTable g_npTable;
	extern const ExceptionalMeshKeys g_exceptionalMeshes[MAX_EXCEPTIONAL_MESH_COUNT];
	extern UINT g_NumVertices_last;
	extern UINT g_PrimCount_last;
	extern IDirect3DBaseTexture9* g_pBaseTexture_last;
	extern TextureItem* g_pItem_last;
	extern DWORD g_dwAlphaValue;
	extern DWORD g_dwNormalTextureAlpha;

	extern DWORD g_dwColorArg1_0;
	extern DWORD g_dwColorOp_0;
	extern DWORD g_dwColorArg2_0;
	extern DWORD g_dwAlphaOp_0;
	extern DWORD g_dwAlphaArg1_0;
	extern DWORD g_dwAlphaArg2_0;
	extern DWORD g_dwTexCoordIndex_0;

	// Is mesh a exceptional mesh
	bool IsExceptionalMesh(UINT numVertices, UINT primCount, DWORD srcBlend, DWORD destBlend, DWORD alphaRef);
	// Initialize normal map texture table
	void InitTextureTable(TextureTable &texTable);
	// Init global settings
	HRESULT Init(IDirect3DDevice9* pd3dDevice);
	// Query texture and perform normal mapping
	HRESULT PerformNormalMappping(IDirect3DDevice9* pd3dDevice, IDirect3DBaseTexture9* pBaseTexture,
                                  D3DPRIMITIVETYPE Type, UINT baseVertexIndex, UINT minIndex, UINT startIndex,
                                  UINT Stride, UINT NumVertices, UINT primCount, DWORD AlphaRef, DWORD TransformStateType);
	// Backup TextureStageStates
	void backupTextureStageStates(IDirect3DDevice9* pd3dDevice);
	// Restore TextureStageStates
	void restoreTextureStageStates(IDirect3DDevice9* pd3dDevice);

	//
	// Standard Procedure Functions
	//
	void onCreateDevice(IDirect3DDevice9* pd3dDevice);
	void onLostDevice();
	void onResetDevice(IDirect3DDevice9* pd3dDevice);
	void onDestroy(IDirect3DDevice9* pd3dDevice);
}