#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <math.h>

namespace SV {
	bool IsHeroShadow(IDirect3DDevice9* pd3dDevice, IDirect3DVertexBuffer9* pVertexBuffer, IDirect3DIndexBuffer9* pIndexBuffer, 
						DWORD startIndex, DWORD primCount, DWORD baseVertexIndex);
}