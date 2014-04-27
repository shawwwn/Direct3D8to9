#include "NormalMapExceptionHandler.h"

namespace NP {
	std::vector<TextureException*> g_ExceptionList;

	/**
	*	Construct and add an new exception to the exception list
	*	if item not exist, otherwise, increase exception count
	*	on the existing item.
	*/
	bool AddException(TextureItem* pWhichTextureItem)
	{
		// Search for existing exception 
		int index = 0;
		for (std::vector<TextureException*>::iterator it=g_ExceptionList.begin(); it!=g_ExceptionList.end(); ++it, ++index)
		{
			TextureException*& pException = *it;
			if (pException->m_pTextureItem == pWhichTextureItem)
			{
				pException->m_FailCount++;
				if (pException->m_FailCount >= MAX_FAIL_COUNT)
					return false;
				pException->m_FrameCount = 0;	// reset frame count
				return true;
			}
		}

		// Construct an new exception
		g_ExceptionList.push_back(new TextureException(pWhichTextureItem));
		return true;
	}

	/**
	*	Increase the frame count on the exception item.
	*	Returns true if the frame count reaches maximum, 
	*	otherwise, returns false.
	*/
	bool CheckExceptionFrameCount(TextureException* pWhichException)
	{
		pWhichException->m_FrameCount++;
		if (pWhichException->m_FrameCount >= MAX_FRAME_COUNT)
			return true;
		return false;
	}

	/**
	*	Delete an exception and free its memory from the global
	*	exception list.
	*/
	inline void DeleteException(std::vector<TextureException*>::iterator &whichIterator)
	{
		TextureException* pException = *whichIterator;
		g_ExceptionList.erase(whichIterator);
		delete pException;
	}

	/**
	*	Loop thorugh the exception list and check each exception's
	*	frame count. Remove the exception that its frame count is
	*	bigger than the maximum frame count.
	*/
	void CheckAll()
	{
		if (g_ExceptionList.empty())
			return;

		for (std::vector<TextureException*>::iterator it=g_ExceptionList.begin(); it!=g_ExceptionList.end(); )
		{
			TextureException* pException = *it;
			if (CheckExceptionFrameCount(pException))
				DeleteException(it);
			else
				++it;
		}
	}
}