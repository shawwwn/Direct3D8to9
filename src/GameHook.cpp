#include "GameHook.h"

namespace HOOK {
	static DWORD next_line;
	volatile DWORD g_GameBase;
	volatile DWORD g_CurrentRT;
	DWORD address_switchRT;
	DWORD address_switchRT_default_case;

	//
	// Records target value in switch-case statement
	//
	__declspec (naked) void switch_case()
	{
		// Save all registers
		__asm 
		{
			pushad;
			mov [g_CurrentRT], eax;
		}

		next_line = address_switchRT + 9; // 9 bytes after the original address
	
		// Restore the original code
		__asm
		{
			popad;
			cmp eax, 15
			ja default_case;
			jmp [next_line];
		default_case:
			jmp [address_switchRT_default_case];
		}
	}

	void deployHooks()
	{
		// Initialize offests
		g_GameBase = (DWORD)GetModuleHandle("Nirvana.dll");
		address_switchRT = g_GameBase + SWITCH_RENDER_TARGET;
		address_switchRT_default_case = g_GameBase + SWITCH_RENDER_TARGET_DEFAULT_CASE;

		// Hook
		JmpPatch(switch_case, (void*)address_switchRT, 4);
	}
}