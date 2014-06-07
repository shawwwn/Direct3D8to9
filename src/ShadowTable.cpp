#include "ShadowTable.h"

namespace SV {
	// Return -1 if entry not found
	int ShadowTable::getShadowParam(DWORD numVertices, DWORD primCount)
	{
		ub4 curKey = numVertices*10000 + primCount;
		ub4 index = svHash(curKey);
		ShadowItem item = m_hashtable[index];
		if (curKey!=item.m_Key)
			return -1;
		return item.m_ShadowParameter;
	}

}