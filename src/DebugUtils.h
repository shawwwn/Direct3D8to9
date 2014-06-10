#pragma once
#pragma warning(disable:4996)

#pragma comment (lib, "D:\\Program Files\\Microsoft DirectX SDK (August 2009)\\Lib\\x86\\d3dx9.lib")
#pragma comment (lib, "D:\\Program Files\\Microsoft DirectX SDK (August 2009)\\Lib\\x86\\d3d9.lib")
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <fstream>
#include <direct.h>
#if defined(_DEBUG) || defined(NORMALD3D)
#include "debug/RenderStageController.h"
#else
#include "RenderStageController.h"
#endif
namespace DB {
	extern bool g_dbDebugOn;
	extern int g_dbDrawPrimitiveCount;

	bool dirExists(const char* dirPath);
	void createDir(const char* dirPath);
	void savePrimitiveStatesUsingDrawPrimitiveCount(IDirect3DDevice9* pd3dDevice, D3DPRIMITIVETYPE Type, UINT minIndex, UINT NumVertices,
													UINT startIndex, UINT primCount, UINT StreamNumber, UINT Stride, DWORD Stage,
													D3DTRANSFORMSTATETYPE State, DWORD FVFHandle, UINT baseVertexIndex, BOOL zBufferDiscardingEnabled,
													IDirect3DBaseTexture9* pTexture, IDirect3DVertexBuffer9* pVertexData, IDirect3DIndexBuffer9* pIndexData);
	void savePrimitiveStatesToFile(IDirect3DDevice9* pd3dDevice, D3DPRIMITIVETYPE Type, UINT minIndex, UINT NumVertices,
                                   UINT startIndex, UINT primCount, UINT StreamNumber, UINT Stride, DWORD Stage,
								   D3DTRANSFORMSTATETYPE State, DWORD FVFHandle, UINT baseVertexIndex, BOOL zBufferDiscardingEnabled,
								   IDirect3DBaseTexture9* pTexture, IDirect3DVertexBuffer9* pVertexData, IDirect3DIndexBuffer9* pIndexData,
								   char* filename);
	void saveBackBufferToImage(IDirect3DDevice9* pd3dDevice, bool post);
	void restDrawPrimitiveCount();
	void increaseDrawPrimitiveCount();
	void saveRenderStatesUsingDrawPrimitiveCount(IDirect3DDevice9* pd3dDevice);
	void saveRenderStatesToFile(IDirect3DDevice9* pd3dDevice, char* fileName);
	void logTexture(IDirect3DDevice9* pd3dDevice, IDirect3DTexture9* pTexture, char* filename);
	void logTextureUsingDrawPrimitiveCount(IDirect3DDevice9* pd3dDevice, IDirect3DTexture9* pTexture);
	void logTextureDesc(IDirect3DDevice9* pd3dDevice, IDirect3DTexture9* pTexture, char* filename);
	void logTextureDescUsingDrawPrimitiveCount(IDirect3DDevice9* pd3dDevice, IDirect3DTexture9* pTexture);
}