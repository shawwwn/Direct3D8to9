#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#if defined(_DEBUG) || defined(NORMALD3D)
#include "debug/RenderStageController.h"
#else
#include "RenderStageController.h"
#endif

void GetRotation(D3DMATRIX* pMatrix, float& Yaw, float& Pitch, float& Roll);
// Check render state before setting
inline void SetRenderStateSafe(IDirect3DDevice9* pDevice, D3DRENDERSTATETYPE State, DWORD Value)
{
	if (g_DRS[State]!=Value)
		pDevice->SetRenderState(State, Value);
}