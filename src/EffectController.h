#pragma once

#ifndef NORMALD3D
#include "Nirvana_ext_export.h"
#pragma comment(lib, "../lib/Nirvana_ext.lib")
#endif

namespace CTRL {
	extern bool g_EnableEffect;
	extern bool g_EnableHDR;
	extern bool g_EnableNP;
	extern bool g_EnablePP;
	extern bool g_EnableSV;
	extern bool g_DisableUnitShadow;
#ifndef NORMALD3D
	void InitController();
#endif
}