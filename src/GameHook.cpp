#include "GameHook.h"

namespace HOOK {
	static DWORD next_line;
	volatile DWORD g_GameBase;
	volatile DWORD g_CurrentRenderTarget;
	volatile RENDER_TYPE g_CurrentRenderType;
	volatile DWORD currentRenderCall;
	DWORD address_render_state_sequence;
	DWORD address_render_target_switch;
	DWORD address_render_target_switch_default_case;
	DWORD address_render_mesh;
	DWORD address_render_mesh_real_func;
	DWORD address_render_particle;
	DWORD address_render_particle_real_func;

	//
	// Trampoline functions
	//
	#pragma warning(push)
	#pragma warning(disable : 4740)
	__declspec (naked) void render_state_sequence()
	{
		__asm
		{
			mov edx, [eax+0x30];
			mov ecx, edi;
			pushad;
			mov [currentRenderCall], edx;
		}

		next_line = address_render_state_sequence + 5;

		__asm
		{
			popad;
			jmp [next_line];
		}
	}
	__declspec (naked) void render_target_switch()
	{
		// Save all registers
		__asm 
		{
			pushad;
			mov [g_CurrentRenderTarget], eax;
		}

		next_line = address_render_target_switch + 9; // 9 bytes after the original address

		// Restore the original code
		__asm
		{
			popad;
			cmp eax, 0x15
			ja default_case;
			jmp [next_line];
		default_case:
			jmp [address_render_target_switch_default_case];
		}
	}
	__declspec (naked) void render_mesh()
	{
		__asm pushad;

		g_CurrentRenderType = D3D_MESH;
		next_line = address_render_mesh + 5;

		__asm
		{
			popad;
			call address_render_mesh_real_func;
			jmp next_line;
		}
	}
	__declspec (naked) void render_particle()
	{
		__asm pushad;

		g_CurrentRenderType = D3D_PARTICLE;
		next_line = address_render_particle + 5;

		__asm
		{
			popad;
			call [address_render_particle_real_func];
			jmp next_line;
		}
	}
	#pragma warning(pop)

	void deployHooks()
	{
		// Initialize offests
		g_GameBase = (DWORD)GetModuleHandle("Nirvana.dll");
		address_render_state_sequence = g_GameBase + RENDER_STATE_SEQUENCE;
		address_render_target_switch = g_GameBase + RENDER_TARGET_SWITCH;
		address_render_target_switch_default_case = g_GameBase + RENDER_TARGET_SWITCH_DEFAULT_CASE;
		address_render_mesh = g_GameBase + CALL_TO_RENDER_MESH;
		address_render_particle = g_GameBase + CALL_TO_RENDER_PARTICLE;

		// Hook
		address_render_mesh_real_func = getFuncPtr(address_render_mesh+1);
		address_render_particle_real_func = getFuncPtr(address_render_particle+1);

		JmpPatch(render_state_sequence, (void*)address_render_state_sequence);
		JmpPatch(render_target_switch, (void*)address_render_target_switch, 4);
		JmpPatch(render_mesh, (void*)address_render_mesh);
		JmpPatch(render_particle, (void*)address_render_particle);
	}

	RENDER_STATE getCurrentRenderState()
	{
		int offest = currentRenderCall - g_GameBase;
		switch (offest)
		{
		case RENDER_UNIT_AND_EFFECT_FUNC:
			return STATE_UNIT_AND_EFFECT;
			break;
		case RENDER_UNKNOWN_1_FUNC:
			return STATE_PORTRAIT;
			break;
		case RENDER_MAYJOR_UI_FUNC:
			return STATE_MAYJOR_UI;
			break;
		case RENDER_MINOR_UI_FUNC:
			return STATE_MINOR_UI;
			break;
		case RENDER_MINI_MAP_FUNC:
			return STATE_MINI_MAP;
			break;
		default:
			break;
		}
		return STATE_NULL;
	}
}