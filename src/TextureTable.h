#pragma once

#include <map>
#include <stdexcept>      // std::out_of_range
#include <d3d9.h>
#include <d3dx9.h>
namespace NP {
	#define DEFAULT_NORMAL_ALPHAREF 192
	#define DEFAULT_TRANSPLANT_ALPHAREF 4

	struct TextureKeys
	{
		public:
			TextureKeys(DWORD stride, DWORD numVertices, DWORD primCount);
			bool operator <(const TextureKeys &right) const;
			DWORD m_Stride;	// Stride
			DWORD m_NumVertices;	// NumVertices
			DWORD m_PrimCount;	// primCount
	};

	struct TextureItem
	{
		public:
			TextureItem();
			TextureItem(bool computed, IDirect3DTexture9* pBaseTexture, IDirect3DTexture9* pNormalTexture, 
						UINT width, UINT height, bool isMask, UINT normalAlphaRef, UINT transplantAlphaRef, bool isTransplantByDefault);
			bool TextureItem::operator ==(const TextureItem &right) const;
			// member variables
			IDirect3DTexture9* m_pBaseTexture;
			IDirect3DTexture9* m_pNormalTexture;
			bool m_Computed;
			UINT m_Width;
			UINT m_Height;
			bool m_IsMask;
			UINT m_TransplantAlphaRef;
			UINT m_NormalAlphaRef;
			bool m_IsTransplantByDefault;
	};

	class TextureTable
	{
		public:
			TextureTable();
			TextureItem& TextureTable::at(TextureKeys& keys);
			void addTexture(DWORD stride, DWORD numVertices, DWORD primCount, UINT width, UINT height,
				bool isMask, UINT normalAlphaRef, UINT transplantAlphaRef, bool isTransplantByDefault,
				IDirect3DTexture9* pBaseTexture, IDirect3DTexture9* pNormalTexture);
			void addTexture(TextureKeys &keys, TextureItem &item);
			void addTextureEntry(DWORD stride, DWORD numVertices, DWORD primCount, UINT width, UINT height,
				bool isMask, UINT normalAlphaRef, UINT transplantAlphaRef, bool isTransplantByDefault);
			void addTextureEntry(TextureKeys &keys, UINT width, UINT height,
				bool isMask, UINT normalAlphaRef, UINT transplantAlphaRef, bool isTransplantByDefault);
			void removeTexture(DWORD stride, DWORD numVertices, DWORD primCount);
			void removeTexture(TextureKeys &keys);
			IDirect3DTexture9* queryBaseTexture(DWORD stride, DWORD numVertices, DWORD primCount);
			IDirect3DTexture9* queryBaseTexture(TextureKeys &keys);
			IDirect3DTexture9* queryNormalTexture(DWORD stride, DWORD numVertices, DWORD primCount);
			IDirect3DTexture9* queryNormalTexture(TextureKeys &keys);
			void computeNormalTextures();
			void cleanup();
			// member variables
			std::map<TextureKeys, TextureItem> m_Table;
	};
}