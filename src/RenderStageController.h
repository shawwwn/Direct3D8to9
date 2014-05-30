#include <d3d9.h>
#include <d3dx9.h>

#define STAGE_UNREDERED				0
#define STAGE_TERRAIN				1
#define STAGE_BUIDLING_TERRAIN		2
#define STAGE_FOOT_PRINT			3
#define STAGE_WAR_FOG				4
#define STAGE_UNIT_SHADOW			5
#define STAGE_UNIT					6

#define STAGE_UI					10

extern DWORD g_DRS[257];			// RenderState array, indexing from 1-256

void resetRenderStage();
int getRenderStage();
int checkRenderStage(UINT stride, D3DPRIMITIVETYPE primType, DWORD hFVF, DWORD stateType, UINT numVertices, UINT primCount,
                     IDirect3DTexture9* pTexture);