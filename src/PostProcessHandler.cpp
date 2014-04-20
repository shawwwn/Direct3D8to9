#include "PostProcessHandler.h"

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
	IDirect3DTexture9* g_pScreenRenderSource=NULL;
	IDirect3DTexture9* g_pScreenRenderTarget=NULL;

	PostProcess g_PostProcessChain[1];

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

		// Get device parameters
		D3DDISPLAYMODE* pMode;
		hr = pd3dDevice->GetDisplayMode(D3DADAPTER_DEFAULT, pMode);
		if (FAILED(hr))
			return hr;
		g_deviceWidth = pMode->Width;
		g_deviceHeight = pMode->Height;

		// Create textures for rendering
		hr = pd3dDevice->CreateTexture(g_deviceWidth, g_deviceHeight, 1,
									   D3DUSAGE_RENDERTARGET,
									   D3DFMT_A16B16G16R16F,
									   D3DPOOL_DEFAULT,
									   &g_pScreenRenderSource, NULL);
		if (FAILED(hr))
			return hr;
		hr = pd3dDevice->CreateTexture(g_deviceWidth, g_deviceHeight, 1,
			                           D3DUSAGE_RENDERTARGET,
									   D3DFMT_A16B16G16R16F,
									   D3DPOOL_DEFAULT,
									   &g_pScreenRenderTarget, NULL);
		if (FAILED(hr))
			return hr;

		// Initialize effects
		// TODO: Use vector implementation on PostProcessChain
		g_PostProcessChain[0].Init(pd3dDevice, "PP_ColorBloomH.fx");
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
		IDirect3DSurface9* pOldRT;
		pd3dDevice->GetRenderTarget(0, &pOldRT);

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
		LPDIRECT3DSURFACE9 t_Surface;
		g_pScreenRenderSource->GetSurfaceLevel(0, &t_Surface);
		pd3dDevice->StretchRect(pOldRT, NULL, t_Surface, NULL, D3DTEXF_NONE);
		t_Surface->Release();

		//
		// Set render target (texture/backbuffer)
		//
		RenderToTexture(pd3dDevice, g_pScreenRenderTarget);
		//RenderToBackBuffer(pd3dDevice);

		//
		// Render the quad
		//
		if(SUCCEEDED(pd3dDevice->BeginScene()))
		{
			// TODO: Add render logic...
		}

		//
		// Restore original render target (back buffer)
		//
		pd3dDevice->SetRenderTarget(0, pOldRT);
		pOldRT->Release();
	}

	/*
	 * Set Render target to texture
	 */
	HRESULT RenderToTexture(IDirect3DDevice9* pd3dDevice, IDirect3DTexture9* pTexture)
	{
		IDirect3DSurface9* t_Surface = NULL;
		pTexture->GetSurfaceLevel(0, &t_Surface);
		pd3dDevice->SetRenderTarget(0, t_Surface);
		t_Surface->Release();
	}

	/*
	 * Set Render target to backbuffer (Unsafe)
	 */
	HRESULT RenderToBackBuffer(IDirect3DDevice9* pd3dDevice)
	{
		IDirect3DSurface9* t_Surface = NULL;
		pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &t_Surface);
		pd3dDevice->SetRenderTarget(0, t_Surface);
		t_Surface->Release();
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