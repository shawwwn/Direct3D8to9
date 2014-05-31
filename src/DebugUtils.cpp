#include "DebugUtils.h"

namespace DB {
	// Variables
	bool g_dbDebugOn=false;
	int g_dbDrawPrimitiveCount=0;

	// D3D Debug Functions
	bool dirExists(const char* dirPath)
	{
		DWORD ftyp = GetFileAttributesA(dirPath);
		if (ftyp == INVALID_FILE_ATTRIBUTES)
			return false;  //something is wrong with your path!
		if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
			return true;   // this is a directory!
		return false;    // this is not a directory!
	}
	void createDir(const char* dirPath)
	{
		if (!dirExists(dirPath))
			mkdir(dirPath);
	}
	void savePrimitiveStatesUsingDrawPrimitiveCount(IDirect3DDevice9* pd3dDevice, D3DPRIMITIVETYPE Type, UINT minIndex, UINT NumVertices,
													UINT startIndex, UINT primCount, UINT StreamNumber, UINT Stride, DWORD Stage,
													D3DTRANSFORMSTATETYPE State, DWORD FVFHandle, UINT baseVertexIndex, BOOL zBufferDiscardingEnabled,
													IDirect3DBaseTexture9* pTexture, IDirect3DVertexBuffer9* pVertexData, IDirect3DIndexBuffer9* pIndexData)
	{
		char fullPath[64]="pics/";
		char fileName[16];
		char fileSuffix[16]="_prim.txt";
		createDir(fullPath);
		itoa(g_dbDrawPrimitiveCount, fileName, 10);
		strcat(fullPath, fileName);
		strcat(fullPath, fileSuffix);
		savePrimitiveStatesToFile(pd3dDevice, Type, minIndex, NumVertices, startIndex, primCount, 
			                   StreamNumber, Stride, Stage, State, FVFHandle,
							   baseVertexIndex, zBufferDiscardingEnabled, pTexture, pVertexData, pIndexData,
							   fullPath);
	}
	void savePrimitiveStatesToFile(IDirect3DDevice9* pd3dDevice, D3DPRIMITIVETYPE Type, UINT minIndex, UINT NumVertices,
                                   UINT startIndex, UINT primCount, UINT StreamNumber, UINT Stride, DWORD Stage,
								   D3DTRANSFORMSTATETYPE State, DWORD FVFHandle, UINT baseVertexIndex, BOOL zBufferDiscardingEnabled,
								   IDirect3DBaseTexture9* pTexture, IDirect3DVertexBuffer9* pVertexData, IDirect3DIndexBuffer9* pIndexData,
								   char* filename)
	{
		std::ofstream myfile;
		myfile.open (filename);
		myfile << "D3DPRIMITIVETYPE: " << (UINT)Type << "\n";
		myfile << "MinIndex: " << minIndex << "\n";
		myfile << "NumVertices: " << NumVertices << "\n";
		myfile << "StartIndex: " << startIndex << "\n";
		myfile << "PrimCount: " << primCount << "\n";
		myfile << "StreamNumber: " << StreamNumber << "\n";
		myfile << "Stride: " << Stride << "\n";
		myfile << "Stage: " << Stage << "\n";
		myfile << "D3DTRANSFORMSTATETYPE: " << (UINT)State << "\n";
		myfile << "FVFHandle: " << FVFHandle << "\n";
		myfile << "BaseVertexIndex: " << baseVertexIndex << "\n";
		myfile << "zBufferDiscardingEnabled: " << zBufferDiscardingEnabled << "\n";
		myfile << "pTexture9: " << (UINT)pTexture << "\n";
		myfile << "pVertexBuffer: " << (UINT)pVertexData << "\n";
		myfile << "pIndexBuffer: " << (UINT)pIndexData << "\n";
		myfile << "RenderStage: " << checkRenderStage(Stride, Type, FVFHandle, State, NumVertices, primCount, (IDirect3DTexture9*)pTexture) << "\n";
		myfile.close();
	}
	void saveBackBufferToImage(IDirect3DDevice9* pd3dDevice, bool post)
	{
		char fullPath[64]="pics/";
		char fileName[16];
		char postSuffix[8]="_end";
		char preSuffix[8]="_begin";
		char fileSuffix[8]=".jpg";
		createDir(fullPath);
		itoa(g_dbDrawPrimitiveCount, fileName, 10);
		strcat(fullPath, fileName);
		if (post)
			strcat(fullPath, postSuffix);
		else
			strcat(fullPath, preSuffix);
		strcat(fullPath, fileSuffix);
		// Save current screen
		IDirect3DSurface9* backBuffer;
		pd3dDevice->GetRenderTarget(0, &backBuffer);
		D3DXSaveSurfaceToFile(fullPath, D3DXIFF_JPG, backBuffer, NULL, NULL);
		backBuffer->Release();
	}
	void restDrawPrimitiveCount()
	{
		g_dbDrawPrimitiveCount=0;
	}
	void increaseDrawPrimitiveCount()
	{
		g_dbDrawPrimitiveCount++;
	}
	void saveRenderStatesUsingDrawPrimitiveCount(IDirect3DDevice9* pd3dDevice)
	{
		char fullPath[64]="pics/";
		char fileName[16];
		char fileSuffix[8]=".txt";
		createDir(fullPath);
		itoa(g_dbDrawPrimitiveCount, fileName, 10);
		strcat(fullPath, fileName);
		strcat(fullPath, fileSuffix);
		saveRenderStatesToFile(pd3dDevice, fullPath);
	}
	void saveRenderStatesToFile(IDirect3DDevice9* pd3dDevice, char* filename)
	{
		  std::ofstream myfile;
		  myfile.open (filename);
		  DWORD value;
		  pd3dDevice->GetRenderState(D3DRS_ZENABLE, &value);
		  myfile << "D3DRS_ZENABLE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_FILLMODE, &value);
		  myfile << "D3DRS_FILLMODE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_SHADEMODE, &value);
		  myfile << "D3DRS_SHADEMODE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_ZWRITEENABLE, &value);
		  myfile << "D3DRS_ZWRITEENABLE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_ALPHATESTENABLE, &value);
		  myfile << "D3DRS_ALPHATESTENABLE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_LASTPIXEL, &value);
		  myfile << "D3DRS_LASTPIXEL: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_SRCBLEND, &value);
		  myfile << "D3DRS_SRCBLEND: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_DESTBLEND, &value);
		  myfile << "D3DRS_DESTBLEND: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_CULLMODE, &value);
		  myfile << "D3DRS_CULLMODE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_ZFUNC, &value);
		  myfile << "D3DRS_ZFUNC: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_ALPHAREF, &value);
		  myfile << "D3DRS_ALPHAREF: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_ALPHAFUNC, &value);
		  myfile << "D3DRS_ALPHAFUNC: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_DITHERENABLE, &value);
		  myfile << "D3DRS_DITHERENABLE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_ALPHABLENDENABLE, &value);
		  myfile << "D3DRS_ALPHABLENDENABLE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_FOGENABLE, &value);
		  myfile << "D3DRS_FOGENABLE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_SPECULARENABLE, &value);
		  myfile << "D3DRS_SPECULARENABLE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_FOGCOLOR, &value);
		  myfile << "D3DRS_FOGCOLOR: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_FOGTABLEMODE, &value);
		  myfile << "D3DRS_FOGTABLEMODE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_FOGSTART, &value);
		  myfile << "D3DRS_FOGSTART: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_FOGEND, &value);
		  myfile << "D3DRS_FOGEND: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_FOGDENSITY, &value);
		  myfile << "D3DRS_FOGDENSITY: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_RANGEFOGENABLE, &value);
		  myfile << "D3DRS_RANGEFOGENABLE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_STENCILENABLE, &value);
		  myfile << "D3DRS_STENCILENABLE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_STENCILFAIL, &value);
		  myfile << "D3DRS_STENCILFAIL: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_STENCILZFAIL, &value);
		  myfile << "D3DRS_STENCILZFAIL: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_STENCILPASS, &value);
		  myfile << "D3DRS_STENCILPASS: " << value << "\n";
	  
		  pd3dDevice->GetRenderState(D3DRS_STENCILFUNC, &value);
		  myfile << "D3DRS_STENCILFUNC: " << value << "\n";
	  
		  pd3dDevice->GetRenderState(D3DRS_STENCILREF, &value);
		  myfile << "D3DRS_STENCILREF: " << value << "\n";
	  	  
		  pd3dDevice->GetRenderState(D3DRS_STENCILMASK, &value);
		  myfile << "D3DRS_STENCILMASK: " << value << "\n";
	  	  
		  pd3dDevice->GetRenderState(D3DRS_STENCILWRITEMASK, &value);
		  myfile << "D3DRS_STENCILWRITEMASK: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_TEXTUREFACTOR, &value);
		  myfile << "D3DRS_TEXTUREFACTOR: " << value << "\n";
	  
		  pd3dDevice->GetRenderState(D3DRS_WRAP0, &value);
		  myfile << "D3DRS_WRAP0: " << value << "\n";
	  
		  pd3dDevice->GetRenderState(D3DRS_WRAP1, &value);
		  myfile << "D3DRS_WRAP1: " << value << "\n";
	  
		  pd3dDevice->GetRenderState(D3DRS_WRAP2, &value);
		  myfile << "D3DRS_WRAP2: " << value << "\n";
	  
		  pd3dDevice->GetRenderState(D3DRS_WRAP3, &value);
		  myfile << "D3DRS_WRAP3: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_WRAP4, &value);
		  myfile << "D3DRS_WRAP4: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_WRAP5, &value);
		  myfile << "D3DRS_WRAP5: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_WRAP6, &value);
		  myfile << "D3DRS_WRAP6: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_WRAP7, &value);
		  myfile << "D3DRS_WRAP7: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_CLIPPING, &value);
		  myfile << "D3DRS_CLIPPING: " << value << "\n";
	  
		  pd3dDevice->GetRenderState(D3DRS_LIGHTING, &value);
		  myfile << "D3DRS_LIGHTING: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_AMBIENT, &value);
		  myfile << "D3DRS_AMBIENT: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_FOGVERTEXMODE, &value);
		  myfile << "D3DRS_FOGVERTEXMODE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_COLORVERTEX, &value);
		  myfile << "D3DRS_COLORVERTEX: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_LOCALVIEWER, &value);
		  myfile << "D3DRS_LOCALVIEWER: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_NORMALIZENORMALS, &value);
		  myfile << "D3DRS_NORMALIZENORMALS: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, &value);
		  myfile << "D3DRS_DIFFUSEMATERIALSOURCE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_SPECULARMATERIALSOURCE, &value);
		  myfile << "D3DRS_SPECULARMATERIALSOURCE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, &value);
		  myfile << "D3DRS_EMISSIVEMATERIALSOURCE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_VERTEXBLEND, &value);
		  myfile << "D3DRS_VERTEXBLEND: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_CLIPPLANEENABLE, &value);
		  myfile << "D3DRS_CLIPPLANEENABLE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_POINTSIZE, &value);
		  myfile << "D3DRS_POINTSIZE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_POINTSIZE_MIN, &value);
		  myfile << "D3DRS_POINTSIZE_MIN: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_POINTSPRITEENABLE, &value);
		  myfile << "D3DRS_POINTSPRITEENABLE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_POINTSCALEENABLE, &value);
		  myfile << "D3DRS_POINTSCALEENABLE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_POINTSCALE_A, &value);
		  myfile << "D3DRS_POINTSCALE_A: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_POINTSCALE_B, &value);
		  myfile << "D3DRS_POINTSCALE_B: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_POINTSCALE_C, &value);
		  myfile << "D3DRS_POINTSCALE_C: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_MULTISAMPLEANTIALIAS, &value);
		  myfile << "D3DRS_MULTISAMPLEANTIALIAS: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_MULTISAMPLEMASK, &value);
		  myfile << "D3DRS_MULTISAMPLEMASK: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_PATCHEDGESTYLE, &value);
		  myfile << "D3DRS_PATCHEDGESTYLE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_DEBUGMONITORTOKEN, &value);
		  myfile << "D3DRS_DEBUGMONITORTOKEN: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_POINTSIZE_MAX, &value);
		  myfile << "D3DRS_POINTSIZE_MAX: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_INDEXEDVERTEXBLENDENABLE, &value);
		  myfile << "D3DRS_INDEXEDVERTEXBLENDENABLE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_COLORWRITEENABLE, &value);
		  myfile << "D3DRS_COLORWRITEENABLE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_TWEENFACTOR, &value);
		  myfile << "D3DRS_TWEENFACTOR: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_BLENDOP, &value);
		  myfile << "D3DRS_BLENDOP: " << value << "\n";
	  
		  pd3dDevice->GetRenderState(D3DRS_POSITIONDEGREE, &value);
		  myfile << "D3DRS_POSITIONDEGREE: " << value << "\n";
	  
		  pd3dDevice->GetRenderState(D3DRS_NORMALDEGREE, &value);
		  myfile << "D3DRS_NORMALDEGREE: " << value << "\n";
	  
		  pd3dDevice->GetRenderState(D3DRS_SCISSORTESTENABLE, &value);
		  myfile << "D3DRS_SCISSORTESTENABLE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_SLOPESCALEDEPTHBIAS, &value);
		  myfile << "D3DRS_SLOPESCALEDEPTHBIAS: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_ANTIALIASEDLINEENABLE, &value);
		  myfile << "D3DRS_ANTIALIASEDLINEENABLE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_MINTESSELLATIONLEVEL, &value);
		  myfile << "D3DRS_MINTESSELLATIONLEVEL: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_MAXTESSELLATIONLEVEL, &value);
		  myfile << "D3DRS_MAXTESSELLATIONLEVEL: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_ADAPTIVETESS_X, &value);
		  myfile << "D3DRS_ADAPTIVETESS_X: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_ADAPTIVETESS_Y, &value);
		  myfile << "D3DRS_ADAPTIVETESS_Y: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_ADAPTIVETESS_Z, &value);
		  myfile << "D3DRS_ADAPTIVETESS_Z: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_ADAPTIVETESS_W, &value);
		  myfile << "D3DRS_ADAPTIVETESS_W: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_ENABLEADAPTIVETESSELLATION, &value);
		  myfile << "D3DRS_ENABLEADAPTIVETESSELLATION: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_TWOSIDEDSTENCILMODE, &value);
		  myfile << "D3DRS_TWOSIDEDSTENCILMODE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_CCW_STENCILFAIL, &value);
		  myfile << "D3DRS_CCW_STENCILFAIL: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_CCW_STENCILZFAIL, &value);
		  myfile << "D3DRS_CCW_STENCILZFAIL: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_CCW_STENCILPASS, &value);
		  myfile << "D3DRS_CCW_STENCILPASS: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_CCW_STENCILFUNC, &value);
		  myfile << "D3DRS_CCW_STENCILFUNC: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_COLORWRITEENABLE1, &value);
		  myfile << "D3DRS_COLORWRITEENABLE1: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_COLORWRITEENABLE2, &value);
		  myfile << "D3DRS_COLORWRITEENABLE2: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_COLORWRITEENABLE3, &value);
		  myfile << "D3DRS_COLORWRITEENABLE3: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_BLENDFACTOR, &value);
		  myfile << "D3DRS_BLENDFACTOR: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_SRGBWRITEENABLE, &value);
		  myfile << "D3DRS_SRGBWRITEENABLE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, &value);
		  myfile << "D3DRS_SEPARATEALPHABLENDENABLE: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_SRCBLENDALPHA, &value);
		  myfile << "D3DRS_SRCBLENDALPHA: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_DESTBLENDALPHA, &value);
		  myfile << "D3DRS_DESTBLENDALPHA: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_BLENDOPALPHA, &value);
		  myfile << "D3DRS_BLENDOPALPHA: " << value << "\n";

		  pd3dDevice->GetRenderState(D3DRS_FORCE_DWORD, &value);
		  myfile << "D3DRS_FORCE_DWORD: " << value << "\n";

		  myfile.close();
	}
	void logTexture(IDirect3DDevice9* pd3dDevice, IDirect3DTexture9* pTexture, char* filename)
	{
		D3DXSaveTextureToFile(filename, D3DXIFF_JPG, pTexture, NULL);
	}
	void logTextureUsingDrawPrimitiveCount(IDirect3DDevice9* pd3dDevice, IDirect3DTexture9* pTexture)
	{
		char fullPath[64]="pics/";
		char fileName[16];
		char fileSuffix[16]="_tex.jpg";
		itoa(g_dbDrawPrimitiveCount, fileName, 10);
		strcat(fullPath, fileName);
		strcat(fullPath, fileSuffix);
		logTexture(pd3dDevice, pTexture, fullPath);
	}
	void logTextureDesc(IDirect3DDevice9* pd3dDevice, IDirect3DTexture9* pTexture, char* filename)
	{
		D3DSURFACE_DESC Desc;
		pTexture->GetLevelDesc(0, &Desc);
		std::ofstream myfile;
		myfile.open (filename);
		myfile << "Format: "             << (DWORD)(Desc.Format)             << "\n";
		myfile << "Type: "               << (DWORD)(Desc.Type)               << "\n";
		myfile << "Usage: "              << (DWORD)(Desc.Usage)              << "\n";
		myfile << "Pool: "               << (DWORD)(Desc.Pool)               << "\n";
		myfile << "MultiSampleType: "    << (DWORD)(Desc.MultiSampleType)    << "\n";
		myfile << "MultiSampleQuality: " << (DWORD)(Desc.MultiSampleQuality) << "\n";
		myfile << "Width: "              << (DWORD)(Desc.Width)              << "\n";
		myfile << "Height: "             << (DWORD)(Desc.Height)             << "\n";
		myfile.close();
	}
	void logTextureDescUsingDrawPrimitiveCount(IDirect3DDevice9* pd3dDevice, IDirect3DTexture9* pTexture)
	{
		char fullPath[64]="pics/";
		char fileName[16];
		char fileSuffix[16]="_texDesc.txt";
		itoa(g_dbDrawPrimitiveCount, fileName, 10);
		strcat(fullPath, fileName);
		strcat(fullPath, fileSuffix);
		logTextureDesc(pd3dDevice, pTexture, fullPath);
	}
}