#include "TextureException.h"

namespace NP {

	TextureException::TextureException(TextureItem* pWhichItem);
	{
		m_pWhichItem = pWhichItem;
		m_FrameCount = 0;
		m_FailCount = 0;
	}

	TextureException::~TextureException() {};
}