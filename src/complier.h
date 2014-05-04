#pragma once

// Load d3d9.dll dynamically

#ifdef _DEBUG
#define D3D9_USE_DYNAMIC_LIBRARY
#define D3D_DEBUG_INFO
#endif