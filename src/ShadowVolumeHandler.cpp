#include "ShadowVolumeHandler.h"

namespace SV {
	IDirect3DDevice9* m_pDevice = NULL;
	ShadowTable g_shwTable;
	bool g_rendered = false;
	LPDIRECT3DVERTEXBUFFER9 g_pBigSquareVB = NULL;
	ShadowVolume g_baseShadow;
	UINT g_deviceHeight = 0;
	UINT g_deviceWidth = 0;
	UINT g_NumVertices_last = 0;
	UINT g_PrimCount_last = 0;
	int g_shwParam_last = -1;


	//
	// Compute light vector then generate shadow mesh
	//
	void GenerateShadow(IDirect3DDevice9* pd3dDevice,
						IDirect3DVertexBuffer9* pVertexBuffer, IDirect3DIndexBuffer9* pIndexBuffer,
						DWORD baseVertexIndex, DWORD startIndex,
						DWORD numVertices, DWORD primCount,
						int inversion)
	{
		D3DXVECTOR3 vLight;					// light vector in object space
		D3DXVECTOR3* pRefLight = NULL;		// reference light value

		/*
		// Get the global lightning. Deal with for extreme value(open dialog, etc.)
		D3DLIGHT9 light;
		pd3dDevice->GetLight(0, &light);
		D3DVECTOR& wc3Light = light.Direction;
		*/

		if (inversion & SHW_FLYING_UNIT)
			pRefLight = const_cast<D3DXVECTOR3*>(&wc3Light_fly);
		else
			pRefLight = const_cast<D3DXVECTOR3*>(&wc3Light);

		if (inversion & SHW_USE_TRANSFORMATION)
		{
			// Transform the light vector to be in object space
			D3DXMATRIX worldMax;
			pd3dDevice->GetTransform(D3DTS_WORLD, &worldMax);
			D3DXMatrixInverse((D3DXMATRIXA16*)&worldMax, NULL, (D3DXMATRIXA16*)&worldMax); // inverse world matrix
			vLight.x = pRefLight->x*worldMax._11 + pRefLight->y*worldMax._21 + pRefLight->z*worldMax._31; // + maxInvesed._41;
			vLight.y = pRefLight->x*worldMax._12 + pRefLight->y*worldMax._22 + pRefLight->z*worldMax._32; // + maxInvesed._42;
			vLight.z = pRefLight->x*worldMax._13 + pRefLight->y*worldMax._23 + pRefLight->z*worldMax._33; // + maxInvesed._43;
			//D3DXVec3Normalize(&vLight, &vLight);
		}
		else
			vLight = *pRefLight; // Use hardcoded light vector
		
		
		if (!(inversion & SHW_X_INVERTED))
			vLight.x *= -1;
		if (!(inversion & SHW_Y_INVERTED))
			vLight.y *= -1;
		if (!(inversion & SHW_Z_INVERTED))
			vLight.z *= -1;

		g_baseShadow.Reset();
		g_baseShadow.BuildFromStreamBuffer(pVertexBuffer, pIndexBuffer, baseVertexIndex, startIndex, numVertices, primCount, vLight);
	}

	//
	// For debug
	//
	void RenderShadowVolume(IDirect3DDevice9* pd3dDevice)
	{
		g_baseShadow.Render(pd3dDevice);
	}

	//
	// Render shadow information to stencil buffer
	//
	HRESULT RenderShadow(IDirect3DDevice9* pd3dDevice)
	{
		IDirect3DStateBlock9* pStateBlock = NULL;
		pd3dDevice->CreateStateBlock(D3DSBT_ALL, &pStateBlock);

		// Disable z-buffer writes (note: z-testing still occurs), and enable the
		// stencil-buffer
		SetRenderStateSafe(pd3dDevice, D3DRS_ZWRITEENABLE,	FALSE);
		SetRenderStateSafe(pd3dDevice, D3DRS_STENCILENABLE,	TRUE);

		// If ztest passes, inc/decrement stencil buffer value
		SetRenderStateSafe(pd3dDevice, D3DRS_STENCILREF,	0x1);
		SetRenderStateSafe(pd3dDevice, D3DRS_STENCILPASS,	D3DSTENCILOP_INCR);
	
		// Make sure that no pixels get drawn to the frame buffer
		SetRenderStateSafe(pd3dDevice, D3DRS_ALPHABLENDENABLE,	TRUE);
		SetRenderStateSafe(pd3dDevice, D3DRS_SRCBLEND,			D3DBLEND_ZERO);
		SetRenderStateSafe(pd3dDevice, D3DRS_DESTBLEND,			D3DBLEND_ONE);

		// TODO: Check device caps
		if(true)
		{
			// With 2-sided stencil, we can avoid rendering twice:
			SetRenderStateSafe(pd3dDevice, D3DRS_TWOSIDEDSTENCILMODE,	TRUE);
			SetRenderStateSafe(pd3dDevice, D3DRS_CCW_STENCILPASS,		D3DSTENCILOP_DECR);
			SetRenderStateSafe(pd3dDevice, D3DRS_CULLMODE,				D3DCULL_NONE);

			// Draw both sides of shadow volume in stencil/z only
			g_baseShadow.Render( pd3dDevice );

			SetRenderStateSafe(pd3dDevice, D3DRS_TWOSIDEDSTENCILMODE,	FALSE);
		}
		else
		{
			// Draw front-side of shadow volume in stencil/z only
			SetRenderStateSafe(pd3dDevice, D3DRS_CULLMODE,		D3DCULL_CCW);
			g_baseShadow.Render( pd3dDevice );

			// Now reverse cull order so back sides of shadow volume are written.
			SetRenderStateSafe(pd3dDevice, D3DRS_CULLMODE,		D3DCULL_CW);

			// Decrement stencil buffer value
			SetRenderStateSafe(pd3dDevice, D3DRS_STENCILPASS,	D3DSTENCILOP_DECR);

			// Draw back-side of shadow volume in stencil/z only
			g_baseShadow.Render( pd3dDevice );
		}

		pd3dDevice->EndStateBlock(&pStateBlock);
		pStateBlock->Apply();
		SAFE_RELEASE(pStateBlock);
		return S_OK;
	}

	//
	//	Use stencil buffer as a mask. draw shadows to the scene
	//
	HRESULT DrawShadow(IDirect3DDevice9* pd3dDevice)
	{
		IDirect3DStateBlock9* pStateBlock = NULL;
		pd3dDevice->CreateStateBlock(D3DSBT_ALL, &pStateBlock);

		// Set renderstates (disable z-buffering, enable stencil, disable fog, and
		// turn on alphablending)
		SetRenderStateSafe(pd3dDevice, D3DRS_ZENABLE,			FALSE);
		SetRenderStateSafe(pd3dDevice, D3DRS_STENCILENABLE,		TRUE);
		SetRenderStateSafe(pd3dDevice, D3DRS_FOGENABLE,			FALSE);
		SetRenderStateSafe(pd3dDevice, D3DRS_ALPHABLENDENABLE,	TRUE);
		SetRenderStateSafe(pd3dDevice, D3DRS_SRCBLEND,			D3DBLEND_SRCALPHA);
		SetRenderStateSafe(pd3dDevice, D3DRS_DESTBLEND,			D3DBLEND_INVSRCALPHA);
		SetRenderStateSafe(pd3dDevice, D3DRS_ALPHATESTENABLE,	FALSE);
		
		// Only write where stencil val >= 1 (count indicates # of shadows that
		// overlap that pixel)
		SetRenderStateSafe(pd3dDevice, D3DRS_STENCILREF,		0x1);
		SetRenderStateSafe(pd3dDevice, D3DRS_STENCILFUNC,		D3DCMP_LESSEQUAL);
		SetRenderStateSafe(pd3dDevice, D3DRS_CULLMODE,			D3DCULL_CCW); // counter clock-wise render triangles
		pd3dDevice->EndStateBlock(&pStateBlock);

		// Draw a big, gray square
		pd3dDevice->SetFVF( SHADOWVERTEX::FVF );
		pd3dDevice->SetStreamSource( 0, g_pBigSquareVB, 0, sizeof(SHADOWVERTEX) );
		pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );

		pStateBlock->Apply();
		SAFE_RELEASE(pStateBlock);
		return S_OK;
	}

	void setupScreenDimensions(IDirect3DDevice9* pd3dDevice)
	{
		// Get screen dimensions
		IDirect3DSurface9* t_pSurface = NULL;
		D3DSURFACE_DESC t_Desc;
		pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &t_pSurface);
		t_pSurface->GetDesc(&t_Desc);
		g_deviceWidth = t_Desc.Width;
		g_deviceHeight = t_Desc.Height;
		SAFE_RELEASE(t_pSurface);
	}

	HRESULT initTemporaryResources(IDirect3DDevice9* pd3dDevice)
	{
		pd3dDevice->CreateVertexBuffer(4*sizeof(SHADOWVERTEX), D3DUSAGE_WRITEONLY, SHADOWVERTEX::FVF, D3DPOOL_DEFAULT, &g_pBigSquareVB, NULL);

		SHADOWVERTEX* v;
		FLOAT sx = (FLOAT)g_deviceWidth;
		FLOAT sy = (FLOAT)g_deviceHeight;
		g_pBigSquareVB->Lock( 0, 0, (void**)&v, 0 );
		v[0].p = D3DXVECTOR4(  0, sy, 0.0f, 1.0f );
		v[1].p = D3DXVECTOR4(  0,  0, 0.0f, 1.0f );
		v[2].p = D3DXVECTOR4( sx, sy, 0.0f, 1.0f );
		v[3].p = D3DXVECTOR4( sx,  0, 0.0f, 1.0f );
		v[0].color = 0x6f000000;
		v[1].color = 0x6f000000;
		v[2].color = 0x6f000000;
		v[3].color = 0x6f000000;
		g_pBigSquareVB->Unlock();

		return S_OK;
	}

	HRESULT releaseTemporaryResources()
	{
		SAFE_RELEASE(g_pBigSquareVB);
		return D3D_OK;
	}


	//
	// Standard Procedure Functions
	//
	void onCreateDevice(IDirect3DDevice9* pd3dDevice)
	{
		m_pDevice = pd3dDevice;
		InitShadowTable(g_shwTable);
		setupScreenDimensions(pd3dDevice);
		initTemporaryResources(pd3dDevice);
	}
	void onLostDevice()
	{
		releaseTemporaryResources();
	}
	void onResetDevice(IDirect3DDevice9* pd3dDevice)
	{
		setupScreenDimensions(pd3dDevice);
		initTemporaryResources(pd3dDevice);
	}
	void onDestroy(IDirect3DDevice9* pd3dDevice)
	{
		releaseTemporaryResources();
	}
}