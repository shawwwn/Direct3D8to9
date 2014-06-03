#include "ShadowVolume.h"

namespace SV {
	const DWORD SHADOWVERTEX::FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;

	void AddEdge( WORD* pEdges, DWORD& dwNumEdges, WORD v0, WORD v1 )
	{
		// Remove interior edges (which appear in the list twice)
		for( DWORD i=0; i < dwNumEdges; i++ )
		{
			if( ( pEdges[2*i+0] == v0 && pEdges[2*i+1] == v1 ) ||
				( pEdges[2*i+0] == v1 && pEdges[2*i+1] == v0 ) )
			{
				if( dwNumEdges > 1 )
				{
					pEdges[2*i+0] = pEdges[2*(dwNumEdges-1)+0];
					pEdges[2*i+1] = pEdges[2*(dwNumEdges-1)+1];
				}
				dwNumEdges--;
				return;
			}
		}

		pEdges[2*dwNumEdges+0] = v0;
		pEdges[2*dwNumEdges+1] = v1;
		dwNumEdges++;
	}

	void ShadowVolume::Reset()
	{
		m_dwNumVertices = 0;
	}

	HRESULT ShadowVolume::BuildFromStreamBuffer(IDirect3DVertexBuffer9* pVertexBuffer, IDirect3DIndexBuffer9* pIndexBuffer,
												DWORD baseVertexIndex, DWORD startIndex,
												DWORD numVertices, DWORD primCount,
												D3DXVECTOR3 vLight)
	{
		// Warcraft3 FVF
		struct MESHVERTEX { D3DXVECTOR3 p, n; FLOAT tu, tv; };

		MESHVERTEX* pVerticesData;
		WORD*       pIndicesData;

		// Lock the geometry buffers
		pVertexBuffer->Lock(baseVertexIndex * sizeof(MESHVERTEX),
							numVertices * sizeof(MESHVERTEX),
							(LPVOID*)&pVerticesData,
							D3DLOCK_DONOTWAIT | D3DLOCK_READONLY | D3DLOCK_NOOVERWRITE | D3DLOCK_NOSYSLOCK | D3DLOCK_NO_DIRTY_UPDATE);
		pIndexBuffer->Lock(startIndex * sizeof(WORD),
							primCount * 3,			// for triangle list
							(LPVOID*)&pIndicesData,
							D3DLOCK_DONOTWAIT | D3DLOCK_READONLY | D3DLOCK_NOOVERWRITE | D3DLOCK_NOSYSLOCK | D3DLOCK_NO_DIRTY_UPDATE );
		DWORD dwNumFaces    = primCount;

		// Allocate a temporary edge list
		WORD* pEdges = new WORD[dwNumFaces*6];
		if( pEdges == NULL )
		{
			pVertexBuffer->Unlock();
			pIndexBuffer->Unlock();
			return E_OUTOFMEMORY;
		}
		DWORD dwNumEdges = 0;

		// For each face
		for( DWORD i=0; i<dwNumFaces; i++ )
		{
			WORD wFace0 = pIndicesData[3*i+0];
			WORD wFace1 = pIndicesData[3*i+1];
			WORD wFace2 = pIndicesData[3*i+2];

			D3DXVECTOR3 v0 = pVerticesData[wFace0].p;
			D3DXVECTOR3 v1 = pVerticesData[wFace1].p;
			D3DXVECTOR3 v2 = pVerticesData[wFace2].p;

			// Transform vertices or transform light?
			D3DXVECTOR3 vCross1(v2-v1);
			D3DXVECTOR3 vCross2(v1-v0);
			D3DXVECTOR3 vNormal;
			D3DXVec3Cross( &vNormal, &vCross1, &vCross2 );

			if( D3DXVec3Dot( &vNormal, &vLight ) >= 0.0f )
			{
				AddEdge( pEdges, dwNumEdges, wFace0, wFace1 );
				AddEdge( pEdges, dwNumEdges, wFace1, wFace2 );
				AddEdge( pEdges, dwNumEdges, wFace2, wFace0 );

				m_pVertices[m_dwNumVertices++] = v2;
				m_pVertices[m_dwNumVertices++] = v1;
				m_pVertices[m_dwNumVertices++] = v0;
			}
			else
			{
				D3DXVECTOR3 v3 = v0 - vLight*LIGHT_RANGE;
				D3DXVECTOR3 v4 = v1 - vLight*LIGHT_RANGE;
				D3DXVECTOR3 v5 = v2 - vLight*LIGHT_RANGE;

				m_pVertices[m_dwNumVertices++] = v5;
				m_pVertices[m_dwNumVertices++] = v4;
				m_pVertices[m_dwNumVertices++] = v3;
			}
		}

		for( DWORD i=0; i<dwNumEdges; i++ )
		{
			D3DXVECTOR3 v1 = pVerticesData[pEdges[2*i+0]].p;
			D3DXVECTOR3 v2 = pVerticesData[pEdges[2*i+1]].p;
			D3DXVECTOR3 v3 = v1 - vLight*LIGHT_RANGE;
			D3DXVECTOR3 v4 = v2 - vLight*LIGHT_RANGE;

			// Add a quad (two triangles) to the vertex list
			m_pVertices[m_dwNumVertices++] = v1;
			m_pVertices[m_dwNumVertices++] = v2;
			m_pVertices[m_dwNumVertices++] = v3;

			m_pVertices[m_dwNumVertices++] = v2;
			m_pVertices[m_dwNumVertices++] = v4;
			m_pVertices[m_dwNumVertices++] = v3;
		}
		// Delete the temporary edge list
		delete[] pEdges;

		// Unlock the geometry buffers
		pVertexBuffer->Unlock();
		pIndexBuffer->Unlock();
		return S_OK;
	}

	HRESULT ShadowVolume::Render( LPDIRECT3DDEVICE9 pd3dDevice )
	{
		pd3dDevice->SetFVF(D3DFVF_XYZ);
		return pd3dDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_dwNumVertices/3, m_pVertices, sizeof(D3DXVECTOR3));
	}
}