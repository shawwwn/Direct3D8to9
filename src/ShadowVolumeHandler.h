#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "SysUtils.h"
#include "ShadowVolume.h"

namespace SV {
	extern bool g_Enable;
	extern LPDIRECT3DVERTEXBUFFER9 g_pBigSquareVB;
	extern ShadowVolume g_HumBaseShadow;
	extern UINT g_deviceHeight;
	extern UINT g_deviceWidth;

	void GenerateShadow(IDirect3DDevice9* pd3dDevice, IDirect3DVertexBuffer9* pVertexBuffer, IDirect3DIndexBuffer9* pIndexBuffer, DWORD startIndex, DWORD primCount, DWORD baseVertexIndex, D3DMATRIX* pMatrix);
	void RenderShadowVolume(IDirect3DDevice9* pd3dDevice);
	HRESULT RenderShadow(IDirect3DDevice9* pd3dDevice);
	HRESULT DrawShadow(IDirect3DDevice9* pd3dDevice);

	//
	// Standard Procedure Functions
	//
	void onCreateDevice(IDirect3DDevice9* pd3dDevice);
	void onLostDevice();
	void onResetDevice(IDirect3DDevice9* pd3dDevice);
	void onDestroy(IDirect3DDevice9* pd3dDevice);
}
