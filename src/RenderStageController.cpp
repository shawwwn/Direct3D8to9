#include "RenderStageController.h"

DWORD g_DRS[257] = {0};

static int g_curRenderStage = STAGE_UNREDERED;

inline bool isUIStage(UINT stride, D3DPRIMITIVETYPE primType, DWORD hFVF, DWORD stateType, UINT numVertices, UINT primCount)
{
	return (primType==5 && stateType==2 && stride==36 && numVertices==4 && primCount==2 && g_DRS[D3DRS_ALPHAREF]==192);
}

void resetRenderStage()
{
	g_curRenderStage = STAGE_UNREDERED;
}

int checkRenderStage(UINT stride, D3DPRIMITIVETYPE primType, DWORD hFVF, DWORD stateType, UINT numVertices, UINT primCount, IDirect3DTexture9* pTexture)
{
	HOOK::RENDER_STATE rs = HOOK::getCurrentRenderState();
	if (rs == HOOK::STATE_MAYJOR_UI)
	{
		if (isUIStage(stride, primType, hFVF, stateType, numVertices, primCount))
			return STAGE_UI;
		return STAGE_UNKNOWN;
	}

	if (rs != HOOK::STATE_UNIT_AND_EFFECT)
		return STAGE_UNKNOWN;

	switch (HOOK::g_CurrentRenderTarget)
	{
	case 0x01:
		return STAGE_TERRAIN;
		break;
	case 0x02:
		return STAGE_WAR_FOG;
		break;
	case 0x03:
		return STAGE_UNIT_SHADOW;
		break;
	case 0x07:
		return STAGE_UNIT_SELECTION_CIRCLE;
		break;
	case 0x09:
		return STAGE_FOOT_PRINT;
		break;
	case 0x13:
		return STAGE_BUIDLING_TERRAIN;
		break;
	case 0x0A:
		return STAGE_TERRAIN_DECORATION;
		break;
	case 0x0B:
		if (HOOK::g_CurrentRenderType == HOOK::D3D_MESH)
			return STAGE_UNIT;
		break;
	case 0x0E:
		return STAGE_WATER;
		break;
	case 0x0F:
		return STAGE_SCREEN_SELECTION_BOX;
		break;
	default:
		return STAGE_UNKNOWN;
		break;
	}
	return STAGE_UNKNOWN;
}