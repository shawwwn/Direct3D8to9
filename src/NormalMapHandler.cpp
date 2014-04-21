#include "NormalMapHandler.h"

namespace NP {
	TextureTable g_texTable;
	DWORD g_AlphaValue = D3DCOLOR_ARGB(178,255,255,255);	// 70% transparency

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
		g_texTable.addTextureEntry(32, 320, 153, 192, 128, 128);	// Human Farm
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
				// TODO: Get below to work.
				/*
				hr = pd3dDevice->CreateTexture(256, 256,
												1,
												0,
												D3DFMT_UNKNOWN,
												D3DPOOL_MANAGED,
												&item.m_pTexture,
												NULL);
				*/
				hr = D3DXCreateTextureFromFile(pd3dDevice, "FarmNormalMap.bmp", &(pItem->m_pTexture));
				if (FAILED(hr))
					MessageBox(NULL, "Create Normal Map Texture Failed!", "Error", MB_OK);
				hr = D3DXComputeNormalMap(pItem->m_pTexture, (IDirect3DTexture9*)pBaseTexture, 0, D3DX_NORMALMAP_MIRROR, D3DX_CHANNEL_BLUE, 10);
				if (FAILED(hr))
					MessageBox(NULL, "Compute Normal Map Texture Failed!", "Error", MB_OK);
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
