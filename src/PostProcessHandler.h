#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "PostProcess.h"

namespace PP{
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

	// backup & set necessary render states for post process
	void backUpStates(IDirect3DDevice9* pd3dDevice);
	// restore previous render states
	void restoreStates(IDirect3DDevice9* pd3dDevice);

}