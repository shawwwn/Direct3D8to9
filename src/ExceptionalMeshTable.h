#pragma once

#include <d3d9.h>
#include <d3dx9.h>

namespace NP {
	struct ExceptionalMeshKeys
	{
		DWORD m_NumVertices;
		DWORD m_PrimCount;
		DWORD m_SrcBlend;
		DWORD m_DestBlend;
		DWORD m_AlphaRef;
	};
	#define EMK_END() {0, 0, 0, 0, 0}

	// TODO: Implement actual table
}