#include "TextureException.h"

namespace NP { namespace EXCP {

	TextureException::TextureException(TextureItem* pWhichItem)
	{
		m_pTextureItem = pWhichItem;
		m_FrameCount = 0;
		m_FailCount = 1;
	}

	TextureException::~TextureException() {};
}}