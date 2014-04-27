#pragma once

#include <vector>
#include "TextureException.h"

namespace NP {
	#define MAX_FAIL_COUNT 5
	#define MAX_FRAME_COUNT 1000

	extern std::vector<TextureException*> g_ExceptionList;

	bool AddException(TextureItem* pWhichTextureItem);
	bool CheckExceptionFrameCount(TextureException* pWhichException);
	inline void DeleteExceptionDeleteException(std::vector<TextureException*>::iterator &whichIterator);
	void CheckAll();
}