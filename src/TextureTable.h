#pragma once

#include <map>
#include <stdexcept>      // std::out_of_range
#include <d3d9.h>
#include <d3dx9.h>
namespace NP {
	struct TextureKeys
	{
		public:
			TextureKeys(DWORD k1, DWORD k2, DWORD k3, DWORD k4);
			bool operator <(const TextureKeys &right) const;
			DWORD dwKey1;	// Stride
			DWORD dwKey2;	// NumVertices
			DWORD dwKey3;	// primCount
			DWORD dwKey4;	// AlphaRef
	};

	struct TextureItem
	{
		public:
			TextureItem();
			TextureItem(IDirect3DTexture9* pTexture, bool Computed);
			bool TextureItem::operator ==(const TextureItem &right) const;
			// member variables
			IDirect3DTexture9* m_pTexture;
			bool m_Computed;
	};

	class TextureTable
	{
		public:
			TextureTable();
			TextureItem& TextureTable::at(TextureKeys& keys);
			void addTexture(DWORD dwKey1, DWORD dwKey2, DWORD dwKey3, DWORD dwKey4, IDirect3DTexture9* pTexture);
			void addTexture(TextureKeys &keys, TextureItem &item);
			void addTextureEntry(DWORD dwKey1, DWORD dwKey2, DWORD dwKey3, DWORD dwKey4, UINT width, UINT height);
			void addTextureEntry(TextureKeys &keys, UINT width, UINT height);
			void removeTexture(DWORD dwKey1, DWORD dwKey2, DWORD dwKey3, DWORD dwKey4);
			void removeTexture(TextureKeys &keys);
			IDirect3DTexture9* queryTexture(DWORD dwKey1, DWORD dwKey2, DWORD dwKey3, DWORD dwKey4);
			IDirect3DTexture9* queryTexture(TextureKeys &keys);
			void cleanup();
			// member variables
			std::map<TextureKeys, TextureItem> m_Table;
	};
}