#include "NormalTable.h"

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
	// struct NormalItem
	//
	NormalItem::NormalItem() {}
	NormalItem::NormalItem(bool computed, IDirect3DTexture9* pBaseTexture, IDirect3DTexture9* pNormalTexture, UINT width, UINT height, bool inverted, bool isMask, UINT normalAlphaRef, UINT transplantAlphaRef)
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
	bool NormalItem::operator ==(const NormalItem &right) const
	{
		return m_pBaseTexture == right.m_pBaseTexture;
	}

	//
	// class NormalTable
	//
	NormalTable::NormalTable()
	{
		InitNormalTable();
	}
	NormalItem& NormalTable::getData(DWORD stride, DWORD numVertices, DWORD primCount)
	{
		TextureKeys key(stride, numVertices, primCount);
		return m_Table.at(key);
	}
	void NormalTable::addTexture(DWORD stride, DWORD numVertices, DWORD primCount, UINT width, UINT height,
		bool inverted, bool isMask, UINT normalAlphaRef, UINT transplantAlphaRef,
		IDirect3DTexture9* pBaseTexture, IDirect3DTexture9* pNormalTexture)
	{
		TextureKeys keys(stride, numVertices, primCount);
		NormalItem item(false, pBaseTexture, pNormalTexture, width, height, inverted, isMask, normalAlphaRef, transplantAlphaRef);
		addTexture(keys, item);
	}
	void NormalTable::addTexture(TextureKeys &keys, NormalItem &item)
	{
		try
		{
			m_Table.at(keys);	// check if item exists
			return;				// exists
		}
		catch (const std::out_of_range)
		{
			m_Table.insert(std::pair<TextureKeys, NormalItem>(keys, item));	// not exists
		}
	
	}
	void NormalTable::addTextureEntry(DWORD stride, DWORD numVertices, DWORD primCount, UINT width, UINT height,
		bool inverted, bool isMask, UINT normalAlphaRef, UINT transplantAlphaRef)
	{
		TextureKeys keys(stride, numVertices, primCount);
		addTextureEntry(keys, width, height, inverted, isMask, normalAlphaRef, transplantAlphaRef);
	}
	void NormalTable::addTextureEntry(TextureKeys &keys, UINT width, UINT height,
		bool inverted, bool isMask, UINT normalAlphaRef, UINT transplantAlphaRef)
	{
		// TODO: Pass an constructed NormalItem and use addTexture instead
		try
		{
			m_Table.at(keys);	// check if item exists
			return;				// exists
		}
		catch (const std::out_of_range)
		{
			NormalItem item(false, NULL, NULL, width, height, inverted, isMask, normalAlphaRef, transplantAlphaRef);	// not exists
			m_Table.insert(std::pair<TextureKeys, NormalItem>(keys, item));
		}
	}
	void NormalTable::removeTexture(DWORD stride, DWORD numVertices, DWORD primCount)
	{
		TextureKeys keys(stride, numVertices, primCount);
		removeTexture(keys);
	}
	void NormalTable::removeTexture(TextureKeys &keys)
	{
		m_Table.erase(keys);
	}
	IDirect3DTexture9* NormalTable::queryBaseTexture(DWORD stride, DWORD numVertices, DWORD primCount)
	{
		TextureKeys keys(stride, numVertices, primCount);
		return queryBaseTexture(keys);
	}
	IDirect3DTexture9* NormalTable::queryBaseTexture(TextureKeys &keys)
	{
		return m_Table[keys].m_pBaseTexture;
	}
	IDirect3DTexture9* NormalTable::queryNormalTexture(DWORD stride, DWORD numVertices, DWORD primCount)
	{
		TextureKeys keys(stride, numVertices, primCount);
		return queryBaseTexture(keys);
	}
	IDirect3DTexture9* NormalTable::queryNormalTexture(TextureKeys &keys)
	{
		return m_Table[keys].m_pNormalTexture;
	}
	void NormalTable::computeNormalTextures()
	{
		// TODO: Loop through the map and compute all base textures into normal texture
	}
	void NormalTable::cleanup()
	{
		for (std::map<TextureKeys, NormalItem>::iterator it=m_Table.begin(); it!=m_Table.end(); ++it)
		{
			NormalItem &item = it->second;
			item.m_pBaseTexture = NULL;
			SAFE_RELEASE(item.m_pNormalTexture);
		}
		m_Table.clear();
	}
	void NormalTable::writeKeysToFile()
	{
		FILE* pKeyFile;
		FILE* pValueFile;
		fopen_s(&pKeyFile, "NormalMap_keys.txt", "w");
		fopen_s(&pValueFile, "NormalMap_vals.txt", "w");
		for(NormalMapTable::iterator it = m_Table.begin(); it != m_Table.end(); ++it)
		{
		  TextureKeys key = it->first;
		  NormalItem& item = it->second;
		  fprintf(pKeyFile, "%02d%04d%04d\n", key.m_Stride, key.m_NumVertices, key.m_PrimCount);
		  fprintf(pValueFile, "%3d %3d %1d %1d\n", item.m_Height, item.m_Width, item.m_Inverted, item.m_IsMask);
		}
		fclose(pKeyFile);
		fclose(pValueFile);
	}
}