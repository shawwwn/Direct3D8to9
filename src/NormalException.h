#pragma once

#ifdef _DEBUG
#include "debug/NormalTable.h"
#else
#include "NormalTable.h"
#endif

namespace NP { namespace EXCP {

	//==========================================================================
	//
	//	NormalException Struct
	//
	//	Stores the exception count and the frame count.
	//	@m_FailCount :  For counting D3DXComputeTexture exception.
	//	@m_FrameCount : For counting the frame past after the exception happen.
	//	@m_pWhichItem : The failing NormalItem 
	//
	//==========================================================================
	struct NormalException
	{
		public:
			NormalException(NormalItem* pWhichItem);
			~NormalException();

			UINT m_FrameCount;
			UINT m_FailCount;
			NormalItem* m_pTextureItem;
	};

}}