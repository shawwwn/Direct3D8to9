#ifndef H_NIR_EXT_EXP
#define H_NIR_EXT_EXP

#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>

#ifdef BUILDING_NIR_EXT
#	define DECLSPECIFIER __declspec(dllexport)
#else
#	define DECLSPECIFIER __declspec(dllimport)
#endif

/* exports */
struct DECLSPECIFIER PluginParameter {
	public:
		PluginParameter(char* name, char* value, bool allocNew);
		char* paramName;
		char* paramValue;
};

struct DECLSPECIFIER Plugin {
	public:
		Plugin(char* name);
		char* pluginName;
		int parameterSize;
		PluginParameter* pParameterList[10];		// an array of pointers of PluginParameter
};

DECLSPECIFIER Plugin* getPluginInfo(const char* pluginName);

#endif // H_NIR_EXT_EXP