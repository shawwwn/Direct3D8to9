#include "ShadowTable.h"

namespace SV {
	//
	// struct ShadowKeys
	//
	ShadowKeys::ShadowKeys(DWORD numVertices, DWORD primCount)
	{
		m_NumVertices = numVertices;
		m_PrimCount = primCount;
	}
	bool ShadowKeys::operator <(const ShadowKeys &right) const
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

	//
	// class ShadowTable
	//
	ShadowTable::ShadowTable() {}

	// Return -1 if entry not found
	int ShadowTable::getShadowParam(DWORD numVertices, DWORD primCount)
	{
		ShadowKeys keys(numVertices, primCount);
		try
		{
			return m_Table.at(keys);
		}
		catch (const std::out_of_range)
		{
			return -1;
		}
		return -1;
	}
	void ShadowTable::addShadow(DWORD numVertices, DWORD primCount, int inversion)
	{
		ShadowKeys keys(numVertices, primCount);
		m_Table.insert(std::pair<ShadowKeys, int>(keys, inversion));
	}
}