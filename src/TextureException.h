#pragma once

#include "NormalTable.h"

namespace NP { namespace EXCP {

	//==========================================================================
	//
	//	TextureException Struct
	//
	//	Stores the exception count and the frame count.
	//	@m_FailCount :  For counting D3DXComputeTexture exception.
	//	@m_FrameCount : For counting the frame past after the exception happen.
	//	@m_pWhichItem : The failing TextureItem 
	//
	//==========================================================================
	struct TextureException
	{
		public:
			TextureException(TextureItem* pWhichItem);
			~TextureException();

			UINT m_FrameCount;
			UINT m_FailCount;
			TextureItem* m_pTextureItem;
	};

}}