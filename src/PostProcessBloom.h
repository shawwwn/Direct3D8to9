#pragma once

#include "PostProcess.h"

namespace PP {
	struct PostProcessBloom: public PostProcess
	{
		protected:
			HRESULT Init(IDirect3DDevice9* pDevice, UINT resourceRef);
		public:
			PostProcessBloom();
			~PostProcessBloom();
			
			//
			// Standard Procedure Functions
			//
			void onCreateDevice(IDirect3DDevice9* pd3dDevice);
	};
}