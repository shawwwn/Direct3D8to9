#pragma once

#include <vector>
#include <algorithm>    // std::find
#include "NormalException.h"

namespace NP { namespace EXCP {
	#define MAX_FAIL_COUNT 3
	#define MAX_FRAME_COUNT 6000

	extern std::vector<NormalException*> g_ExceptionList;
	extern std::vector<NormalData*> g_ExcludedList;

	bool isExcluded(NormalData* pWhichTextureItem);
	void RemoveExclude(NormalData* pWhichTextureItem);
	void AddExclude(NormalData* pWhichTextureItem);
	bool AddException(NormalData* pWhichTextureItem);
	bool CheckExceptionFrameCount(NormalException* pWhichException);
	inline void DeleteExceptionDeleteException(std::vector<NormalException*>::iterator &whichIterator);
	void CheckAll();
}}