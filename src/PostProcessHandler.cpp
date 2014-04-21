#include "PostProcessHandler.h"

#include <stdio.h>
#include <stdlib.h>

namespace PP{
	//
	// Gobal Variables Definition
	//
	DWORD dwZEnable=0;
	DWORD dwZWriteEnable=0;
	DWORD dwLocalViewer=0;
	DWORD dwAlphaTestEnable=0;
	DWORD dwCullMode=0;
	DWORD dwAlphaBlendEnable=0;
	DWORD dwZFunc=0;
	DWORD dwSrcBlend=0;
	DWORD dwDestBlend=0;
	DWORD dwFogEnable=0;
	DWORD dwLighting=0;
	
	UINT g_deviceWidth=0;
	UINT g_deviceHeight=0;

	IDirect3DVertexDeclaration9* g_pVertDeclPP=NULL;
	IDirect3DTexture9* g_pSourceRT_Texture=NULL;
	IDirect3DTexture9* g_pTargetRT_Texture=NULL;

	PostProcess g_PostProcessChain[1];

	bool g_presented=false;

	// Vertex declaration for post-processing
	const D3DVERTEXELEMENT9 PPVERT::Decl[4] =
	{
		{ 0, 0,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 },
		{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  0 },
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  1 },
		D3DDECL_END()
	};

	//
	// Function Defintions
	//

	/*
	 * Global initialization
	 */
	HRESULT InitGobals(IDirect3DDevice9* pd3dDevice)
	{
		// Create vertex declaration for post-process
		HRESULT hr;
		if(FAILED(hr = pd3dDevice->CreateVertexDeclaration(PPVERT::Decl, &g_pVertDeclPP)))
		{
			MessageBox(NULL, "Create Vertex Declaration Fail!", "Error", MB_OK);
			return hr;
		}
		
		// TODO: fix the crash
		/*
		// Get screen dimensions
		D3DVIEWPORT9 *pViewport=NULL;
		pd3dDevice->GetViewport(pViewport);
		g_deviceWidth = (UINT)pViewport->Width;
		g_deviceHeight = (UINT)pViewport->Height;
		pViewport=NULL;
		*/

		// Get screen dimensions
		IDirect3DSurface9* t_pSurface = NULL;
		D3DSURFACE_DESC t_Desc;
		pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &t_pSurface);
		t_pSurface->GetDesc(&t_Desc);
		g_deviceWidth = t_Desc.Width;
		g_deviceHeight = t_Desc.Height;
		t_pSurface->Release();

		// Create textures for rendering
		hr = pd3dDevice->CreateTexture(g_deviceWidth, g_deviceHeight, 1,
									   D3DUSAGE_RENDERTARGET,
									   D3DFMT_A16B16G16R16F,
									   D3DPOOL_DEFAULT,
									   &g_pSourceRT_Texture, NULL);
		if (FAILED(hr))
		{
			MessageBox(NULL, "Fail to create texture!", "Error", MB_OK);
			return hr;
		}
		hr = pd3dDevice->CreateTexture(g_deviceWidth, g_deviceHeight, 1,
			                           D3DUSAGE_RENDERTARGET,
									   D3DFMT_A16B16G16R16F,
									   D3DPOOL_DEFAULT,
									   &g_pTargetRT_Texture, NULL);
		if (FAILED(hr))
			return hr;

		// Initialize effects
		// TODO: Use vector to iterate PostProcessChain
		g_PostProcessChain[0].Init(pd3dDevice, SHADER_BLOOM_H);
		return hr;
	}

	/*
	 * Perform Post Process on a device
	 */
	HRESULT PerformPostProcess(IDirect3DDevice9* pd3dDevice)
	{
		HRESULT hr;
		//
		// Save original render target so we can restore it later
		//
		IDirect3DSurface9* pOldRT_Surface;
		pd3dDevice->GetRenderTarget(0, &pOldRT_Surface);

		//
		//	backup render states
		//
		backupStates(pd3dDevice);
		
		//
		// Set up our quad
		//
		PPVERT Quad[4] =
		{
			{ -0.5f,				-0.5f,						1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f },
			{ g_deviceWidth-0.5f,	-0.5f,						1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f },
			{ -0.5f,				g_deviceHeight-0.5f,		1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f },
			{ g_deviceWidth-0.5f,	g_deviceHeight-0.5f,		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }
		};

		//
		// Create a vertex buffer out of the quad
		//
		IDirect3DVertexBuffer9* pVB;
		hr = pd3dDevice->CreateVertexBuffer(sizeof(PPVERT)*4,
											D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC,
											0,
											D3DPOOL_DEFAULT,
											&pVB,
											NULL );
		if(FAILED(hr))
			return hr;

		//
		// Fill the vertex buffer
		//
		LPVOID pVBData;
		if(SUCCEEDED(pVB->Lock(0, 0, &pVBData, D3DLOCK_DISCARD)))
		{
			CopyMemory(pVBData, Quad, sizeof(Quad));
			pVB->Unlock();
		}

		//
		// Copy back buffer to source texture (g_pScreenRenderSource)
		//
		LPDIRECT3DSURFACE9 t_pSurface;
		g_pSourceRT_Texture->GetSurfaceLevel(0, &t_pSurface);
		pd3dDevice->StretchRect(pOldRT_Surface, NULL, t_pSurface, NULL, D3DTEXF_NONE);
		t_pSurface->Release();

		//
		// Set new render target (texture/backbuffer)
		//
		LPDIRECT3DSURFACE9 pNewRT_Surface = RenderToTexture(pd3dDevice, g_pTargetRT_Texture);
		//LPDIRECT3DSURFACE9 pNewRT_Surface = RenderToBackBuffer(pd3dDevice);

		//
		// Render the quad
		//
		if(SUCCEEDED(pd3dDevice->BeginScene()))
		{
			// TODO: add loop to iterate the effect chain
			g_PostProcessChain[0].m_pEffect->SetTechnique("PostProcess");
			pd3dDevice->SetVertexDeclaration(g_pVertDeclPP);	// Set the vertex declaration
			// Draw the quad
			UINT cPasses, p;
			g_PostProcessChain[0].m_pEffect->Begin(&cPasses, 0);
			g_PostProcessChain[0].m_pEffect->SetTexture(g_PostProcessChain[0].m_hTexScene, g_pSourceRT_Texture); 
			g_PostProcessChain[0].m_pEffect->SetTexture(g_PostProcessChain[0].m_hTexSource, g_pSourceRT_Texture);
			g_PostProcessChain[0].m_pEffect->CommitChanges();
			// clear the previous screen
			pd3dDevice->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0L);
			//
			// Render
			//
			for(p = 0; p < cPasses; ++p)
			{
				g_PostProcessChain[0].m_pEffect->BeginPass(p);
				pd3dDevice->SetStreamSource(0, pVB, 0, sizeof(PPVERT));
				pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
				g_PostProcessChain[0].m_pEffect->EndPass();
			}
			g_PostProcessChain[0].m_pEffect->End();
			pd3dDevice->EndScene(); // End the scene
		}
		pVB->Release(); // Release the vertex buffer

		//
		// Restore render states
		//
		restoreStates(pd3dDevice);

		//
		// Restore original render target (back buffer)
		//
		pd3dDevice->SetRenderTarget(0, pOldRT_Surface);
		
		//
		// Draw pNewRT_Surface onto the screen
		//
		pd3dDevice->StretchRect(pNewRT_Surface, 0, pOldRT_Surface, 0, D3DTEXF_NONE);
		pNewRT_Surface->Release();
		pOldRT_Surface->Release();
	
		return D3D_OK;
	}

	/*
	 * Set Render target to texture
	 * Note: will create a new reference to the surface
	 * @return - pointer to target texture surface
	 */
	IDirect3DSurface9* RenderToTexture(IDirect3DDevice9* pd3dDevice, IDirect3DTexture9* pTexture)
	{
		IDirect3DSurface9* pSurface = NULL;
		pTexture->GetSurfaceLevel(0, &pSurface);
		pd3dDevice->SetRenderTarget(0, pSurface);
		return pSurface;
	}

	/*
	 * Set Render target to backbuffer (Unsafe)
	 * Note: will create a new reference to the surface
	 * @return - pointer to the backbuffer surface
	 */
	IDirect3DSurface9* RenderToBackBuffer(IDirect3DDevice9* pd3dDevice)
	{
		IDirect3DSurface9* pSurface = NULL;
		pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pSurface);
		pd3dDevice->SetRenderTarget(0, pSurface);
		return pSurface;
	}

	/*
	 * Backup render states
	 */
	void backupStates(IDirect3DDevice9* pd3dDevice)
	{
		pd3dDevice->GetRenderState(D3DRS_ZENABLE, &dwZEnable);
		pd3dDevice->SetRenderState(D3DRS_ZENABLE, 1);

		pd3dDevice->GetRenderState(D3DRS_LOCALVIEWER, &dwLocalViewer);
		pd3dDevice->SetRenderState(D3DRS_LOCALVIEWER, 1);

		pd3dDevice->GetRenderState(D3DRS_ZWRITEENABLE, &dwZWriteEnable);
		pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, 1);

		pd3dDevice->GetRenderState(D3DRS_ALPHATESTENABLE, &dwAlphaTestEnable);
		pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, 0);

		pd3dDevice->GetRenderState(D3DRS_CULLMODE, &dwCullMode);
		pd3dDevice->SetRenderState(D3DRS_CULLMODE, 3); //1

		pd3dDevice->GetRenderState(D3DRS_ALPHABLENDENABLE, &dwAlphaBlendEnable);
		pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, 1);

		pd3dDevice->GetRenderState(D3DRS_ZFUNC, &dwZFunc);
		pd3dDevice->SetRenderState(D3DRS_ZFUNC, 4);

		pd3dDevice->GetRenderState(D3DRS_DESTBLEND, &dwDestBlend);
		//pd3dDevice->SetRenderState(D3DRS_DESTBLEND, 6);
		pd3dDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

		pd3dDevice->GetRenderState(D3DRS_SRCBLEND, &dwSrcBlend);
		pd3dDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);

		pd3dDevice->GetRenderState(D3DRS_FOGENABLE, &dwFogEnable);
		pd3dDevice->SetRenderState(D3DRS_FOGENABLE, 0);
	
		pd3dDevice->GetRenderState(D3DRS_LIGHTING, &dwLighting);
		pd3dDevice->SetRenderState(D3DRS_LIGHTING, 0);
	}


	/*
	 * Restore render states
	 */
	void restoreStates(IDirect3DDevice9* pd3dDevice)
	{
		pd3dDevice->SetRenderState(D3DRS_ZENABLE, dwZEnable);
		pd3dDevice->SetRenderState(D3DRS_LOCALVIEWER, dwLocalViewer);
		pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE, dwZWriteEnable);
		pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, dwAlphaTestEnable);
		pd3dDevice->SetRenderState(D3DRS_CULLMODE, dwCullMode);
		pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, dwAlphaBlendEnable);
		pd3dDevice->SetRenderState(D3DRS_ZFUNC, dwZFunc);
		pd3dDevice->SetRenderState(D3DRS_DESTBLEND, dwDestBlend);
		pd3dDevice->SetRenderState(D3DRS_SRCBLEND, dwSrcBlend);
		pd3dDevice->SetRenderState(D3DRS_FOGENABLE, dwFogEnable);
		pd3dDevice->SetRenderState(D3DRS_LIGHTING, dwLighting);
	}

}