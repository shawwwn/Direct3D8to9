#pragma once

#include "NormalTable.h"

namespace NP { namespace EXCP {

	//==========================================================================
	//
	//	NormalException Struct
	//
	//	Stores the exception count and the frame count.
	//	@m_FailCount :  For counting D3DXComputeTexture exception.
	//	@m_FrameCount : For counting the frame past after the exception happen.
	//	@m_pWhichItem : The failing NormalData 
	//
	//==========================================================================
	struct NormalException
	{
		public:
			NormalException(NormalData* pWhichItem);
			~NormalException();

			UINT m_FrameCount;
			UINT m_FailCount;
			NormalData* m_pTextureItem;
	};

}}