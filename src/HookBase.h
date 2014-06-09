#pragma once

#define WIN32_LEAN_AND_MEAN
#include "Windows.h"

namespace HOOK {
	void JmpPatch(void* pDest, void* pSrc, int nNops = 0);
	void* getFuncPtr(DWORD address);
}