#pragma once

#include "Nirvana_ext_export.h"
#pragma comment(lib, "../lib/Nirvana_ext.lib")


namespace CTRL {
	extern bool g_EnableEffect;
	extern bool g_EnableHDR;
	extern bool g_EnableNP;
	extern bool g_EnablePP;
	extern bool g_EnableSV;
	extern bool g_DisableUnitShadow;

	void InitController();
}