#pragma once

#include <map>
#include <stdexcept>		// std::out_of_range
#include <d3d9.h>
#include <d3dx9.h>
#include "SysUtils.h"		// SAFE_RELEASE
extern "C" {
#include "mphf/npHash.h"
}

namespace NP {
	// Static pre-defined data
	struct NormalKeyedItem
	{
		// TODO: use key
		ub4 m_key;
		UINT m_Width;
		UINT m_Height;
		bool m_Inverted;
		bool m_IsMask;
	};

	// Dynamic data for storage
	struct NormalItem
	{
		NormalItem() : m_Computed(false), m_pBaseTexture(nullptr), m_pNormalTexture(nullptr) {};
		bool NormalItem::operator ==(const NormalItem &right) const;

		bool m_Computed;
		IDirect3DTexture9* m_pBaseTexture;
		IDirect3DTexture9* m_pNormalTexture;

		UINT m_Width;
		UINT m_Height;
		bool m_Inverted;
		bool m_IsMask;
	};

	class NormalTable
	{
		private:
			const static NormalKeyedItem m_items[NPHASHNKEYS];
			NormalItem m_datas[NPHASHNKEYS];	// parallel to m_keys
		public:
			NormalTable();
			NormalItem& NormalTable::getData(DWORD stride, DWORD numVertices, DWORD primCount);
			void cleanup();
	};
}