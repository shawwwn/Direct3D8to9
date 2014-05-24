#include "ShadowVolumeHandler.h"

namespace SV {
	bool g_rendered = false;
	LPDIRECT3DVERTEXBUFFER9 g_pBigSquareVB = NULL;
	ShadowVolume g_HumBaseShadow;
	UINT g_deviceHeight = 0;
	UINT g_deviceWidth = 0;

	void GenerateShadow(IDirect3DDevice9* pd3dDevice, IDirect3DVertexBuffer9* pVertexBuffer, IDirect3DIndexBuffer9* pIndexBuffer, DWORD startIndex, DWORD primCount, DWORD baseVertexIndex, D3DMATRIX* pMatrix)
	{
		/*
		// Transform the light vector to be in object space
		D3DXVECTOR3 tLight;
		D3DLIGHT9 light;
		pd3dDevice->GetLight(0, &light);
		D3DVECTOR& vLight = light.Direction;
		D3DXMATRIXA16 maxInvesed;
		D3DXMatrixInverse( &maxInvesed, NULL, (D3DXMATRIXA16*)pMatrix );
		tLight.x = vLight.x*maxInvesed._11 + vLight.y*maxInvesed._21 + vLight.z*maxInvesed._31 + maxInvesed._41;
		tLight.y = vLight.x*maxInvesed._12 + vLight.y*maxInvesed._22 + vLight.z*maxInvesed._32 + maxInvesed._42;
		tLight.z = vLight.x*maxInvesed._13 + vLight.y*maxInvesed._23 + vLight.z*maxInvesed._33 + maxInvesed._43;
		tLight.z *= -1;
		*/
		//D3DXVec3Normalize(&tLight, &tLight);

		D3DXVECTOR3 tLight(-25, -25, 25);	// hardcoded directional light
	
		g_HumBaseShadow.Reset();
		g_HumBaseShadow.BuildFromStreamBuffer(pVertexBuffer, pIndexBuffer, startIndex, primCount, baseVertexIndex, tLight);
	}

	//
	// For debug
	//
	void RenderShadowVolume(IDirect3DDevice9* pd3dDevice)
	{
		g_HumBaseShadow.Render(pd3dDevice);
	}

	//
	// Render shadow information to stencil buffer
	//
	HRESULT RenderShadow(IDirect3DDevice9* pd3dDevice)
	{
		// Backup render states
		DWORD dwZWriteEnable, dwStencilEnable, dwShadeMode, dwStencilFunc, dwStencilZFail, dwStencilFail, dwStencilRef, dwStencilMask,
			  dwStencilWriteMask, dwStencilPass, dwAlphaBlendEnable, dwSrcBlend, dwDestBlend, dwTwoSidedStencilMode, dwCCWStencilFunc,
			  dwCCWStencilZFail, dwCCWStencilFail, dwCCWStencilPass, dwCullMode;
		pd3dDevice->GetRenderState(D3DRS_ZWRITEENABLE,          &dwZWriteEnable);
		pd3dDevice->GetRenderState(D3DRS_STENCILENABLE,         &dwStencilEnable);
		pd3dDevice->GetRenderState(D3DRS_SHADEMODE,             &dwShadeMode);
		pd3dDevice->GetRenderState(D3DRS_STENCILFUNC,           &dwStencilFunc);
		pd3dDevice->GetRenderState(D3DRS_STENCILZFAIL,          &dwStencilZFail);
		pd3dDevice->GetRenderState(D3DRS_STENCILFAIL,           &dwStencilFail);
		pd3dDevice->GetRenderState(D3DRS_STENCILREF,            &dwStencilRef);
		pd3dDevice->GetRenderState(D3DRS_STENCILMASK,           &dwStencilMask);
		pd3dDevice->GetRenderState(D3DRS_STENCILWRITEMASK,      &dwStencilWriteMask);
		pd3dDevice->GetRenderState(D3DRS_STENCILPASS,           &dwStencilPass);
		pd3dDevice->GetRenderState(D3DRS_ALPHABLENDENABLE,      &dwAlphaBlendEnable);
		pd3dDevice->GetRenderState(D3DRS_SRCBLEND,              &dwSrcBlend);
		pd3dDevice->GetRenderState(D3DRS_DESTBLEND,             &dwDestBlend);
		pd3dDevice->GetRenderState(D3DRS_TWOSIDEDSTENCILMODE,   &dwTwoSidedStencilMode);
		pd3dDevice->GetRenderState(D3DRS_CCW_STENCILFUNC,       &dwCCWStencilFunc);
		pd3dDevice->GetRenderState(D3DRS_CCW_STENCILZFAIL,      &dwCCWStencilZFail);
		pd3dDevice->GetRenderState(D3DRS_CCW_STENCILFAIL,       &dwCCWStencilFail);
		pd3dDevice->GetRenderState(D3DRS_CCW_STENCILPASS,       &dwCCWStencilPass);
		pd3dDevice->GetRenderState(D3DRS_CULLMODE,              &dwCullMode);

		// Disable z-buffer writes (note: z-testing still occurs), and enable the
		// stencil-buffer
		pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,  FALSE );
		pd3dDevice->SetRenderState( D3DRS_STENCILENABLE, TRUE );

		// Dont bother with interpolating color
		pd3dDevice->SetRenderState( D3DRS_SHADEMODE,     D3DSHADE_FLAT );

		// Set up stencil compare fuction, reference value, and masks.
		// Stencil test passes if ((ref & mask) cmpfn (stencil & mask)) is true.
		// Note: since we set up the stencil-test to always pass, the STENCILFAIL
		// renderstate is really not needed.
		pd3dDevice->SetRenderState( D3DRS_STENCILFUNC,  D3DCMP_ALWAYS );
		pd3dDevice->SetRenderState( D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP );
		pd3dDevice->SetRenderState( D3DRS_STENCILFAIL,  D3DSTENCILOP_KEEP );

		// If ztest passes, inc/decrement stencil buffer value
		pd3dDevice->SetRenderState( D3DRS_STENCILREF,       0x1 );
		pd3dDevice->SetRenderState( D3DRS_STENCILMASK,      0xffffffff );
		pd3dDevice->SetRenderState( D3DRS_STENCILWRITEMASK, 0xffffffff );
		pd3dDevice->SetRenderState( D3DRS_STENCILPASS,      D3DSTENCILOP_INCR );
	
		// Make sure that no pixels get drawn to the frame buffer
		pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		pd3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_ZERO );
		pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
	
		if( true )
		{
			// With 2-sided stencil, we can avoid rendering twice:
			pd3dDevice->SetRenderState( D3DRS_TWOSIDEDSTENCILMODE, TRUE );
			pd3dDevice->SetRenderState( D3DRS_CCW_STENCILFUNC,  D3DCMP_ALWAYS );
			pd3dDevice->SetRenderState( D3DRS_CCW_STENCILZFAIL, D3DSTENCILOP_KEEP );
			pd3dDevice->SetRenderState( D3DRS_CCW_STENCILFAIL,  D3DSTENCILOP_KEEP );
			pd3dDevice->SetRenderState( D3DRS_CCW_STENCILPASS, D3DSTENCILOP_DECR );

			pd3dDevice->SetRenderState( D3DRS_CULLMODE,  D3DCULL_NONE );

			// Draw both sides of shadow volume in stencil/z only
			g_HumBaseShadow.Render( pd3dDevice );

			pd3dDevice->SetRenderState( D3DRS_TWOSIDEDSTENCILMODE, FALSE );
		}
		else
		{
			// Draw front-side of shadow volume in stencil/z only
			pd3dDevice->SetRenderState( D3DRS_CULLMODE,   D3DCULL_CCW );
			g_HumBaseShadow.Render( pd3dDevice );

			// Now reverse cull order so back sides of shadow volume are written.
			pd3dDevice->SetRenderState( D3DRS_CULLMODE,   D3DCULL_CW );

			// Decrement stencil buffer value
			pd3dDevice->SetRenderState( D3DRS_STENCILPASS, D3DSTENCILOP_DECR );

			// Draw back-side of shadow volume in stencil/z only
			g_HumBaseShadow.Render( pd3dDevice );
		}

		// Restore render states
		pd3dDevice->SetRenderState(D3DRS_ZWRITEENABLE,          dwZWriteEnable);
		pd3dDevice->SetRenderState(D3DRS_STENCILENABLE,         dwStencilEnable);
		pd3dDevice->SetRenderState(D3DRS_SHADEMODE,             dwShadeMode);
		pd3dDevice->SetRenderState(D3DRS_STENCILFUNC,           dwStencilFunc);
		pd3dDevice->SetRenderState(D3DRS_STENCILZFAIL,          dwStencilZFail);
		pd3dDevice->SetRenderState(D3DRS_STENCILFAIL,           dwStencilFail);
		pd3dDevice->SetRenderState(D3DRS_STENCILREF,            dwStencilRef);
		pd3dDevice->SetRenderState(D3DRS_STENCILMASK,           dwStencilMask);
		pd3dDevice->SetRenderState(D3DRS_STENCILWRITEMASK,      dwStencilWriteMask);
		pd3dDevice->SetRenderState(D3DRS_STENCILPASS,           dwStencilPass);
		pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,      dwAlphaBlendEnable);
		pd3dDevice->SetRenderState(D3DRS_SRCBLEND,              dwSrcBlend);
		pd3dDevice->SetRenderState(D3DRS_DESTBLEND,             dwDestBlend);
		pd3dDevice->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE,   dwTwoSidedStencilMode);
		pd3dDevice->SetRenderState(D3DRS_CCW_STENCILFUNC,       dwCCWStencilFunc);
		pd3dDevice->SetRenderState(D3DRS_CCW_STENCILZFAIL,      dwCCWStencilZFail);
		pd3dDevice->SetRenderState(D3DRS_CCW_STENCILFAIL,       dwCCWStencilFail);
		pd3dDevice->SetRenderState(D3DRS_CCW_STENCILPASS,       dwCCWStencilPass);
		pd3dDevice->SetRenderState(D3DRS_CULLMODE,              dwCullMode);
		return S_OK;
	}

	//
	//	Use stencil buffer as a mask. draw shadows to the scene
	//
	HRESULT DrawShadow(IDirect3DDevice9* pd3dDevice)
	{
		// backup..
		DWORD dwCullMode;
		pd3dDevice->GetRenderState(D3DRS_CULLMODE,              &dwCullMode);

		// Set renderstates (disable z-buffering, enable stencil, disable fog, and
		// turn on alphablending)
		pd3dDevice->SetRenderState( D3DRS_ZENABLE,          FALSE );
		pd3dDevice->SetRenderState( D3DRS_STENCILENABLE,    TRUE );
		pd3dDevice->SetRenderState( D3DRS_FOGENABLE,        FALSE );
		pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		pd3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
		pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE);

		pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
		pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
		pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
		pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
		pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
		pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );

		// Only write where stencil val >= 1 (count indicates # of shadows that
		// overlap that pixel)
		pd3dDevice->SetRenderState( D3DRS_STENCILREF,  0x1 );
		pd3dDevice->SetRenderState( D3DRS_STENCILFUNC, D3DCMP_LESSEQUAL );
		pd3dDevice->SetRenderState( D3DRS_STENCILPASS, D3DSTENCILOP_KEEP );
	
		// Draw a big, gray square
		pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW); // counter clock-wise render triangles
		pd3dDevice->SetFVF( SHADOWVERTEX::FVF );
		pd3dDevice->SetStreamSource( 0, g_pBigSquareVB, 0, sizeof(SHADOWVERTEX) );
		pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
	
		// Restore render states
		pd3dDevice->SetRenderState( D3DRS_ZENABLE,          TRUE );
		pd3dDevice->SetRenderState( D3DRS_STENCILENABLE,    FALSE );
		pd3dDevice->SetRenderState( D3DRS_FOGENABLE,        TRUE );
		pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
		pd3dDevice->SetRenderState( D3DRS_CULLMODE,         dwCullMode );
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
		v[0].color = 0x7f000000;
		v[1].color = 0x7f000000;
		v[2].color = 0x7f000000;
		v[3].color = 0x7f000000;
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