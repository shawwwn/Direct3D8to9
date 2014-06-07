#include "TextureTable.h"

namespace NP {
	//
	// struct TextureKeys
	//
	TextureKeys::TextureKeys(DWORD stride, DWORD numVertices, DWORD primCount)
	{
		m_Stride = stride;
		m_NumVertices = numVertices;
		m_PrimCount = primCount;
	}
	bool TextureKeys::operator <(const TextureKeys &right) const
	{
		if ( m_Stride == right.m_Stride )
		{
			if ( m_NumVertices == right.m_NumVertices ) 
			{
				return m_PrimCount < right.m_PrimCount;
			}
			else
			{
				return m_NumVertices < right.m_NumVertices;
			}
		}
		else
		{
			return m_Stride < right.m_Stride;
		}
	}

	//
	// struct TextureItem
	//
	TextureItem::TextureItem() {}
	TextureItem::TextureItem(bool computed, IDirect3DTexture9* pBaseTexture, IDirect3DTexture9* pNormalTexture, UINT width, UINT height, bool inverted, bool isMask, UINT normalAlphaRef, UINT transplantAlphaRef)
	{
		m_Computed = computed;
		m_pBaseTexture = pBaseTexture;
		m_pNormalTexture = pNormalTexture;
		m_Width = width;
		m_Height = height;
		m_Inverted = inverted;
		m_IsMask = isMask;
		m_NormalAlphaRef = normalAlphaRef;
		m_TransplantAlphaRef = transplantAlphaRef;
	}
	bool TextureItem::operator ==(const TextureItem &right) const
	{
		return m_pBaseTexture == right.m_pBaseTexture;
	}

	//
	// class TextureTable
	//
	TextureTable::TextureTable() {}
	TextureItem& TextureTable::at(TextureKeys& keys)
	{
		return m_Table.at(keys);
	}
	void TextureTable::addTexture(DWORD stride, DWORD numVertices, DWORD primCount, UINT width, UINT height,
		bool inverted, bool isMask, UINT normalAlphaRef, UINT transplantAlphaRef,
		IDirect3DTexture9* pBaseTexture, IDirect3DTexture9* pNormalTexture)
	{
		TextureKeys keys(stride, numVertices, primCount);
		TextureItem item(false, pBaseTexture, pNormalTexture, width, height, inverted, isMask, normalAlphaRef, transplantAlphaRef);
		addTexture(keys, item);
	}
	void TextureTable::addTexture(TextureKeys &keys, TextureItem &item)
	{
		try
		{
			m_Table.at(keys);	// check if item exists
			return;				// exists
		}
		catch (const std::out_of_range)
		{
			m_Table.insert(std::pair<TextureKeys, TextureItem>(keys, item));	// not exists
		}
	
	}
	void TextureTable::addTextureEntry(DWORD stride, DWORD numVertices, DWORD primCount, UINT width, UINT height,
		bool inverted, bool isMask, UINT normalAlphaRef, UINT transplantAlphaRef)
	{
		TextureKeys keys(stride, numVertices, primCount);
		addTextureEntry(keys, width, height, inverted, isMask, normalAlphaRef, transplantAlphaRef);
	}
	void TextureTable::addTextureEntry(TextureKeys &keys, UINT width, UINT height,
		bool inverted, bool isMask, UINT normalAlphaRef, UINT transplantAlphaRef)
	{
		// TODO: Pass an constructed TextureItem and use addTexture instead
		try
		{
			m_Table.at(keys);	// check if item exists
			return;				// exists
		}
		catch (const std::out_of_range)
		{
			TextureItem item(false, NULL, NULL, width, height, inverted, isMask, normalAlphaRef, transplantAlphaRef);	// not exists
			m_Table.insert(std::pair<TextureKeys, TextureItem>(keys, item));
		}
	}
	void TextureTable::removeTexture(DWORD stride, DWORD numVertices, DWORD primCount)
	{
		TextureKeys keys(stride, numVertices, primCount);
		removeTexture(keys);
	}
	void TextureTable::removeTexture(TextureKeys &keys)
	{
		m_Table.erase(keys);
	}
	IDirect3DTexture9* TextureTable::queryBaseTexture(DWORD stride, DWORD numVertices, DWORD primCount)
	{
		TextureKeys keys(stride, numVertices, primCount);
		return queryBaseTexture(keys);
	}
	IDirect3DTexture9* TextureTable::queryBaseTexture(TextureKeys &keys)
	{
		return m_Table[keys].m_pBaseTexture;
	}
	IDirect3DTexture9* TextureTable::queryNormalTexture(DWORD stride, DWORD numVertices, DWORD primCount)
	{
		TextureKeys keys(stride, numVertices, primCount);
		return queryBaseTexture(keys);
	}
	IDirect3DTexture9* TextureTable::queryNormalTexture(TextureKeys &keys)
	{
		return m_Table[keys].m_pNormalTexture;
	}
	void TextureTable::computeNormalTextures()
	{
		// TODO: Loop through the map and compute all base textures into normal texture
	}
	void TextureTable::cleanup()
	{
		for (std::map<TextureKeys, TextureItem>::iterator it=m_Table.begin(); it!=m_Table.end(); ++it)
		{
			TextureItem &item = it->second;
			item.m_pBaseTexture = NULL;
			SAFE_RELEASE(item.m_pNormalTexture);
		}
		m_Table.clear();
	}
	void TextureTable::writeKeysToFile()
	{
		FILE* pKeyFile;
		FILE* pValueFile;
		fopen_s(&pKeyFile, "NormalMap_keys.txt", "w");
		fopen_s(&pValueFile, "NormalMap_vals.txt", "w");
		for(NormalMapTable::iterator it = m_Table.begin(); it != m_Table.end(); ++it)
		{
		  TextureKeys key = it->first;
		  TextureItem& item = it->second;
		  fprintf(pKeyFile, "%04d%04d\n", key.m_NumVertices, key.m_PrimCount);
		  fprintf(pValueFile, "%3d, %3d - %d, %d\n", item.m_Height, item.m_Width, item.m_Inverted, item.m_IsMask);
		}
		fclose(pKeyFile);
		fclose(pValueFile);
	}
}