#include "NormalTable.h"

namespace NP {
	//
	// struct NormalItem
	//
	bool NormalItem::operator ==(const NormalItem &right) const
	{
		return m_pBaseTexture == right.m_pBaseTexture;
	}

	//
	// class NormalTable
	//
	NormalTable::NormalTable()
	{
		// Make a copy from static data
		for (int i=0; i<NPHASHNKEYS; i++)
		{
			m_datas[i].m_Width = m_items[i].m_Width;
			m_datas[i].m_Height = m_items[i].m_Height;
			m_datas[i].m_Inverted = m_items[i].m_Inverted;
			m_datas[i].m_IsMask = m_items[i].m_IsMask;
		}
	};
	NormalItem& NormalTable::getData(DWORD stride, DWORD numVertices, DWORD primCount)
	{
		ub4 curKey = stride*100000000 + numVertices*10000 + primCount;
		ub4 index = npHash(curKey);
		if (index>=NPHASHNKEYS)
			throw std::out_of_range("Out Of Boundary");
		if(m_items[index].m_key==curKey)
			return m_datas[index];
		throw std::out_of_range("Key Didn't Match");
	}
	void NormalTable::cleanup()
	{
		for (int i=0; i<NPHASHNKEYS; i++)
		{
			if (m_datas[i].m_pNormalTexture!=nullptr)
				SAFE_RELEASE(m_datas[i].m_pNormalTexture);
		}
	}
}