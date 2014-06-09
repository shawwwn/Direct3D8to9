#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#if !defined(_DEBUG) && !defined(NORMALD3D)
#include "GameHook.h"
#endif

BOOL WINAPI DllMain(HINSTANCE module_handle, DWORD reason_for_call, LPVOID reserved)
{
	if (reason_for_call == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(module_handle); // Disable DllMain calls for DLL_THREAD_*
#if !defined(_DEBUG) && !defined(NORMALD3D)
		HOOK::deployHooks();
#endif
	}
	return TRUE;
}