#pragma once


#ifdef _DEBUG
	// Load d3d9.dll dynamically
	#define D3D9_USE_DYNAMIC_LIBRARY
	// More detail on debug output
	#define D3D_DEBUG_INFO
	// SMAA load textures from memory instead of program resource
	#define SMAA_USE_DDS_PRECOMPUTED_TEXTURES
#endif

// SMAA load shaders/textures from local file system (this will disable SMAA_USE_DDS_PRECOMPUTED_TEXTURES)
//#define SMAA_ALLOW_LOCAL_FILES