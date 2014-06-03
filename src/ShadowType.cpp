#include "ShadowType.h"
#include <stdio.h>


namespace SV {
	bool IsHeroShadow(IDirect3DDevice9* pd3dDevice, IDirect3DVertexBuffer9* pVertexBuffer, IDirect3DIndexBuffer9* pIndexBuffer, 
						DWORD startIndex, DWORD primCount, DWORD baseVertexIndex)
	{
		// Warcraft3 FVF
		struct SHADOWVERTEX { D3DXVECTOR3 p, n; D3DCOLOR cl; FLOAT tu, tv; };
		SHADOWVERTEX* pVerticesData;
		WORD*         pIndicesData;

		// Lock the geometry buffers
		pVertexBuffer->Lock(0, 0, (LPVOID*)&pVerticesData, D3DLOCK_DONOTWAIT | D3DLOCK_READONLY | D3DLOCK_NOOVERWRITE | D3DLOCK_NOSYSLOCK | D3DLOCK_NO_DIRTY_UPDATE);
		pIndexBuffer->Lock(0, 0, (LPVOID*)&pIndicesData, D3DLOCK_DONOTWAIT | D3DLOCK_READONLY | D3DLOCK_NOOVERWRITE | D3DLOCK_NOSYSLOCK | D3DLOCK_NO_DIRTY_UPDATE);
		
		WORD idx0 = pIndicesData[startIndex + 0];
		WORD idx2 = pIndicesData[startIndex + 2];
		WORD idx3 = pIndicesData[startIndex + 3];

		float tu0 = pVerticesData[baseVertexIndex + idx0].tu;
		float tu3 = pVerticesData[baseVertexIndex + idx3].tu;
		float tv0 = pVerticesData[baseVertexIndex + idx0].tv;
		float tv2 = pVerticesData[baseVertexIndex + idx2].tv;

		// Unlock the geometry buffers
		pVertexBuffer->Unlock();
		pIndexBuffer->Unlock();

		float scale_x = 100.00f * 1.28f / (tu3-tu0);
		float scale_y = 100.00f * 1.28f / (tv0-tv2);

		/*
		char buffer[64];
		memset(buffer, 0, 64);
		sprintf_s(buffer, 64, "x: %f - y: %f", scale_x, scale_y);
		MessageBox(NULL, buffer, buffer, MB_OK);
		*/

		float remainder_x = fmod(scale_x , 10.0f);
		float remainder_y = fmod(scale_y , 10.0f);
		if (abs(remainder_x-5.0f) < 2)	// threshold, in WC3 unit shadow scale format
		{
			return true;
		}
		return false;
	}
}