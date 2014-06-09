#pragma once

#include "HookBase.h"
#include "SysUtils.h"

namespace HOOK {
	#define RENDER_UNIT_AND_EFFECT_FUNC			0x00395900
	#define RENDER_UNKNOWN_FUNC					0x0033AE70
	#define RENDER_MAIN_UI_FUNC					0x0060C580
	#define RENDER_CLOCK_UI_FUNC				0x0060EA80
	#define RENDER_MINI_MAP_FUNC				0x00347F40
	#define RENDER_CURSOR_FUNC					0x0060EA80

	#define CALL_TO_RENDER_UNIT					0x0050B9CB
	#define CALL_TO_RENDER_PARTICLE				0x0050B9E7

	#define SWITCH_RENDER_TARGET				0x00395696
	#define SWITCH_RENDER_TARGET_DEFAULT_CASE	0x00395899

	// Globals values
	extern volatile DWORD g_GameBase;
	extern volatile DWORD g_CurrentRT;

	// Hooked functions' RVA
	extern DWORD address_switchRT;
	extern DWORD address_switchRT_default_case;
	
	// Deploy hooks to capture render call
	void deployHooks();
}