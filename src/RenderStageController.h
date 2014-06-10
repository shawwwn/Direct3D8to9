#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "GameHook.h"

#define STAGE_UNREDERED				0
#define STAGE_UNKNOWN				1
#define STAGE_TERRAIN				2
#define STAGE_BUIDLING_TERRAIN		3
#define STAGE_FOOT_PRINT			4
#define STAGE_WAR_FOG				5
#define STAGE_UNIT_SHADOW			6
#define STAGE_UNIT					7
#define STAGE_TERRAIN_DECORATION	8
#define STAGE_UNIT_SELECTION_CIRCLE	9
#define STAGE_SCREEN_SELECTION_BOX	10
#define STAGE_WATER					11

#define STAGE_UI_MINOR				30
#define STAGE_UI					31

extern DWORD g_DRS[257];			// RenderState array, indexing from 1-256

void resetRenderStage();
int checkRenderStage(UINT stride, D3DPRIMITIVETYPE primType, DWORD hFVF, DWORD stateType, UINT numVertices, UINT primCount,
                     IDirect3DTexture9* pTexture);