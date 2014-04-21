#include "NormalMapHandler.h"
#include "DebugUtils.h"

namespace NP {
	TextureTable g_texTable;
	DWORD g_AlphaValue = D3DCOLOR_ARGB(160,255,255,255);	// 60% transparency

	DWORD g_pColorArg1_0;
	DWORD g_pColorOp_0;
	DWORD g_pColorArg2_0;
	DWORD g_pAlphaOp_0;
	DWORD g_pAlphaArg1_0;
	DWORD g_pAlphaArg2_0;
	DWORD g_pTexCoordIndex_0;
	DWORD g_AlphaTestEnable;

	void InitGlobals()
	{
		g_texTable.cleanup();
		// format: Stride, NumVertices, PrimCount, AlphaRef
		g_texTable.addTextureEntry(32, 320, 153, 192, 256, 256);	// Human Farm
		g_texTable.addTextureEntry(32, 8,   6,   192, 256, 256);	// Human Townhall - base
		g_texTable.addTextureEntry(32, 454, 209, 192, 512, 512);	// Human Townhall - body
		g_texTable.addTextureEntry(32, 18,  10,  192, 256, 256);	// Human Townhall - top
		g_texTable.addTextureEntry(32, 359, 302, 192, 256, 256);	// Human Altar - body
		g_texTable.addTextureEntry(32, 99,  46,  192, 256, 256);	// Human Barracks - top
		g_texTable.addTextureEntry(32, 387, 209, 192, 256, 256);	// Human Barracks - body
		g_texTable.addTextureEntry(32, 386, 224, 192, 256, 256);	// Human Lumber Mill - body
		g_texTable.addTextureEntry(32, 39,  24,  192, 256, 256);	// Human Arcane Vault - box
		g_texTable.addTextureEntry(32, 251, 149, 192, 256, 128);	// Human Scout Tower
		g_texTable.addTextureEntry(32, 1053,511, 192, 256, 256);	// Human Construction Set

		g_texTable.addTextureEntry(32, 160, 104, 192, 256, 256);	// Orc Structure - base

		g_texTable.addTextureEntry(32, 271, 239, 192, 256, 256);	// Gold Mine - mine
		g_texTable.addTextureEntry(32, 84,  51,  192, 64,  64);		// Gold Mine - gold
		g_texTable.addTextureEntry(32, 123, 60,  192, 256, 256);	// Gold Mine - base
		g_texTable.addTextureEntry(32, 132, 68,  192, 256, 64);		// Gold Merchant - top
		g_texTable.addTextureEntry(32, 474, 274, 192, 256, 256);	// Gold Merchant - body
		g_texTable.addTextureEntry(32, 547, 442, 192, 256, 256);	// Tarven
		g_texTable.addTextureEntry(32, 331, 346, 192, 512, 256);	// Fountain of Health
		g_texTable.addTextureEntry(32, 491, 348, 192, 256, 256);	// Goblin Laboratory
		g_texTable.addTextureEntry(32, 571, 394, 192, 256, 256);	// Mercenary Camp
		// TODO: add more...
	}

	HRESULT PerformNormalMappping(IDirect3DDevice9* pd3dDevice, IDirect3DBaseTexture9* pBaseTexture,
                                  D3DPRIMITIVETYPE Type, UINT baseVertexIndex, UINT minIndex, UINT startIndex,
                                  UINT Stride, UINT NumVertices, UINT primCount, DWORD AlphaRef)
	{
		HRESULT hr = D3D_OK;
		IDirect3DTexture9* pTexture = NULL;
		//
		// Query For Normal Map Texture
		//
		TextureKeys keys(Stride, NumVertices, primCount, AlphaRef);
		try
		{
			TextureItem* pItem = &(g_texTable.at(keys));	// check if item exists, return in reference

			if (!pItem->m_Computed || pItem->m_pTexture == NULL)
			{
				// Create normal map texture
				hr = D3DXCreateTexture(pd3dDevice, pItem->m_Width, pItem->m_Height, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &(pItem->m_pTexture));
				//hr = D3DXCreateTextureFromFile(pd3dDevice, "FarmNormalMap.bmp", &(pItem->m_pTexture));
				if (FAILED(hr))
					MessageBox(NULL, "Create Normal Map Texture Failed!", "Error", MB_OK);
				hr = D3DXComputeNormalMap(pItem->m_pTexture, (IDirect3DTexture9*)pBaseTexture, 0, D3DX_NORMALMAP_MIRROR, D3DX_CHANNEL_RED, 100);
				if (FAILED(hr))
				{
					MessageBox(NULL, "Compute Normal Map Texture Failed!", "Error", MB_OK);
					D3DXSaveTextureToFile("texture.bmp", D3DXIFF_BMP, pBaseTexture, NULL);
				}
				pItem->m_Computed = true;
			}
			pTexture = pItem->m_pTexture;
		}
		catch (const std::out_of_range)
		{
			return D3DERR_INVALIDCALL;	// not exists
		}

		DB::logTextureDesc(pd3dDevice, pTexture, "texture.txt");
		//
		// Render Normal Map
		//
		backupTextureStageStates(pd3dDevice);
		backupRenderStates(pd3dDevice);
		
		// Pass1 - original
		pd3dDevice->SetTexture(0, pBaseTexture);
		pd3dDevice->DrawIndexedPrimitive(Type, baseVertexIndex, minIndex, NumVertices, startIndex, primCount);
		
		// Pass2 - normal map
		pd3dDevice->SetTexture(0, pTexture);
		// set alpha blending
		pd3dDevice->SetRenderState(D3DRS_TEXTUREFACTOR, g_AlphaValue);
		pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
		pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TFACTOR);
		pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pd3dDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
		pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		// use dot3 product
		pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DOTPRODUCT3);
		pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
		// close extra operations
		pd3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		pd3dDevice->DrawIndexedPrimitive(Type, baseVertexIndex, minIndex, NumVertices, startIndex, primCount);
		
		// Pass3 - original re-cover
		pd3dDevice->SetTextureStageState(0,D3DTSS_COLORARG1, g_pColorArg1_0);
		pd3dDevice->SetTextureStageState(0,D3DTSS_COLOROP, g_pColorOp_0);
		pd3dDevice->SetTextureStageState(0,D3DTSS_COLORARG2, g_pColorArg2_0);
		pd3dDevice->SetTexture(0, pBaseTexture);
		pd3dDevice->DrawIndexedPrimitive(Type, baseVertexIndex, minIndex, NumVertices, startIndex, primCount);
		
		restoreTextureStageStates(pd3dDevice);
		restoreRenderStates(pd3dDevice);
		return D3D_OK;
	}

	void backupTextureStageStates(IDirect3DDevice9* pd3dDevice)
	{
		pd3dDevice->GetTextureStageState(0, D3DTSS_COLORARG1, &g_pColorArg1_0);
		pd3dDevice->GetTextureStageState(0, D3DTSS_COLOROP, &g_pColorOp_0);
		pd3dDevice->GetTextureStageState(0, D3DTSS_COLORARG2, &g_pColorArg2_0);
		pd3dDevice->GetTextureStageState(0, D3DTSS_ALPHAOP, &g_pAlphaOp_0);
		pd3dDevice->GetTextureStageState(0, D3DTSS_ALPHAARG1, &g_pAlphaArg1_0);
		pd3dDevice->GetTextureStageState(0, D3DTSS_ALPHAARG2, &g_pAlphaArg2_0);
		pd3dDevice->GetTextureStageState(0, D3DTSS_TEXCOORDINDEX, &g_pTexCoordIndex_0);
	}
	void restoreTextureStageStates(IDirect3DDevice9* pd3dDevice)
	{
		pd3dDevice->SetTextureStageState(0,D3DTSS_COLORARG1, g_pColorArg1_0);
		pd3dDevice->SetTextureStageState(0,D3DTSS_COLOROP, g_pColorOp_0);
		pd3dDevice->SetTextureStageState(0,D3DTSS_COLORARG2, g_pColorArg2_0);
		pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, g_pAlphaOp_0);
		pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, g_pAlphaArg1_0);
		pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, g_pAlphaArg2_0);
		pd3dDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, g_pTexCoordIndex_0);
	}
	void backupRenderStates(IDirect3DDevice9* pd3dDevice)
	{
		pd3dDevice->GetRenderState(D3DRS_ALPHATESTENABLE, &g_AlphaTestEnable);
	}
	void restoreRenderStates(IDirect3DDevice9* pd3dDevice)
	{
		pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, g_AlphaTestEnable);
	}
}
