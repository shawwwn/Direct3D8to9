#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "SysUtils.h"
#include "DxUtils.h"
#include "EffectController.h"
#include "ShadowVolume.h"
#if _DEBUG
#include "debug/ShadowTable.h"
#else
#include "ShadowTable.h"
#endif

namespace SV {
	const D3DXVECTOR3 wc3Light(0.675f, 0.406f, -0.616f);	// WC3's default directional light in most scenerios
	const D3DXVECTOR3 wc3Light_fly(0, 0, -0.616f);			// for flying units

	extern IDirect3DDevice9* m_pDevice;
	extern ShadowTable g_shwTable;
	extern bool g_rendered;
	extern LPDIRECT3DVERTEXBUFFER9 g_pBigSquareVB;
	extern ShadowVolume g_baseShadow;
	extern UINT g_deviceHeight;
	extern UINT g_deviceWidth;

	void GenerateShadow(IDirect3DDevice9* pd3dDevice, IDirect3DVertexBuffer9* pVertexBuffer, IDirect3DIndexBuffer9* pIndexBuffer,
						DWORD baseVertexIndex, DWORD startIndex,
						DWORD numVertices, DWORD primCount,
						int inversion);
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
