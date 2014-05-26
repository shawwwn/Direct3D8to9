#include <map>
#include <stdexcept>		// std::out_of_range
#include "SysUtils.h"

namespace SV {
    const int SHW_X_INVERTED            = 1;        // 0x01
    const int SHW_Y_INVERTED            = 1 << 1;   // 0x02
    const int SHW_Z_INVERTED            = 1 << 2;   // 0x04
    const int SHW_USE_TRANSFORMATION    = 1 << 3;   // 0x08
    const int SHW_FLYING_UNIT           = 1 << 4;   // 0x10

	struct ShadowKeys
	{
		ShadowKeys(DWORD numVertices, DWORD primCount);
		bool operator <(const ShadowKeys &right) const;
		DWORD m_NumVertices;
		DWORD m_PrimCount;
	};

	class ShadowTable
	{
		public:
			ShadowTable();
			int getShadowParam(DWORD numVertices, DWORD primCount);
			void addShadow(DWORD numVertices, DWORD primCount, int inversion=0);

			// member variables
			std::map<ShadowKeys, int> m_Table;
	};
}