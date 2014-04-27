#include "NormalMapHandler.h"
#include "DebugUtils.h"

namespace NP {
	TextureTable g_texTable;
	DWORD g_AlphaValue = D3DCOLOR_ARGB(178,0,0,255);	// 70% transparency for transpant models
	DWORD g_NormalTextureAlpha = D3DCOLOR_ARGB(255,0,0,255);	// 100% opacity for normal models

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


	void InitGlobals(IDirect3DDevice9* pd3dDevice)
	{
		g_texTable.cleanup();
		/*
		 * Format: 
		 * Stride, NumVertices, PrimCount, Width, Height, Inverted, IsMask(optional), NormalAlphaRef(optional), TransplantAlphaRef(optional)
		 */
		g_texTable.addTextureEntry(32,  1053, 511,  256, 256, false);								// Human Construction Set
		//g_texTable.addTextureEntry(32,  20,   10,   256, 256, false, true, 192, 4);					// Human Farm - top
		g_texTable.addTextureEntry(32,  320,  153,  256, 256, false);								// Human Farm - body
		g_texTable.addTextureEntry(32,  8,    6,    256, 256, false);								// Human Townhall - base
		g_texTable.addTextureEntry(32,  18,   10,   512, 512, false, true, 192, 4);					// Human Townhall - top
		g_texTable.addTextureEntry(32,  454,  209,  512, 512, false);								// Human Townhall - body
		g_texTable.addTextureEntry(32,  37,   19,   512, 512, false, true, 192, 4);					// Human Keep - top
		g_texTable.addTextureEntry(32,  405,  200,  512, 512, false);								// Human Keep - body
		g_texTable.addTextureEntry(32,  177,  83,   512, 512, false, true, 192, 4);					// Human Castle - top
		g_texTable.addTextureEntry(32,  418,  352,  512, 512, false);								// Human Castle - body
		g_texTable.addTextureEntry(32,  90,   30,   256, 256, false);								// Human Castle - base
		//g_texTable.addTextureEntry(32,  52,   42,   256, 256, false, true, 192, 4);					// Human Altar - top (weird color)
		g_texTable.addTextureEntry(32,  359,  302,  256, 256, false);								// Human Altar - body
		g_texTable.addTextureEntry(32,  99,   46,   256, 256, false, true, 192, 4);					// Human Barracks - top
		g_texTable.addTextureEntry(32,  387,  209,  256, 256, false);								// Human Barracks - body
		g_texTable.addTextureEntry(32,  14,   8,    256, 256, false, true, 192, 4);					// Human Lumber Mill - top
		g_texTable.addTextureEntry(32,  386,  224,  256, 256, false);								// Human Lumber Mill - body
		g_texTable.addTextureEntry(32,  20,   28,   256, 256, false);								// Human Lumber Mill - base
		g_texTable.addTextureEntry(32,  22,   14,   256, 256, false, true, 192, 4);					// Human BlackSmith - top
		g_texTable.addTextureEntry(32,  605,  343,  256, 256, false);								// Human BlackSmith - body
		g_texTable.addTextureEntry(32,  39,   24,   256, 256, false, true, 192, 4);					// Human Arcane Vault - top
		g_texTable.addTextureEntry(32,  85,   40,   256, 256, false);								// Human Arcane Vault - gem
		g_texTable.addTextureEntry(32,  96,   48,   256, 256, false);								// Human Arcane Vault - pole
		g_texTable.addTextureEntry(32,  500,  266,  256, 256, false);								// Human Arcane Vault - chain
		//g_texTable.addTextureEntry(32,  39,   24,   256, 256, false, true, 192, 4);					// Human Arcane Sanctum - top
		g_texTable.addTextureEntry(32,  923,  578,  256, 256, false);								// Human Arcane Sanctum - body
		//g_texTable.addTextureEntry(32,  25,   17,   256, 256, false, true, 192, 4);					// Human Gryphon Aviary - top
		g_texTable.addTextureEntry(32,  414,  309,  256, 256, true);								// Human Gryphon Aviary - body
		//g_texTable.addTextureEntry(32,  20,   26,   256, 256, false, true, 192, 4);					// Human Workshop - top
		g_texTable.addTextureEntry(32,  310,  266,  256, 256, false);								// Human Workshop - body
		//g_texTable.addTextureEntry(32,  27,   15,   256, 128, true, true, 192, 4);					// Human Scout Tower - top
		g_texTable.addTextureEntry(32,  251,  149,  256, 128, true);								// Human Scout Tower - body
		//g_texTable.addTextureEntry(32,  216,  123,  256, 128, true, true, 192, 4);					// Human Arcane Tower - top (conflict)
		//g_texTable.addTextureEntry(32,  88,   56,   256, 128, true);								// Human Arcane Tower - body (conflict)
		g_texTable.addTextureEntry(32,  97,   48,   256, 128, true);								// Human Arcane Tower - tower
		//g_texTable.addTextureEntry(32,  51,   27,   256, 128, true, true, 192, 4);					// Human Guard Tower - top
		g_texTable.addTextureEntry(32,  216,  123,  256, 128, true);								// Human Guard Tower - body
		//g_texTable.addTextureEntry(32,  32,   20,   256, 128, true, true, 192, 4);					// Human Cannon Tower - top
		g_texTable.addTextureEntry(32,  300,  189,  256, 128, true);								// Human Cannon Tower - body

		g_texTable.addTextureEntry(32,  300,  252,  256, 256, false);								// Orc Construction Set - large
		g_texTable.addTextureEntry(32,  264,  228,  256, 256, false);								// Orc Construction Set - medium
		g_texTable.addTextureEntry(32,  198,  164,  256, 256, false);								// Orc Construction Set - small
		//g_texTable.addTextureEntry(32,  64,   64,   256, 256, false, true, 192, 4);					// Orc Construction Set - top (conflict)
		g_texTable.addTextureEntry(32,  160,  104,  256, 256, true);								// Orc Structure - base
		g_texTable.addTextureEntry(32,  124,  80,   256, 256, false);								// Orc Structure Spike
		g_texTable.addTextureEntry(32,  192,  144,  128, 128, false);								// Orc Structure Barricade

		g_texTable.addTextureEntry(32,  191,  214,  256, 256, false, true, 192, 4);					// Orc Great Hall - top	
		g_texTable.addTextureEntry(32,  290,  164,  256, 256, false);								// Orc Great Hall - body
		g_texTable.addTextureEntry(32,  183,  188,  256, 256, false, true, 192, 4);					// Orc Stronghold - top
		g_texTable.addTextureEntry(32,  384,  249,  256, 256, false);								// Orc Stronghold - body
		g_texTable.addTextureEntry(32,  226,  149,  256, 256, false, true, 192, 4);					// Orc Fortress - top
		g_texTable.addTextureEntry(32,  516,  498,  256, 256, false);								// Orc Fortress - body
		g_texTable.addTextureEntry(32,  95,   59,   256, 256, false, true, 192, 4);					// Orc Altar - top
		g_texTable.addTextureEntry(32,  291,  264,  256, 256, false);								// Orc Altar - body
		g_texTable.addTextureEntry(32,  265,  206,  128, 128, false);								// Orc Burrow - body
		//g_texTable.addTextureEntry(32,  36,   28,   128, 128, false, true, 192, 4);					// Orc Burrow - top
		g_texTable.addTextureEntry(32,  309,  317,  256, 256, false);								// Orc War Mill - body
		g_texTable.addTextureEntry(32,  125,  81,   256, 256, false);								// Orc War Mill - saw
		g_texTable.addTextureEntry(32,  42,   48,   256, 256, false, true, 192, 4);					// Orc War Mill - top
		g_texTable.addTextureEntry(32,  466,  295,  256, 256, false);								// Orc Watch Tower - body
		g_texTable.addTextureEntry(32,  17,   12,   256, 256, false, true, 192, 4);					// Orc Watch Tower - top
		g_texTable.addTextureEntry(32,  255,  195,  256, 256, false);								// Orc Barracks - body
		g_texTable.addTextureEntry(32,  73,   56,   256, 256, false, true, 192, 4);					// Orc Barracks - top
		//g_texTable.addTextureEntry(32,  19,   20,   256, 256, false);								// Orc Voodoo Lounge - funnel
		g_texTable.addTextureEntry(32,  66,   54,   256, 256, false);								// Orc Voodoo Lounge - tusk
		g_texTable.addTextureEntry(32,  145,  78,   256, 256, false);								// Orc Voodoo Lounge - body
		g_texTable.addTextureEntry(32,  211,  207,  256, 256, false, true, 192, 4);					// Orc Voodoo Lounge - top
		g_texTable.addTextureEntry(32,  327,  260,  256, 256, true);								// Orc Beastiary - body
		g_texTable.addTextureEntry(32,  69,   92,   256, 256, false, true, 192, 4);					// Orc Beastiary - top
		g_texTable.addTextureEntry(32,  414,  295,  256, 256, true);								// Orc Spirit Lounge - body
		g_texTable.addTextureEntry(32,  52,   26,   256, 256, true,  true, 192, 4);					// Orc Spirit Lounge - top
		g_texTable.addTextureEntry(32,  323,  221,  256, 256, false);								// Orc Tauren Totem - body
		g_texTable.addTextureEntry(32,  57,   67,   256, 256, false, true, 192, 4);					// Orc Tauren Totem - top

		g_texTable.addTextureEntry(32,  271,  239,  256, 256, false);								// Gold Mine - mine
		g_texTable.addTextureEntry(32,  84,   51,   64,  64,  false);								// Gold Mine - gold
		g_texTable.addTextureEntry(32,  123,  60,   256, 256, false);								// Gold Mine - base
		g_texTable.addTextureEntry(32,  132,  68,   256, 64,  false, true, 192, 4);					// Goblin Merchant - top
		g_texTable.addTextureEntry(32,  474,  274,  256, 256, false);								// Goblin Merchant - body
		g_texTable.addTextureEntry(32,  547,  442,  256, 256, false);								// Tarven
		g_texTable.addTextureEntry(32,  331,  346,  512, 256, false);								// Fountain of Health
		g_texTable.addTextureEntry(32,  491,  348,  256, 256, false);								// Goblin Laboratory
		g_texTable.addTextureEntry(32,  571,  394,  256, 256, false);								// Mercenary Camp
		g_texTable.addTextureEntry(32,  407,  347,  256, 256, false);								// Marketplace - body
		g_texTable.addTextureEntry(32,  94,   46,   256, 256, false, true, 192, 4);					// Marketplace - top

		//g_texTable.addTextureEntry(32,  36,   28,  256, 256, false);								// Tree
		//g_texTable.addTextureEntry(32,  247,  336, 256, 256, false);								// Test Subject

		//g_texTable.addTextureEntry(32,  1065, 1143,256, 256, false);								// Main Screen
		// TODO: add more...
	}

	HRESULT PerformNormalMappping(IDirect3DDevice9* pd3dDevice, IDirect3DBaseTexture9* pBaseTexture,
                                  D3DPRIMITIVETYPE Type, UINT baseVertexIndex, UINT minIndex, UINT startIndex,
                                  UINT Stride, UINT NumVertices, UINT primCount, DWORD AlphaRef, DWORD TransformStateType)
	{
		if (TransformStateType==2) { return D3DERR_INVALIDCALL; }	// filter out terrain texture
		HRESULT hr = D3D_OK;
		IDirect3DTexture9* pNormalTexture = NULL;
		DWORD dwAlphaTestEnable, dwAlphaBlendEnable, dwZWriteEnable;
		pd3dDevice->GetRenderState(D3DRS_ALPHATESTENABLE, &dwAlphaTestEnable);
		pd3dDevice->GetRenderState(D3DRS_ALPHABLENDENABLE, &dwAlphaBlendEnable);
		pd3dDevice->GetRenderState(D3DRS_ZWRITEENABLE, &dwZWriteEnable);
		bool isPureColorMesh;
		bool isAlphaBenldEnable = (dwAlphaTestEnable==1 && dwAlphaBlendEnable==1);


		//
		// Query For Normal Map Texture
		//
		TextureKeys keys(Stride, NumVertices, primCount);
		try
		{
			TextureItem* pItem = &(g_texTable.at(keys));	// check if item exists, return in reference

			if (!pItem->m_Computed)
			{
				// Create normal map texture
				if (pItem->m_pNormalTexture == NULL)
				{
					hr = D3DXCreateTexture(pd3dDevice, pItem->m_Width, pItem->m_Height, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &(pItem->m_pNormalTexture));
					if (FAILED(hr))
						MessageBox(NULL, "Create Normal Map Texture Failed!", "Error", MB_OK);
				}

				// Compute normal map texture
				float invertSign = pItem->m_Inverted ? -1.0f : 1.0f;
				hr = D3DXComputeNormalMap(pItem->m_pNormalTexture, (IDirect3DTexture9*)pBaseTexture, 0, D3DX_NORMALMAP_MIRROR, D3DX_CHANNEL_LUMINANCE, NORMAL_AMPLITUDE*invertSign);
				if (FAILED(hr))
				{
					MessageBox(NULL, "Compute Normal Map Texture Failed!", "Error", MB_OK);
					DB::savePrimitiveStatesToFile(Type, minIndex, NumVertices, startIndex, primCount, 
						0, Stride, 0, D3DTS_VIEW, 0,
						baseVertexIndex, 0, pBaseTexture, "failTex.txt");
					D3DXSaveTextureToFile("failTex.bmp", D3DXIFF_BMP, pBaseTexture, NULL);
					return D3DERR_INVALIDCALL;	// return to normal rendering
				}
				pItem->m_Computed = true;
			}
			pNormalTexture = pItem->m_pNormalTexture;
			isPureColorMesh = (pItem->m_IsMask && dwZWriteEnable==1);

		}
		catch (const std::out_of_range)
		{
			return D3DERR_INVALIDCALL;	// not exists
		}


		//
		// Filter pre-build placement model
		//
		if (isPureColorMesh && isAlphaBenldEnable)
		{
			return D3DERR_INVALIDCALL;	// The model is a pre-build placement
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
		pd3dDevice->SetTexture(0, pNormalTexture);
		pd3dDevice->SetTexture(1, pBaseTexture);
		// set alpha blending
		pd3dDevice->SetRenderState(D3DRS_TEXTUREFACTOR, g_AlphaValue);

		pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pd3dDevice->SetRenderState(D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA);
		pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		//pd3dDevice->SetRenderState(D3DRS_ALPHAREF, 0x08);
		//pd3dDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
		// use dot3 product
		DWORD coord;
		pd3dDevice->GetTextureStageState(0, D3DTSS_TEXCOORDINDEX, &coord);
		pd3dDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, coord);
		pd3dDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DOTPRODUCT3);
		pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);//D3DTA_TFACTOR | D3DTA_DIFFUSE

		if (isPureColorMesh)
		{
			// for pure color texture
			pd3dDevice->DrawIndexedPrimitive(Type, baseVertexIndex, minIndex, NumVertices, startIndex, primCount);
			// Pass3 - transparency
			pd3dDevice->SetTexture(0, pBaseTexture);
			pd3dDevice->SetTexture(1, pBaseTexture);
			pd3dDevice->SetTextureStageState(0,D3DTSS_COLOROP, D3DTOP_MODULATE);
			pd3dDevice->SetTextureStageState(0,D3DTSS_COLORARG1, D3DTA_TEXTURE);
			pd3dDevice->SetTextureStageState(0,D3DTSS_COLORARG2, D3DTA_DIFFUSE);
			pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
			pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
			pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

			pd3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
			pd3dDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
			pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
			pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
			pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_TFACTOR);
		}
		else
		{
			pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			// for normal texture
			pd3dDevice->SetRenderState(D3DRS_TEXTUREFACTOR, g_NormalTextureAlpha);
			pd3dDevice->SetTexture(2, pBaseTexture);
			pd3dDevice->SetTexture(3, pBaseTexture);
			pd3dDevice->SetTextureStageState(2, D3DTSS_TEXCOORDINDEX, coord);
			pd3dDevice->SetTextureStageState(3, D3DTSS_TEXCOORDINDEX, coord);

			pd3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
			pd3dDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			pd3dDevice->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
			pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
			pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_TFACTOR);
			pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
			
			pd3dDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_MODULATE2X);
			pd3dDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_TEXTURE);
			pd3dDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_CURRENT);
			pd3dDevice->SetTextureStageState(2, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
			pd3dDevice->SetTextureStageState(2, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
			pd3dDevice->SetTextureStageState(2, D3DTSS_ALPHAARG2, D3DTA_CURRENT);
			
			pd3dDevice->SetTextureStageState(3, D3DTSS_COLOROP, D3DTOP_MODULATE);
			pd3dDevice->SetTextureStageState(3, D3DTSS_COLORARG1, D3DTA_CURRENT);
			pd3dDevice->SetTextureStageState(3, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
			pd3dDevice->SetTextureStageState(3, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
			pd3dDevice->SetTextureStageState(3, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
			pd3dDevice->SetTextureStageState(3, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
			
		}
		pd3dDevice->DrawIndexedPrimitive(Type, baseVertexIndex, minIndex, NumVertices, startIndex, primCount);


		//
		//	Restore
		//
		pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, dwZWriteEnable);
		pd3dDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
		pd3dDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		pd3dDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);
		pd3dDevice->SetTextureStageState(2, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		pd3dDevice->SetTextureStageState(3, D3DTSS_COLOROP, D3DTOP_DISABLE);
		pd3dDevice->SetTextureStageState(3, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
		restoreTextureStageStates(pd3dDevice);
		restoreRenderStates(pd3dDevice);
		pd3dDevice->SetTexture(0, pBaseTexture);
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
