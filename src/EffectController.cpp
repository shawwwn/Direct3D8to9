#include "EffectController.h"

namespace CTRL {
	bool g_EnableHDR = false;
	bool g_EnableNP  = false;
	bool g_EnablePP  = false;
	bool g_EnableSV  = false;
	bool g_DisableUnitShadow = false;

	// TODO: Retrive status from nirvana_ext.dll 
	void InitController()
	{
		g_EnableHDR = true;
		g_EnableNP = true;
		g_EnablePP = true;
		g_EnableSV = true;
		g_DisableUnitShadow = true;
	}
}