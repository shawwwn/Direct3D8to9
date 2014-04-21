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

	void saveBackBufferToImage(IDirect3DDevice9* pd3dDevice, bool post);
	void restDrawPrimitiveCount();
	void increaseDrawPrimitiveCount();
	void saveRenderStatesUsingDrawPrimitiveCount(IDirect3DDevice9* pd3dDevice);
	void saveRenderStatesToFile(IDirect3DDevice9* pd3dDevice, char* fileName);
}