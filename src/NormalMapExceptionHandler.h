#pragma once

#include <vector>
#include <algorithm>    // std::find
#include "NormalException.h"

namespace NP { namespace EXCP {
	#define MAX_FAIL_COUNT 3
	#define MAX_FRAME_COUNT 6000

	extern std::vector<NormalException*> g_ExceptionList;
	extern std::vector<NormalItem*> g_ExcludedList;

	bool isExcluded(NormalItem* pWhichTextureItem);
	void RemoveExclude(NormalItem* pWhichTextureItem);
	void AddExclude(NormalItem* pWhichTextureItem);
	bool AddException(NormalItem* pWhichTextureItem);
	bool CheckExceptionFrameCount(NormalException* pWhichException);
	inline void DeleteExceptionDeleteException(std::vector<NormalException*>::iterator &whichIterator);
	void CheckAll();
}}