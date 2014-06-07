#include "SysUtils.h"
#include <fstream>
#include <stdio.h>
extern "C" {
#include "mphf/svHash.h"
}

namespace SV {
    const int SHW_X_INVERTED            = 1;        // 0x01
    const int SHW_Y_INVERTED            = 1 << 1;   // 0x02
    const int SHW_Z_INVERTED            = 1 << 2;   // 0x04
    const int SHW_USE_TRANSFORMATION    = 1 << 3;   // 0x08
    const int SHW_FLYING_UNIT           = 1 << 4;   // 0x10

	struct ShadowItem
	{
		ub4 m_Key;
		int m_ShadowParameter;
	};

	class ShadowTable
	{
	public:
		ShadowTable() {};
		~ShadowTable() {};
		int getShadowParam(DWORD numVertices, DWORD primCount);
	private:
		static const ShadowItem m_hashtable[SVHASHNKEYS];
	};
}