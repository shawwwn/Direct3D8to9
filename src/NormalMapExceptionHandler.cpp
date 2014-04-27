#include "NormalMapExceptionHandler.h"

namespace NP { namespace EXCP {
	std::vector<TextureException*> g_ExceptionList;
	std::vector<TextureItem*> g_ExcludedList;

	/**
	*	check the present of an Texture Item in the
	*	excluded list.
	*/
	bool isExcluded(TextureItem* pWhichTextureItem)
	{
		return (std::find(g_ExcludedList.begin(), g_ExcludedList.end(), pWhichTextureItem) != g_ExcludedList.end());
	}

	/**
	*	Remove an item from the excluded list
	*/
	void RemoveExclude(TextureItem* pWhichTextureItem)
	{
		std::vector<TextureItem*>::iterator it = std::find(g_ExcludedList.begin(), g_ExcludedList.end(), pWhichTextureItem);
		if (it != g_ExcludedList.end())
			g_ExcludedList.erase(it);
	}

	/**
	*	Add an Texture Item to the excluded list,
	*	but check its present first.
	*/
	void AddExclude(TextureItem* pWhichTextureItem)
	{
		if (!isExcluded(pWhichTextureItem))
			g_ExcludedList.push_back(pWhichTextureItem);
	}

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
				{
					AddExclude(pWhichTextureItem);
					return false;
				}
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
		if (pWhichException->m_pTextureItem->m_Computed || pWhichException->m_FrameCount >= MAX_FRAME_COUNT)
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
			{
				RemoveExclude(pException->m_pTextureItem);
				DeleteException(it);
			}
			else
				++it;
		}
	}
}}