#pragma once

#include "PostProcess.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "DebugUtils.h"
#include "SearchTex.h"
#include "AreaTex.h"

namespace PP {
	//#define SMAA_USE_DDS_PRECOMPUTED_TEXTURES
	//#define SMAA_ALLOW_LOCAL_FILES

	struct PostProcessSMAA : public PostProcess
	{
		enum Preset { PRESET_LOW, PRESET_MEDIUM, PRESET_HIGH, PRESET_ULTRA, PRESET_CUSTOM };
        enum Input { INPUT_LUMA, INPUT_COLOR, INPUT_DEPTH };
		IDirect3DTexture9 *m_pEdgeTexture, *m_pBlendTexture;
		IDirect3DSurface9 *m_pEdgeSurface, *m_pBlendSurface;
		IDirect3DTexture9 *m_pAreaTexture, *m_pSearchTexture;

		D3DXHANDLE m_hThresholdHandle;
        D3DXHANDLE m_hMaxSearchStepsHandle, m_hMaxSearchStepsDiagHandle;
        D3DXHANDLE m_hCornerRoundingHandle;
        D3DXHANDLE m_hAreaTexHandle, m_hSearchTexHandle;
        D3DXHANDLE m_hColorTexHandle, m_hDepthTexHandle;
        D3DXHANDLE m_hEdgesTexHandle, m_hBlendTexHandle;
        D3DXHANDLE m_hLumaEdgeDetectionHandle, m_hColorEdgeDetectionHandle, m_hDepthEdgeDetectionHandle,
                   m_hBlendWeightCalculationHandle, m_hNeighborhoodBlendingHandle;
		
		int m_MaxSearchSteps;
        int m_MaxSearchStepsDiag;
        float m_CornerRounding;
        float m_Threshold;
		float m_Quad[4][5];

		D3DXHANDLE   m_hTPostProcess;			// PostProcess technique handle
		D3DXHANDLE   m_hTexSource;				// Handle to the post-process source textures
		D3DXHANDLE   m_hTexScene;				// Handle to the saved scene texture

		protected:
			HRESULT initPermanentResources(IDirect3DDevice9* pDevice, UINT width, UINT height);
			HRESULT initTemporaryResources(IDirect3DDevice9* pDevice, UINT width, UINT height);
			HRESULT releaseTemporaryResources();

		private:
			void loadAreaTex();
			void loadSearchTex();
			void edgesDetectionPass(IDirect3DTexture9 *edges, Input input);
			void blendingWeightsCalculationPass();
			void neighborhoodBlendingPass(IDirect3DTexture9 *src, IDirect3DSurface9 *dst);

		public:
			PostProcessSMAA();
			~PostProcessSMAA();

			//
			// Standard Procedure Functions
			//
			
			HRESULT Render(IDirect3DTexture9* pSrcColorTexture, IDirect3DSurface9* pDstSurface);
			void onCreateDevice(IDirect3DDevice9* pd3dDevice, UINT width, UINT height);
			void onLostDevice();
			void onResetDevice(IDirect3DDevice9* pd3dDevice, UINT width, UINT height);
			//void onDestroy(IDirect3DDevice9* pd3dDevice);
	};
}