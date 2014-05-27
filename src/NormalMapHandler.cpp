#include "NormalMapHandler.h"
#include "DebugUtils.h"
#pragma comment(lib, "dxguid.lib")

namespace NP {
	TextureTable g_texTable;
	DWORD g_dwAlphaValue = D3DCOLOR_ARGB(178,0,0,255);	// 70% transparency for transpant models
	DWORD g_dwNormalTextureAlpha = D3DCOLOR_ARGB(255,0,0,255);	// 100% opacity for normal models

	DWORD g_dwColorArg1_0;
	DWORD g_dwColorOp_0;
	DWORD g_dwColorArg2_0;
	DWORD g_dwAlphaOp_0;
	DWORD g_dwAlphaArg1_0;
	DWORD g_dwAlphaArg2_0;
	DWORD g_dwTexCoordIndex_0;

	DWORD g_dwAlphaTestEnable;
	DWORD g_dwAlphaBlendEnable;
	DWORD g_dwSrcBlend;
	DWORD g_dwDestBlend;
	DWORD g_dwTextureFactor;

	bool IsExceptionalMesh(UINT numVertices, UINT primCount, DWORD srcBlend, DWORD destBlend, DWORD alphaRef)
	{
		ExceptionalMeshKeys endKey = EMK_END();
		for (int i=0; memcmp(&(g_exceptionalMeshes[i]), &endKey, sizeof(ExceptionalMeshKeys))!=0; i++)
		{
			if (g_exceptionalMeshes[i].m_NumVertices==numVertices && g_exceptionalMeshes[i].m_PrimCount==primCount)
			{
				if (g_exceptionalMeshes[i].m_SrcBlend!=0 && g_exceptionalMeshes[i].m_SrcBlend!=srcBlend)
					continue;
				if (g_exceptionalMeshes[i].m_DestBlend!=0 && g_exceptionalMeshes[i].m_DestBlend!=destBlend)
					continue;
				if (g_exceptionalMeshes[i].m_AlphaRef!=0 && g_exceptionalMeshes[i].m_AlphaRef!=alphaRef)
					continue;
				return true;
			}
		}
		return false;
	}

	HRESULT Init(IDirect3DDevice9* pd3dDevice)
	{
		InitTextureTable(g_texTable);
		return D3D_OK;
	}

	HRESULT PerformNormalMappping(IDirect3DDevice9* pd3dDevice, IDirect3DBaseTexture9* pBaseTexture,
                                  D3DPRIMITIVETYPE Type, UINT baseVertexIndex, UINT minIndex, UINT startIndex,
                                  UINT Stride, UINT NumVertices, UINT primCount, DWORD AlphaRef, DWORD TransformStateType)
	{
		bool isExceptionalMesh = IsExceptionalMesh(NumVertices, primCount, g_dwSrcBlend, g_dwDestBlend, AlphaRef); // exceptional mesh flag

		if (!isExceptionalMesh && TransformStateType==2) { return D3DERR_INVALIDCALL; }	// filter out terrain texture
		HRESULT hr = D3D_OK;
		IDirect3DTexture9* pNormalTexture = NULL;
		DWORD dwZWriteEnable;
		pd3dDevice->GetRenderState(D3DRS_ZWRITEENABLE, &dwZWriteEnable);
		bool isPureColorMesh;
		bool isAlphaBenldEnable = (g_dwAlphaTestEnable==1 && g_dwAlphaBlendEnable==1);

		//
		// Query For Normal Map Texture
		//
		TextureKeys keys(Stride, NumVertices, primCount);
		try
		{
			TextureItem* pItem = &(g_texTable.at(keys));	// check if item exists, return in reference

			// Check if the TextureItem is excluded temporary
			if (EXCP::isExcluded(pItem))
			{
				return D3DERR_INVALIDCALL;
			}

			if (!pItem->m_Computed)
			{
				// Create normal map texture
				if (pItem->m_pNormalTexture == NULL)
				{
					hr = D3DXCreateTexture(pd3dDevice, pItem->m_Width, pItem->m_Height, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &(pItem->m_pNormalTexture));
					if (FAILED(hr))
					{
						pItem->m_pNormalTexture = NULL;
						EXCP::AddException(pItem);
						#ifdef _DEBUG
							MessageBox(NULL, "Create Normal Map Texture Failed!", "Error", MB_OK);
						#endif
						return D3DERR_INVALIDCALL;	// return to normal rendering
					}
				}

				// Compute normal map texture
				float invertSign = pItem->m_Inverted ? -1.0f : 1.0f;
				hr = D3DXComputeNormalMap(pItem->m_pNormalTexture, (IDirect3DTexture9*)pBaseTexture, 0, D3DX_NORMALMAP_MIRROR, D3DX_CHANNEL_LUMINANCE, NORMAL_AMPLITUDE*invertSign);
				if (FAILED(hr))
				{
					
					EXCP::AddException(pItem);
					pItem->m_pNormalTexture->Release();
					pItem->m_pNormalTexture = NULL;
					#ifdef _DEBUG
						MessageBox(NULL, "Compute Normal Map Texture Failed!", "Error", MB_OK);
						DB::savePrimitiveStatesToFile(Type, minIndex, NumVertices, startIndex, primCount, 
							0, Stride, 0, (D3DTRANSFORMSTATETYPE)TransformStateType, 0,
							baseVertexIndex, 0, pBaseTexture, "failTex.txt");
						D3DXSaveTextureToFile("failTex.bmp", D3DXIFF_BMP, pBaseTexture, NULL);
					#endif
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
		pd3dDevice->SetRenderState(D3DRS_TEXTUREFACTOR, g_dwAlphaValue);

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
			pd3dDevice->SetRenderState(D3DRS_TEXTUREFACTOR, g_dwNormalTextureAlpha);
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
		pd3dDevice->SetTexture(1, NULL);
		pd3dDevice->SetTexture(2, NULL);
		pd3dDevice->SetTexture(3, NULL);
		restoreTextureStageStates(pd3dDevice);
		restoreRenderStates(pd3dDevice);
		pd3dDevice->SetTexture(0, pBaseTexture);
		return D3D_OK;
	}

	void backupTextureStageStates(IDirect3DDevice9* pd3dDevice)
	{
		pd3dDevice->GetTextureStageState(0, D3DTSS_COLORARG1, &g_dwColorArg1_0);
		pd3dDevice->GetTextureStageState(0, D3DTSS_COLOROP, &g_dwColorOp_0);
		pd3dDevice->GetTextureStageState(0, D3DTSS_COLORARG2, &g_dwColorArg2_0);
		pd3dDevice->GetTextureStageState(0, D3DTSS_ALPHAOP, &g_dwAlphaOp_0);
		pd3dDevice->GetTextureStageState(0, D3DTSS_ALPHAARG1, &g_dwAlphaArg1_0);
		pd3dDevice->GetTextureStageState(0, D3DTSS_ALPHAARG2, &g_dwAlphaArg2_0);
		pd3dDevice->GetTextureStageState(0, D3DTSS_TEXCOORDINDEX, &g_dwTexCoordIndex_0);
	}
	void restoreTextureStageStates(IDirect3DDevice9* pd3dDevice)
	{
		pd3dDevice->SetTextureStageState(0,D3DTSS_COLORARG1, g_dwColorArg1_0);
		pd3dDevice->SetTextureStageState(0,D3DTSS_COLOROP, g_dwColorOp_0);
		pd3dDevice->SetTextureStageState(0,D3DTSS_COLORARG2, g_dwColorArg2_0);
		pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, g_dwAlphaOp_0);
		pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, g_dwAlphaArg1_0);
		pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, g_dwAlphaArg2_0);
		pd3dDevice->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, g_dwTexCoordIndex_0);
	}
	void backupRenderStates(IDirect3DDevice9* pd3dDevice)
	{
		pd3dDevice->GetRenderState(D3DRS_ALPHATESTENABLE, &g_dwAlphaTestEnable);
		pd3dDevice->GetRenderState(D3DRS_ALPHABLENDENABLE, &g_dwAlphaBlendEnable);
		pd3dDevice->GetRenderState(D3DRS_SRCBLEND, &g_dwSrcBlend);
		pd3dDevice->GetRenderState(D3DRS_DESTBLEND, &g_dwDestBlend);
		pd3dDevice->GetRenderState(D3DRS_TEXTUREFACTOR, &g_dwTextureFactor);
	}
	void restoreRenderStates(IDirect3DDevice9* pd3dDevice)
	{
		pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, g_dwAlphaTestEnable);
		pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, g_dwAlphaBlendEnable);
		pd3dDevice->SetRenderState(D3DRS_SRCBLEND, g_dwSrcBlend);
		pd3dDevice->SetRenderState(D3DRS_DESTBLEND, g_dwDestBlend);
		pd3dDevice->SetRenderState(D3DRS_TEXTUREFACTOR, g_dwTextureFactor);
	}

	#pragma region Standard Procedure Functions
	void onCreateDevice(IDirect3DDevice9* pd3dDevice)
	{
		Init(pd3dDevice);
	}

	void onLostDevice()
	{
	}

	void onResetDevice(IDirect3DDevice9* pd3dDevice)
	{
	}

	void onDestroy(IDirect3DDevice9* pd3dDevice)
	{
		g_texTable.cleanup();
	}
	#pragma endregion
}
