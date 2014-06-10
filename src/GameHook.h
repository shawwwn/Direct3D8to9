#pragma once

#include "HookBase.h"
#include "SysUtils.h"
#include "EffectController.h"

namespace HOOK {
	enum RENDER_TYPE { D3D_MESH, D3D_PARTICLE };
	enum RENDER_STATE { STATE_NULL, STATE_UNIT_AND_EFFECT, STATE_PORTRAIT, STATE_MAYJOR_UI, STATE_MINOR_UI, STATE_MINI_MAP };
	#define RENDER_STATE_SEQUENCE				0x005FD84D
	#define RENDER_UNIT_AND_EFFECT_FUNC			0x00395900
	#define RENDER_UNKNOWN_1_FUNC				0x0033AE70
	#define RENDER_MAYJOR_UI_FUNC				0x0060C580
	#define RENDER_MINOR_UI_FUNC				0x0060EA80
	#define RENDER_MINI_MAP_FUNC				0x00347F40

	#define CALL_TO_RENDER_MESH					0x0050B9CB
	#define CALL_TO_RENDER_PARTICLE				0x0050B9E7

	#define RENDER_TARGET_SWITCH				0x00395696
	#define RENDER_TARGET_SWITCH_DEFAULT_CASE	0x00395899

	// Globals values
	extern volatile DWORD g_GameBase;
	extern volatile DWORD g_CurrentRenderTarget;
	extern volatile RENDER_TYPE g_CurrentRenderType;

	// Hooked functions' RVA
	extern DWORD address_render_state_sequence;
	extern DWORD address_render_target_switch;
	extern DWORD address_render_target_switch_default_case;
	extern DWORD address_render_mesh;
	extern DWORD address_render_mesh_real_func;
	extern DWORD address_render_particle;
	extern DWORD address_render_particle_real_func;

	// Deploy hooks to capture render call
	void deployHooks();
	RENDER_STATE getCurrentRenderState();
}