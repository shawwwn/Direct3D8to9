#include "RenderStageController.h"

DWORD g_DRS[257] = {0};

static int g_curRenderStage = STAGE_UNREDERED;

void resetRenderStage()
{
	g_curRenderStage = STAGE_UNREDERED;
}
int getRenderStage()
{
	return g_curRenderStage;
}


inline bool isTerrainStage(UINT stride, D3DPRIMITIVETYPE primType, DWORD hFVF, DWORD stateType, UINT numVertices, UINT primCount)
{
	return (primType==4 && stateType==2 && stride==32 && hFVF==274);
}
inline bool isBuidlingTerrainStage(UINT stride, D3DPRIMITIVETYPE primType, DWORD hFVF, DWORD stateType, UINT numVertices, UINT primCount)
{
	return (g_DRS[D3DRS_LIGHTING]==1 && primType==5 && stateType==17 && stride==36 && hFVF==338 && numVertices*2==primCount+4);
}
inline bool isFootPrintStage(UINT stride, D3DPRIMITIVETYPE primType, DWORD hFVF, DWORD stateType, UINT numVertices, UINT primCount)
{
	return (primType==4 && stateType==17 && stride==36 && hFVF==338 && numVertices==primCount*2);
}
inline bool isWarFogStage(UINT stride, D3DPRIMITIVETYPE primType, DWORD hFVF, DWORD stateType, UINT numVertices, UINT primCount, IDirect3DTexture9* pTexture)
{
	bool warFogTex = false;
	D3DSURFACE_DESC Desc;
	pTexture->GetLevelDesc(0, &Desc);
	if (Desc.Width==16 && Desc.Height==16)
		warFogTex = true;
	return (warFogTex && primType==4 && stateType==17 && stride==32 && hFVF==274);
}
inline bool isUnitShadowStage(UINT stride, D3DPRIMITIVETYPE primType, DWORD hFVF, DWORD stateType, UINT numVertices, UINT primCount)
{
	return (g_DRS[D3DRS_LIGHTING]==0 && primType==5 && stateType==17 && stride==36 && hFVF==338 && numVertices*2==primCount+4);
}
inline bool isUIStage(UINT stride, D3DPRIMITIVETYPE primType, DWORD hFVF, DWORD stateType, UINT numVertices, UINT primCount)
{
	return (primType==5 && stateType==2 && stride==36 && numVertices==4 && primCount==2 && g_DRS[D3DRS_ALPHAREF]==192);
}

int checkRenderStage(UINT stride, D3DPRIMITIVETYPE primType, DWORD hFVF, DWORD stateType, UINT numVertices, UINT primCount, IDirect3DTexture9* pTexture)
{
	switch (g_curRenderStage)
	{
	case STAGE_UNREDERED:
		if (isTerrainStage(stride, primType, hFVF, stateType, numVertices, primCount))
			g_curRenderStage = STAGE_TERRAIN;
		break;
	case STAGE_TERRAIN:
		if (isTerrainStage(stride, primType, hFVF, stateType, numVertices, primCount)) {}
		else if (isBuidlingTerrainStage(stride, primType, hFVF, stateType, numVertices, primCount))
			g_curRenderStage = STAGE_BUIDLING_TERRAIN;
		else if (isFootPrintStage(stride, primType, hFVF, stateType, numVertices, primCount))
			g_curRenderStage = STAGE_FOOT_PRINT;
		else if (isWarFogStage(stride, primType, hFVF, stateType, numVertices, primCount, pTexture))
			g_curRenderStage = STAGE_WAR_FOG;
		else if (isUnitShadowStage(stride, primType, hFVF, stateType, numVertices, primCount))
			g_curRenderStage = STAGE_UNIT_SHADOW;
		break;
	case STAGE_BUIDLING_TERRAIN:
		if (isBuidlingTerrainStage(stride, primType, hFVF, stateType, numVertices, primCount)) {}
		else if (isFootPrintStage(stride, primType, hFVF, stateType, numVertices, primCount))
			g_curRenderStage = STAGE_FOOT_PRINT;
		else if (isWarFogStage(stride, primType, hFVF, stateType, numVertices, primCount, pTexture))
			g_curRenderStage = STAGE_WAR_FOG;
		else if (isUnitShadowStage(stride, primType, hFVF, stateType, numVertices, primCount))
			g_curRenderStage = STAGE_UNIT_SHADOW;
		else
			g_curRenderStage = STAGE_UNIT;
		break;
	case STAGE_FOOT_PRINT:
		if (isFootPrintStage(stride, primType, hFVF, stateType, numVertices, primCount)) {}
		else if (isWarFogStage(stride, primType, hFVF, stateType, numVertices, primCount, pTexture))
			g_curRenderStage = STAGE_WAR_FOG;
		else if (isUnitShadowStage(stride, primType, hFVF, stateType, numVertices, primCount))
			g_curRenderStage = STAGE_UNIT_SHADOW;
		else
			g_curRenderStage = STAGE_UNIT;
		break;
	case STAGE_WAR_FOG:
		if (isWarFogStage(stride, primType, hFVF, stateType, numVertices, primCount, pTexture)) {}
		else if (isUnitShadowStage(stride, primType, hFVF, stateType, numVertices, primCount))
			g_curRenderStage = STAGE_UNIT_SHADOW;
		else
			g_curRenderStage = STAGE_UNIT;
		break;
	case STAGE_UNIT_SHADOW:
		if (isUnitShadowStage(stride, primType, hFVF, stateType, numVertices, primCount)) {}
		else
			g_curRenderStage = STAGE_UNIT;
		break;
	case STAGE_UNIT:
		if (isUIStage(stride, primType, hFVF, stateType, numVertices, primCount))
			g_curRenderStage = STAGE_UI;
		break;
	case STAGE_UI:
		break;
	default:
		break;
	}
	return g_curRenderStage;
}