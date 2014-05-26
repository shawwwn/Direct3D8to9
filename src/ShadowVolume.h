#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#define LIGHT_RANGE 1000;

namespace SV {
	class ShadowVolume
	{
		D3DXVECTOR3 m_pVertices[320000]; // Vertex data for rendering shadow volume
		DWORD       m_dwNumVertices;

		public:
			void    Reset();
			HRESULT BuildFromStreamBuffer(IDirect3DVertexBuffer9* pVertexBuffer, IDirect3DIndexBuffer9* pIndexBuffer, DWORD startIndex, DWORD primCount, DWORD baseVertexIndex, D3DXVECTOR3 vLight);
			HRESULT Render(LPDIRECT3DDEVICE9 pd3dDevice);
	};

	struct SHADOWVERTEX
	{
		D3DXVECTOR4 p;
		D3DCOLOR    color;

		static const DWORD FVF;
	};
}