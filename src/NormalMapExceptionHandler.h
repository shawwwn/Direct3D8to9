#pragma once

#include <vector>
#include <algorithm>    // std::find
#include "TextureException.h"

namespace NP { namespace EXCP {
	#define MAX_FAIL_COUNT 3
	#define MAX_FRAME_COUNT 6000

	extern std::vector<TextureException*> g_ExceptionList;
	extern std::vector<TextureItem*> g_ExcludedList;

	bool isExcluded(TextureItem* pWhichTextureItem);
	void RemoveExclude(TextureItem* pWhichTextureItem);
	void AddExclude(TextureItem* pWhichTextureItem);
	bool AddException(TextureItem* pWhichTextureItem);
	bool CheckExceptionFrameCount(TextureException* pWhichException);
	inline void DeleteExceptionDeleteException(std::vector<TextureException*>::iterator &whichIterator);
	void CheckAll();
}}