#include "SysUtils.h"

//
// Functions
//
HMODULE GetCurrentModule()
{
#if _MSC_VER < 1300
	// earlier than .NET compiler (VC 6.0)
	// Here's a trick that will get you the handle of the module
	// you're running in without any a-priori knowledge:
	// http://www.dotnet247.com/247reference/msgs/13/65259.aspx
	MEMORY_BASIC_INFORMATION mbi;
	static int dummy;
	VirtualQuery( &dummy, &mbi, sizeof(mbi) );
	return reinterpret_cast<HMODULE>(mbi.AllocationBase);
#else
	// VC 7.0
	// from ATL 7.0 sources
	return reinterpret_cast<HMODULE>(&__ImageBase);
#endif
}

// Get Z/Y/X rotation angle
void GetRotation(D3DMATRIX* pMatrix, float& Yaw, float& Pitch, float& Roll)
{
	if (pMatrix->_11 == 1.0f)
	{
		Yaw = atan2f(pMatrix->_13, pMatrix->_34);
		Pitch = 0;
		Roll = 0;
	}
	else if (pMatrix->_11 == -1.0f)
	{
		Yaw = atan2f(pMatrix->_13, pMatrix->_34);
		Pitch = 0;
		Roll = 0;
	}
	else 
	{
		Yaw = atan2(-pMatrix->_31, pMatrix->_11);
		Pitch = atan2(-pMatrix->_32, pMatrix->_33);
		Roll = atan2(-pMatrix->_23, pMatrix->_22);
	}
}