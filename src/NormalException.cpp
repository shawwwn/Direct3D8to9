#include "NormalException.h"

namespace NP { namespace EXCP {

	NormalException::NormalException(NormalItem* pWhichItem)
	{
		m_pTextureItem = pWhichItem;
		m_FrameCount = 0;
		m_FailCount = 1;
	}

	NormalException::~NormalException() {};
}}