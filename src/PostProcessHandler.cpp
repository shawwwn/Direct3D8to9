#include "PostProcessHandler.h"

#include <stdio.h>
#include <stdlib.h>

namespace PP{
	#pragma region Variables Definition
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

	IDirect3DVertexBuffer9* g_pVB=NULL;

	IDirect3DVertexDeclaration9* g_pVertDeclPP=NULL;
	IDirect3DTexture9* g_pSourceRT_Texture=NULL;
	IDirect3DTexture9* g_pTargetRT_Texture=NULL;

	PostProcess g_PostProcessChain[MAX_POST_PROCESS_COUNT];
	int post_process_count = 0;

	bool g_presented=false;

	// Vertex declaration for post-processing
	const D3DVERTEXELEMENT9 PPVERT::Decl[4] =
	{
		{ 0, 0,  D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 },
		{ 0, 16, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  0 },
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  1 },
		D3DDECL_END()
	};
	#pragma endregion

	#pragma region Function Defintions

	/**
	*	Global initialization
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

		// Create Vertex Buffer
		SetupVertexBuffer(pd3dDevice);

		// Initialize effects
		// TODO: Use vector to iterate PostProcessChain
		g_PostProcessChain[0].Init(pd3dDevice, SHADER_BLOOM_H);
		post_process_count = 1;
		return hr;
	}

	/**
	*	Set up vertex buffer, this must be called each time the device changes its resolution
	*/
	HRESULT SetupVertexBuffer(IDirect3DDevice9* pd3dDevice)
	{
		// Set up our quad
		PPVERT Quad[4] =
		{
			{ -0.5f,				-0.5f,						1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f },
			{ g_deviceWidth-0.5f,	-0.5f,						1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f },
			{ -0.5f,				g_deviceHeight-0.5f,		1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f },
			{ g_deviceWidth-0.5f,	g_deviceHeight-0.5f,		1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f }
		};

		// Create a vertex buffer out of the quad
		HRESULT hr = pd3dDevice->CreateVertexBuffer(sizeof(PPVERT)*4,
													D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC,
													0,
													D3DPOOL_DEFAULT,
													&g_pVB,
													NULL );
		if(FAILED(hr))
			return hr;

		// Fill the vertex buffer
		LPVOID pVBData;
		if(SUCCEEDED(g_pVB->Lock(0, 0, &pVBData, D3DLOCK_DISCARD)))
		{
			CopyMemory(pVBData, Quad, sizeof(Quad));
			g_pVB->Unlock();
		}
		else
			return D3DERR_INVALIDCALL;
		return D3D_OK;
	}

	/**
	*	Swap g_pTargetRT_Texture/g_pSourceRT_Texture
	*/
	void Swap()
	{
		IDirect3DTexture9* pTempTexture = g_pTargetRT_Texture;
		g_pTargetRT_Texture = g_pSourceRT_Texture;
		g_pSourceRT_Texture = pTempTexture;
		pTempTexture = NULL;
	}

	/**
	*	Perform Post Process on a device
	*/
	HRESULT PerformPostProcess(IDirect3DDevice9* pd3dDevice, RenderMenthod method)
	{
		//
		// Preparation
		//
		IDirect3DSurface9* pOldRT_Surface = NULL;				// original render target(backbuffer)
		pd3dDevice->GetRenderTarget(0, &pOldRT_Surface);		// save the original render target
		IDirect3DSurface9* pRT_Surface = NULL;					// current render target
		backupStates(pd3dDevice);								// backup render states

		if (method == RENDER_TO_TEXTURE)
		{
			// Copy backbuffer to target texture(since we are going to swap the soure and target textures)
			IDirect3DSurface9* t_pSurface = NULL;
			g_pTargetRT_Texture->GetSurfaceLevel(0, &t_pSurface);
			pd3dDevice->StretchRect(pOldRT_Surface, NULL, t_pSurface, NULL, D3DTEXF_NONE);
			t_pSurface->Release();
		}
		

		//
		// Post Process Loop
		//
		for (int i=0; i<post_process_count; i++)
		{
			PostProcess &PProcess = g_PostProcessChain[i];

			//
			//	Initialize soure/target
			//
			if (method == RENDER_TO_TEXTURE)
			{
				// Swap the target texture with the source texture
				Swap();
				// Set texture surface as new render target
				g_pTargetRT_Texture->GetSurfaceLevel(0, &pRT_Surface);
				pd3dDevice->SetRenderTarget(0, pRT_Surface);
			}
			else
			{
				// Copy back buffer to source texture (g_pScreenRenderSource)
				IDirect3DSurface9* t_pSurface = NULL;
				g_pSourceRT_Texture->GetSurfaceLevel(0, &t_pSurface);
				pd3dDevice->StretchRect(pOldRT_Surface, NULL, t_pSurface, NULL, D3DTEXF_NONE);
				t_pSurface->Release();
				// We dont need to set render target here because backbuffer is already the default render target.
				pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pRT_Surface);
			}


			//
			// Render the quad
			//
			if(SUCCEEDED(pd3dDevice->BeginScene()))
			{
				PProcess.m_pEffect->SetTechnique("PostProcess");
				pd3dDevice->SetVertexDeclaration(g_pVertDeclPP);	// Set the vertex declaration
				// Draw the quad
				UINT cPasses, p;
				PProcess.m_pEffect->Begin(&cPasses, 0);
				PProcess.m_pEffect->SetTexture(PProcess.m_hTexScene, g_pSourceRT_Texture); 
				PProcess.m_pEffect->SetTexture(PProcess.m_hTexSource, g_pSourceRT_Texture);
				PProcess.m_pEffect->CommitChanges();
				// clear the previous screen
				pd3dDevice->Clear(0L, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0L);
				// Render
				for(p = 0; p < cPasses; ++p)
				{
					PProcess.m_pEffect->BeginPass(p);
					pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(PPVERT));
					pd3dDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
					PProcess.m_pEffect->EndPass();
				}
				PProcess.m_pEffect->End();
				pd3dDevice->EndScene(); // End the scene
			}
		}


		//
		// Restore render states
		//
		restoreStates(pd3dDevice);


		//
		// Output render result to the screen(not needed in RENDER_TO_BACKBUFFER)
		//
		if (method == RENDER_TO_TEXTURE)
		{
			
			pd3dDevice->SetRenderTarget(0, pOldRT_Surface);
			pd3dDevice->StretchRect(pRT_Surface, 0, pOldRT_Surface, 0, D3DTEXF_NONE);
		}
		pRT_Surface->Release();
		pOldRT_Surface->Release();
		return D3D_OK;
	}

	/**
	*	Backup render states
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

	/**
	*	Restore render states
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
	#pragma endregion
}