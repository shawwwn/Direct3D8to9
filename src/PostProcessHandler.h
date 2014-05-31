#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include "DxUtils.h"
#include "PostPRocess.h"
#include "PostProcessBloom.h"
#include "PostProcessSMAA.h"
#include "PostProcessHDR.h"

//#define RENDER_TO_BACK_BUFFER	// kinda buggy..

namespace PP{
	#define MAX_POST_PROCESS_COUNT 5

	extern IDirect3DDevice9* m_pDevice;
	extern UINT g_deviceWidth;
	extern UINT g_deviceHeight;

	extern IDirect3DTexture9* g_pSourceRT_Texture;
	extern IDirect3DSurface9* g_pSourceRT_Surface;
	extern IDirect3DTexture9* g_pTargetRT_Texture;
	extern IDirect3DSurface9* g_pTargetRT_Surface;

	extern PostProcess* g_pPostProcessChain[MAX_POST_PROCESS_COUNT];
	extern int g_post_process_count;

	extern bool g_presented;

	//
	// Function Declaration
	//
	HRESULT initTemporaryResources(IDirect3DDevice9* pd3dDevice);
	HRESULT initPermanentResources(IDirect3DDevice9* pd3dDevice);
	HRESULT releaseTemporaryResources();
	HRESULT releasePermanentResources();
	void setupScreenDimensions(IDirect3DDevice9* pd3dDevice);
	void swapTextures();
	HRESULT PerformPostProcess(IDirect3DDevice9* pd3dDevice);

	//
	// Standard Procedure Functions
	//
	void onCreateDevice(IDirect3DDevice9* pd3dDevice);
	void onLostDevice();
	void onResetDevice(IDirect3DDevice9* pd3dDevice);
	void onDestroy(IDirect3DDevice9* pd3dDevice);
}