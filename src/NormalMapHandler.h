#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "TextureTable.h"

namespace NP {

	extern TextureTable g_texTable;
	
	// init global settings
	void InitGlobals();
	// query texture and perform normal mapping
	HRESULT PerformNormalMappping(IDirect3DDevice9* pd3dDevice, IDirect3DBaseTexture9* pBaseTexture,
                                  DWORD dwKey1, DWORD dwKey2, DWORD dwKey3, DWORD dwKey4);
}