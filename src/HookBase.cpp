#include "HookBase.h"

namespace HOOK {
	// Jmp to Dest function
	void JmpPatch(void* pDest, void* pSrc, int nNops)
	{
		DWORD OldProt;
		VirtualProtect(pSrc, 5 + nNops, PAGE_EXECUTE_READWRITE, &OldProt);
		*(BYTE*)pSrc = (BYTE)0xE9;
		*(DWORD*)((DWORD)pSrc + 1) = (DWORD)pDest - (DWORD)pSrc - 5;
		for (int i = 0; i < nNops; ++i)
			*(BYTE*)((DWORD)pSrc + 5 + i) = 0x90;
		VirtualProtect(pSrc, 5 + nNops, OldProt, &OldProt);
	}

	// Read the function pointer from a call or a jmp
	DWORD getFuncPtr(DWORD address)
	{
		return *(DWORD*)address + address + 4;
	}
}