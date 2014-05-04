#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "SysUtils.h"

namespace HDR {
	extern IDirect3DDevice9* m_pDevice;
	extern IDirect3DTexture9* g_pHDRTexture;
	extern IDirect3DSurface9* g_pHDRSurface;
	extern IDirect3DSurface9* g_pBackBuffer;
	extern UINT g_deviceWidth;
	extern UINT g_deviceHeight;

	bool isUsable();

	//
	// Standard Procedure Functions
	//
	void onCreateDevice(IDirect3DDevice9* pd3dDevice);
	void onBeginScene();
	void onEndScene();
	void onLostDevice();
	void onResetDevice(IDirect3DDevice9* pd3dDevice);
}
