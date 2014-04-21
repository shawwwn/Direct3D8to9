#include "TextureTable.h"

namespace NP {
	//
	// struct TextureKeys
	//
	TextureKeys::TextureKeys(DWORD k1, DWORD k2, DWORD k3, DWORD k4) : dwKey1(k1), dwKey2(k2), dwKey3(k3), dwKey4(k4) {}
	bool TextureKeys::operator <(const TextureKeys &right) const
	{
		if ( dwKey1 == right.dwKey1 )
		{
			if ( dwKey2 == right.dwKey2 ) 
			{
				if ( dwKey3 == right.dwKey3 )
				{
					return dwKey4 < right.dwKey4;
				}
				else
				{
					return dwKey3 < right.dwKey3;
				}
			}
			else
			{
				return dwKey2 < right.dwKey2;
			}
		}
		else
		{
			return dwKey1 < right.dwKey1;
		}
	}

	//
	// struct TextureItem
	//
	TextureItem::TextureItem() {}
	TextureItem::TextureItem(IDirect3DTexture9* pTexture, bool Computed) : m_pTexture(pTexture), m_Computed(Computed) {}
	bool TextureItem::operator ==(const TextureItem &right) const
	{
		return m_pTexture == right.m_pTexture;
	}

	//
	// class TextureTable
	//
	TextureTable::TextureTable() {}
	TextureItem& TextureTable::at(TextureKeys& keys)
	{
		return m_Table.at(keys);
	}
	void TextureTable::addTexture(DWORD dwKey1, DWORD dwKey2, DWORD dwKey3, DWORD dwKey4, IDirect3DTexture9* pTexture)
	{
		TextureKeys keys(dwKey1, dwKey2, dwKey3, dwKey4);
		TextureItem item(pTexture, false);
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
	void TextureTable::addTextureEntry(DWORD dwKey1, DWORD dwKey2, DWORD dwKey3, DWORD dwKey4, UINT width, UINT height)
	{
		TextureKeys keys(dwKey1, dwKey2, dwKey3, dwKey4);
		addTextureEntry(keys, width, height);
	}
	void TextureTable::addTextureEntry(TextureKeys &keys, UINT width, UINT height)
	{
		try
		{
			m_Table.at(keys);	// check if item exists
			return;				// exists
		}
		catch (const std::out_of_range)
		{
			IDirect3DTexture9* pTexture = NULL;
			TextureItem item(pTexture, false);	// not exists
			m_Table.insert(std::pair<TextureKeys, TextureItem>(keys, item));
		}
	}
	void TextureTable::removeTexture(DWORD dwKey1, DWORD dwKey2, DWORD dwKey3, DWORD dwKey4)
	{
		TextureKeys keys(dwKey1, dwKey2, dwKey3, dwKey4);
		removeTexture(keys);
	}
	void TextureTable::removeTexture(TextureKeys &keys)
	{
		m_Table.erase(keys);
	}
	IDirect3DTexture9* TextureTable::queryTexture(DWORD dwKey1, DWORD dwKey2, DWORD dwKey3, DWORD dwKey4)
	{
		TextureKeys keys(dwKey1, dwKey2, dwKey3, dwKey4);
		return queryTexture(keys);
	}
	IDirect3DTexture9* TextureTable::queryTexture(TextureKeys &keys)
	{
		return m_Table[keys].m_pTexture;
	}
	void TextureTable::cleanup()
	{
		// TODO: Iterate through the map and release all textures
		m_Table.clear();
	}
}