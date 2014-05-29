#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "SysUtils.h"
#include "EffectController.h"
#include "ShadowVolume.h"
#include "ShadowTable.h"

namespace SV {
	const D3DXVECTOR3 wc3Light(0.675f, 0.406f, -0.616f);	// WC3's default directional light in most scenerios
	const D3DXVECTOR3 wc3Light_fly(0, 0, -0.616f);			// for flying units

	extern ShadowTable g_shwTable;
	extern bool g_rendered;
	extern LPDIRECT3DVERTEXBUFFER9 g_pBigSquareVB;
	extern ShadowVolume g_HumBaseShadow;
	extern UINT g_deviceHeight;
	extern UINT g_deviceWidth;
	extern bool g_enterUnitShadow;
	extern bool g_finishUnitShadow;

	void InitShadowTable(ShadowTable& table);
	void GenerateShadow(IDirect3DDevice9* pd3dDevice, IDirect3DVertexBuffer9* pVertexBuffer, IDirect3DIndexBuffer9* pIndexBuffer, 
						DWORD startIndex, DWORD primCount, DWORD baseVertexIndex, int inversion);
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
