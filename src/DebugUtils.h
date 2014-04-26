#pragma once
#pragma warning(disable:4996)

#pragma comment (lib, "D:\\Program Files\\Microsoft DirectX SDK (August 2009)\\Lib\\x86\\d3dx9.lib")
#pragma comment (lib, "D:\\Program Files\\Microsoft DirectX SDK (August 2009)\\Lib\\x86\\d3d9.lib")
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <fstream>

namespace DB {
	extern bool g_dbDebugOn;
	extern int g_dbDrawPrimitiveCount;

	void savePrimitiveStatesUsingDrawPrimitiveCount(D3DPRIMITIVETYPE Type, UINT minIndex, UINT NumVertices, UINT startIndex, UINT primCount, 
                                UINT StreamNumber, UINT Stride, DWORD Stage, D3DTRANSFORMSTATETYPE State, DWORD FVFHandle,
							    UINT baseVertexIndex, BOOL zBufferDiscardingEnabled, IDirect3DBaseTexture9* g_pTexture9);
	void savePrimitiveStatesToFile(D3DPRIMITIVETYPE Type, UINT minIndex, UINT NumVertices, UINT startIndex, UINT primCount, 
                                UINT StreamNumber, UINT Stride, DWORD Stage, D3DTRANSFORMSTATETYPE State, DWORD FVFHandle,
							    UINT baseVertexIndex, BOOL zBufferDiscardingEnabled, IDirect3DBaseTexture9* g_pTexture9,
								char* filename);
	void saveBackBufferToImage(IDirect3DDevice9* pd3dDevice, bool post);
	void restDrawPrimitiveCount();
	void increaseDrawPrimitiveCount();
	void saveRenderStatesUsingDrawPrimitiveCount(IDirect3DDevice9* pd3dDevice);
	void saveRenderStatesToFile(IDirect3DDevice9* pd3dDevice, char* fileName);
	void logTextureDesc(IDirect3DDevice9* pd3dDevice, IDirect3DTexture9* pTexture, char* filename);
}