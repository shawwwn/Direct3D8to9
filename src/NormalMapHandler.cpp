#include "NormalMapHandler.h"

namespace NP {
	TextureTable g_texTable;

	void InitGlobals()
	{
		g_texTable.cleanup();
		// format: Stride, NumVertices, PrimCount, AlphaRef
		g_texTable.addTextureEntry(32, 320, 153, 192);	// Human Farm
		// TODO: add more...
	}

	HRESULT PerformNormalMappping(IDirect3DDevice9* pd3dDevice, IDirect3DBaseTexture9* pBaseTexture,
                                  DWORD dwKey1, DWORD dwKey2, DWORD dwKey3, DWORD dwKey4)
	{
		HRESULT hr = D3D_OK;
		IDirect3DTexture9* pTexture = NULL;
		//
		// Query For Normal Map Texture
		//
		TextureKeys keys(dwKey1, dwKey2, dwKey3, dwKey4);
		try
		{
			TextureItem item = g_texTable.at(keys);	// check if item exists

			if (!item.m_Computed || item.m_pTexture == NULL)
			{
				hr = D3DXComputeNormalMap(item.m_pTexture, (IDirect3DTexture9*)pBaseTexture, 0, D3DX_NORMALMAP_MIRROR, D3DX_CHANNEL_BLUE, 10);
				if (FAILED(hr))
					MessageBox(NULL, "Compute Normal Map failed!", "Error", MB_OK);
				item.m_Computed = true;
			}
			pTexture = item.m_pTexture;
		}
		catch (const std::out_of_range)
		{
			return D3DERR_INVALIDCALL;	// not exists
		}

		//
		// Render Normal Map
		//
		//TODO: add normal map logic
		// .............


		return hr;
	}
}
