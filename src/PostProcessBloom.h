#pragma once

#include "PostProcess.h"

namespace PP {
	struct PostProcessBloom: public PostProcess
	{
		protected:
			HRESULT initPermanentResources(IDirect3DDevice9* pDevice, UINT resourceRef, UINT width, UINT height);
		public:
			PostProcessBloom();
			~PostProcessBloom();
			
			//
			// Standard Procedure Functions
			//
			void onCreateDevice(IDirect3DDevice9* pd3dDevice, UINT width, UINT height);
	};
}