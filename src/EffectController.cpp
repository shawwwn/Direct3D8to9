#include "EffectController.h"
#include "Windows.h"
#include <stdlib.h>     // atoi

namespace CTRL {
	bool g_EnableEffect = false;
	bool g_EnableHDR = false;
	bool g_EnableNP  = false;
	bool g_EnablePP  = false;
	bool g_EnableSV  = false;
	bool g_DisableUnitShadow = false;

	void InitController()
	{
		Plugin* plg=getPluginInfo("Nir_Plugin_RenderCraft.dll");
		if (plg==NULL)
			return;
		if (plg->parameterSize==0)
			return;

		for (int i=0; i < plg->parameterSize; i++)
		{
			PluginParameter* pParam=plg->pParameterList[i];
			char* parameterName=pParam->paramName;
			if (strcmp(parameterName, "EffectEnable")==0)
				g_EnableEffect=atoi(pParam->paramValue)==0 ? false : true;
			else if (strcmp(parameterName, "HDR")==0)
				g_EnableHDR=atoi(pParam->paramValue)==0 ? false : true;
			else if (strcmp(parameterName, "NormalMap")==0)
				g_EnableNP=atoi(pParam->paramValue)==0 ? false : true;
			else if (strcmp(parameterName, "PostProcess")==0)
				g_EnablePP=atoi(pParam->paramValue)==0 ? false : true;
			else if (strcmp(parameterName, "RealTimeShadows")==0)
				g_EnableSV=atoi(pParam->paramValue)==0 ? false : true;
			else if (strcmp(parameterName, "DisableUnitShadow")==0)
				g_DisableUnitShadow=atoi(pParam->paramValue)==0 ? false : true;
			pParam = NULL;
		}
	}
}