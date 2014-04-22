#include "NormalMapHandler.h"
#include "DebugUtils.h"

namespace NP {
	TextureTable g_texTable;
	DWORD g_AlphaValue = D3DCOLOR_ARGB(178,0,0,255);	// 60% transparency

	DWORD g_pColorArg1_0;
	DWORD g_pColorOp_0;
	DWORD g_pColorArg2_0;
	DWORD g_pAlphaOp_0;
	DWORD g_pAlphaArg1_0;
	DWORD g_pAlphaArg2_0;
	DWORD g_pTexCoordIndex_0;

	DWORD g_AlphaTestEnable;
	DWORD g_AlphaBlendEnable;
	DWORD g_SrcBlend;
	DWORD g_DestBlend;
	DWORD g_TextureFactor;

	void InitGlobals()
	{
		g_texTable.cleanup();
		// format: Stride, NumVertices, PrimCount, AlphaRef
		g_texTable.addTextureEntry(32, 320,  153,  192, 256, 256);	// Human Farm
		g_texTable.addTextureEntry(32, 8,    6,    192, 256, 256);	// Human Townhall - base
		g_texTable.addTextureEntry(32, 454,  209,  192, 512, 512);	// Human Townhall - body
		g_texTable.addTextureEntry(32, 18,   10,   192, 256, 256);	// Human Townhall - top
		g_texTable.addTextureEntry(32, 359,  302,  192, 256, 256);	// Human Altar - body
		g_texTable.addTextureEntry(32, 99,   46,   192, 256, 256);	// Human Barracks - top
		g_texTable.addTextureEntry(32, 387,  209,  192, 256, 256);	// Human Barracks - body
		g_texTable.addTextureEntry(32, 386,  224,  192, 256, 256);	// Human Lumber Mill - body
		g_texTable.addTextureEntry(32, 39,   24,   192, 256, 256);	// Human Arcane Vault - box
		g_texTable.addTextureEntry(32, 251,  149,  192, 256, 128);	// Human Scout Tower
		g_texTable.addTextureEntry(32, 1053, 511,  192, 256, 256);	// Human Construction Set

		g_texTable.addTextureEntry(32, 300,  252,  192, 256, 256);	// Orc Construction Set - large
		g_texTable.addTextureEntry(32, 264,  228,  192, 256, 256);	// Orc Construction Set - medium
		g_texTable.addTextureEntry(32, 198,  164,  192, 256, 256);	// Orc Construction Set - small
		g_texTable.addTextureEntry(32, 64,   64,   192, 256, 256);	// Orc Construction Set - top
		g_texTable.addTextureEntry(32, 160,  104,  192, 256, 256);	// Orc Structure - base
		g_texTable.addTextureEntry(32, 191,  214,  192, 256, 256);	// Orc Great Hall - top
		g_texTable.addTextureEntry(32, 290,  164,  192, 256, 256);	// Orc Great Hall - body
		g_texTable.addTextureEntry(32, 183,  188,  192, 256, 256);	// Orc Stronghold - top
		g_texTable.addTextureEntry(32, 384,  249,  192, 256, 256);	// Orc Stronghold - body
		g_texTable.addTextureEntry(32, 226,  149,  192, 256, 256);	// Orc Fortress - top
		g_texTable.addTextureEntry(32, 516,  498,  192, 256, 256);	// Orc Fortress - body
		g_texTable.addTextureEntry(32, 95,   59,   192, 256, 256);	// Orc Altar - top
		g_texTable.addTextureEntry(32, 291,  264,  192, 256, 256);	// Orc Altar - body
		g_texTable.addTextureEntry(32, 265,  206,  192, 128, 128);	// Orc Burrow
		g_texTable.addTextureEntry(32, 309,  317,  192, 256, 256);	// Orc War Mill - body
		g_texTable.addTextureEntry(32, 466,  295,  192, 256, 256);	// Orc Watch Tower - body
		g_texTable.addTextureEntry(32, 255,  195,  192, 256, 256);	// Orc Barracks - body
		g_texTable.addTextureEntry(32, 19,   20,   192, 256, 256);	// Orc Voodoo Lounge - body
		g_texTable.addTextureEntry(32, 66,   54,   192, 256, 256);	// Orc Voodoo Lounge - body2
		g_texTable.addTextureEntry(32, 148,  45,   192, 256, 256);	// Orc Voodoo Lounge - trunk
		g_texTable.addTextureEntry(32, 211,  207,  192, 256, 256);	// Orc Voodoo Lounge - top
		g_texTable.addTextureEntry(32, 327,  260,  192, 256, 256);	// Orc Beastiary - body [transparency issue]
		g_texTable.addTextureEntry(32, 69,   92,   192, 256, 256);	// Orc Beastiary - top
		g_texTable.addTextureEntry(32, 414,  295,  192, 256, 256);	// Orc Spirit Lounge
		g_texTable.addTextureEntry(32, 323,  221,  192, 256, 256);	// Orc Tauren Totem - body
		g_texTable.addTextureEntry(32, 57,   67,   192, 256, 256);	// Orc Tauren Totem - pole

		g_texTable.addTextureEntry(32, 271,  239,  192, 256, 256);	// Gold Mine - mine
		g_texTable.addTextureEntry(32, 84,   51,   192, 64,  64);	// Gold Mine - gold
		g_texTable.addTextureEntry(32, 123,  60,   192, 256, 256);	// Gold Mine - base
		g_texTable.addTextureEntry(32, 132,  68,  192, 256, 64);	// Gold Merchant - top [transparency issue]
		g_texTable.addTextureEntry(32, 474,  274,  192, 256, 256);	// Gold Merchant - body
		g_texTable.addTextureEntry(32, 547,  442,  192, 256, 256);	// Tarven
		g_texTable.addTextureEntry(32, 331,  346,  192, 512, 256);	// Fountain of Health
		g_texTable.addTextureEntry(32, 491,  348,  192, 256, 256);	// Goblin Laboratory
		g_texTable.addTextureEntry(32, 571,  394,  192, 256, 256);	// Mercenary Camp
		g_texTable.addTextureEntry(32, 407,  347,  192, 256, 256);	// Marketplace - body
		g_texTable.addTextureEntry(32, 94,   46,   192, 256, 256);	// Marketplace - top

		//g_texTable.addTextureEntry(32, 1065, 1143, 4,   256, 256);	// Main Screen
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
					//D3DXSaveTextureToFile("texture.bmp", D3DXIFF_BMP, pBaseTexture, NULL);	// for debug
				}
				pItem->m_Computed = true;
			}
			pTexture = pItem->m_pTexture;
		}
		catch (const std::out_of_range)
		{
			return D3DERR_INVALIDCALL;	// not exists
		}

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
		//pd3dDevice->SetRenderState(D3DRS_ALPHAREF, 0x08);
		//pd3dDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
		// use dot3 product
		pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DOTPRODUCT3);
		pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);
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
		pd3dDevice->GetRenderState(D3DRS_ALPHABLENDENABLE, &g_AlphaBlendEnable);
		pd3dDevice->GetRenderState(D3DRS_SRCBLEND, &g_SrcBlend);
		pd3dDevice->GetRenderState(D3DRS_DESTBLEND, &g_DestBlend);
		pd3dDevice->GetRenderState(D3DRS_TEXTUREFACTOR, &g_TextureFactor);
	}
	void restoreRenderStates(IDirect3DDevice9* pd3dDevice)
	{
		pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, g_AlphaTestEnable);
		pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, g_AlphaBlendEnable);
		pd3dDevice->SetRenderState(D3DRS_SRCBLEND, g_SrcBlend);
		pd3dDevice->SetRenderState(D3DRS_DESTBLEND, g_DestBlend);
		pd3dDevice->SetRenderState(D3DRS_TEXTUREFACTOR, g_TextureFactor);
	}
}
