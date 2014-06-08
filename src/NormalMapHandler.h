#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#ifdef _DEBUG
#include "debug/NormalTable.h"
#else
#include "NormalTable.h"
#endif
#include "DxUtils.h"
#include "NormalMapExceptionHandler.h"

namespace NP {
	#define NORMAL_AMPLITUDE -100
	extern NormalTable g_npTable;

	// Init global settings
	HRESULT Init(IDirect3DDevice9* pd3dDevice);
	// Query texture and perform normal mapping
	HRESULT PerformNormalMappping(IDirect3DDevice9* pd3dDevice, IDirect3DBaseTexture9* pBaseTexture,
                                  D3DPRIMITIVETYPE Type, UINT baseVertexIndex, UINT minIndex, UINT startIndex,
                                  UINT Stride, UINT NumVertices, UINT primCount, DWORD AlphaRef, DWORD TransformStateType);

	//
	// Standard Procedure Functions
	//
	void onCreateDevice(IDirect3DDevice9* pd3dDevice);
	void onLostDevice();
	void onResetDevice(IDirect3DDevice9* pd3dDevice);
	void onDestroy(IDirect3DDevice9* pd3dDevice);
}