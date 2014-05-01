#include "PostProcessSMAA.h"

#pragma region This stuff is for loading headers from resources
class ID3D10IncludeResource : public ID3DXInclude {
    public:
        STDMETHOD(Open)(THIS_ D3DXINCLUDE_TYPE, LPCSTR pFileName, LPCVOID, LPCVOID *ppData, UINT *pBytes)  {
            std::stringstream s;
            s << pFileName;
            HRSRC src = FindResource(GetModuleHandle(nullptr), s.str().c_str(), RT_RCDATA);
            HGLOBAL res = LoadResource(GetModuleHandle(nullptr), src);

            *pBytes = SizeofResource(GetModuleHandle(nullptr), src);
            *ppData = (LPCVOID) LockResource(res);

            return S_OK;
        }

        STDMETHOD(Close)(THIS_ LPCVOID)  {
            return S_OK;
        }
};
#pragma endregion


namespace PP {
	PostProcessSMAA::PostProcessSMAA()
	{
		m_pEdgeTexture=NULL;
		m_pEdgeSurface=NULL;
		m_pBlendTexture=NULL;
		m_pBlendSurface=NULL;

		m_Threshold=0.1f;
		m_CornerRounding=0.25f;
		m_MaxSearchSteps=16;
		m_MaxSearchStepsDiag=8;
	}
	PostProcessSMAA::~PostProcessSMAA()
	{
	}
	HRESULT PostProcessSMAA::Init(IDirect3DDevice9* pDevice, UINT resourceRef, UINT width, UINT height)
	{
		m_pDevice = pDevice;

		// Setup the defines for compiling the effect.
		std::vector<D3DXMACRO> defines;
		std::stringstream s;
		// Setup pixel size macro
		s << "float4(1.0 / " << width << ", 1.0 / " << height << ", " << width << ", " << height << ")";
		std::string pixelSizeText = s.str();
		D3DXMACRO renderTargetMetricsMacro = { "SMAA_RT_METRICS", pixelSizeText.c_str() };
		defines.push_back(renderTargetMetricsMacro);
		// Setup preset macro
		D3DXMACRO presetMacros[] = {
			{ "SMAA_PRESET_LOW", nullptr },
			{ "SMAA_PRESET_MEDIUM", nullptr },
			{ "SMAA_PRESET_HIGH", nullptr },
			{ "SMAA_PRESET_ULTRA", nullptr },
			{ "SMAA_PRESET_CUSTOM", nullptr }
		};
		defines.push_back(presetMacros[int(3)]);	// choose quaility - SMAA_PRESET_ULTRA
		// End macro
		D3DXMACRO null = { nullptr, nullptr };
		defines.push_back(null);

		// Setup the flags for the effect.
		DWORD flags = D3DXFX_NOT_CLONEABLE;
		#ifdef D3DXFX_LARGEADDRESS_HANDLE
		flags |= D3DXFX_LARGEADDRESSAWARE;
		#endif

		// Load Shader
		//ID3D10IncludeResource includeResource;
		//D3DXCreateEffectFromResource(device, NULL, L"SMAA.fx", &defines.front(), &includeResource, flags, NULL, &effect, NULL)
		D3DXCreateEffectFromFile(m_pDevice, "SMAA.fx", &defines.front(), NULL, flags, NULL, &m_pEffect, NULL);

		// Create Textures
		m_pDevice->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A16B16G16R16F, D3DPOOL_DEFAULT, &m_pEdgeTexture, NULL);
        m_pEdgeTexture->GetSurfaceLevel(0, &m_pEdgeSurface);
		m_pDevice->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A16B16G16R16F, D3DPOOL_DEFAULT, &m_pBlendTexture, NULL);
        m_pBlendTexture->GetSurfaceLevel(0, &m_pBlendSurface);

		// Load the precomputed textures.
		loadAreaTex();
		loadSearchTex();

		// Create some handles for techniques and variables.
		m_hThresholdHandle = m_pEffect->GetParameterByName(NULL, "threshld");
		m_hMaxSearchStepsHandle = m_pEffect->GetParameterByName(NULL, "maxSearchSteps");
		m_hMaxSearchStepsDiagHandle = m_pEffect->GetParameterByName(NULL, "maxSearchStepsDiag");
		m_hCornerRoundingHandle = m_pEffect->GetParameterByName(NULL, "cornerRounding");
		m_hAreaTexHandle = m_pEffect->GetParameterByName(NULL, "areaTex2D");
		m_hSearchTexHandle = m_pEffect->GetParameterByName(NULL, "searchTex2D");
		m_hColorTexHandle = m_pEffect->GetParameterByName(NULL, "colorTex2D");
		m_hDepthTexHandle = m_pEffect->GetParameterByName(NULL, "depthTex2D");
		m_hEdgesTexHandle = m_pEffect->GetParameterByName(NULL, "edgesTex2D");
		m_hBlendTexHandle = m_pEffect->GetParameterByName(NULL, "blendTex2D");
		m_hLumaEdgeDetectionHandle = m_pEffect->GetTechniqueByName("LumaEdgeDetection");
		m_hColorEdgeDetectionHandle = m_pEffect->GetTechniqueByName("ColorEdgeDetection");
		m_hDepthEdgeDetectionHandle = m_pEffect->GetTechniqueByName("DepthEdgeDetection");
		m_hBlendWeightCalculationHandle = m_pEffect->GetTechniqueByName("BlendWeightCalculation");
		m_hNeighborhoodBlendingHandle = m_pEffect->GetTechniqueByName("NeighborhoodBlending");
		return D3D_OK;
	}
	HRESULT PostProcessSMAA::Cleanup()
	{
		// TODO; Release temportary textures
		return D3D_OK;
	}

	void PostProcessSMAA::loadAreaTex()
	{
		#if SMAA_USE_DDS_PRECOMPUTED_TEXTURES
		D3DXIMAGE_INFO info;
		//D3DXGetImageInfoFromResource(GetCurrentModule(), "AreaTexDX9.dds", &info);
		D3DXGetImageInfoFromFile("AreaTexDX9.dds", &info);
		//D3DXCreateTextureFromResourceEx(m_pDevice, GetCurrentModule(), "AreaTexDX9.dds", info.Width, info.Height, 1, 0, D3DFMT_A8L8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, &info, NULL, &m_pAreaTexture);
		D3DXCreateTextureFromFileEx(m_pDevice, "AreaTexDX9.dds", info.Width, info.Height, 1, 0, D3DFMT_A8L8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, &info, NULL, &m_pAreaTexture);
		#else
		device->CreateTexture(AREATEX_WIDTH, AREATEX_HEIGHT, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8L8, D3DPOOL_DEFAULT, &areaTex, NULL);
		D3DLOCKED_RECT rect;
		areaTex->LockRect(0, &rect, NULL, D3DLOCK_DISCARD);
		for (int i = 0; i < AREATEX_HEIGHT; i++)
			CopyMemory(((char *) rect.pBits) + i * rect.Pitch, areaTexBytes + i * AREATEX_PITCH, AREATEX_PITCH);
		areaTex->UnlockRect(0);
		#endif
	}
	void PostProcessSMAA::loadSearchTex()
	{
		#if SMAA_USE_DDS_PRECOMPUTED_TEXTURES
		D3DXIMAGE_INFO info;
		//D3DXGetImageInfoFromResource(GetCurrentModule(), "SearchTex.dds", &info);
		D3DXGetImageInfoFromFile("SearchTex.dds", &info);
		//D3DXCreateTextureFromResourceEx(m_pDevice, GetCurrentModule(), "SearchTex.dds", info.Width, info.Height, 1, 0, D3DFMT_L8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, &info, NULL, &m_pSearchTexture);
		D3DXCreateTextureFromFileEx(m_pDevice, "SearchTex.dds", info.Width, info.Height, 1, 0, D3DFMT_L8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, &info, NULL, &m_pSearchTexture);
		#else
		m_pDevice->CreateTexture(SEARCHTEX_WIDTH, SEARCHTEX_HEIGHT, 1, D3DUSAGE_DYNAMIC, D3DFMT_L8, D3DPOOL_DEFAULT, &m_pSearchTexture, NULL);
		D3DLOCKED_RECT rect;
		searchTex->LockRect(0, &rect, NULL, D3DLOCK_DISCARD);
		for (int i = 0; i < SEARCHTEX_HEIGHT; i++)
			CopyMemory(((char *) rect.pBits) + i * rect.Pitch, searchTexBytes + i * SEARCHTEX_PITCH, SEARCHTEX_PITCH);
		searchTex->UnlockRect(0);
		#endif
	}
	void PostProcessSMAA::edgesDetectionPass(IDirect3DTexture9 *edges, Input input)
	{
		D3DPERF_BeginEvent(D3DCOLOR_XRGB(0, 0, 0), L"SMAA: 1st pass");

		// Set the render target and clear both the color and the stencil buffers.
		//m_pDevice->SetRenderTarget(0, m_pEdgeSurface);
		m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

		// Setup variables.
		m_pEffect->SetFloat(m_hThresholdHandle, m_Threshold);
		m_pEffect->SetFloat(m_hMaxSearchStepsHandle, float(m_MaxSearchSteps));
		m_pEffect->SetFloat(m_hMaxSearchStepsDiagHandle, float(m_MaxSearchStepsDiag));
		m_pEffect->SetFloat(m_hCornerRoundingHandle, m_CornerRounding);

		// Select the technique accordingly.
		switch (input) {
			case INPUT_LUMA:
				m_pEffect->SetTexture(m_hColorTexHandle, edges);
				m_pEffect->SetTechnique(m_hLumaEdgeDetectionHandle);
				break;
			case INPUT_COLOR:
				m_pEffect->SetTexture(m_hColorTexHandle, edges);
				m_pEffect->SetTechnique(m_hColorEdgeDetectionHandle);
				break;
			case INPUT_DEPTH:
				m_pEffect->SetTexture(m_hDepthTexHandle, edges);
				m_pEffect->SetTechnique(m_hDepthEdgeDetectionHandle);
				break;
			default:
				throw std::logic_error("unexpected error");
		}

		// Do it!
		UINT passes;
		m_pEffect->Begin(&passes, 0);
		m_pEffect->BeginPass(0);
		m_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		m_pEffect->EndPass();
		m_pEffect->End();

		D3DPERF_EndEvent();
	}

	HRESULT PostProcessSMAA::Render(IDirect3DTexture9* pSrcColorTexture, IDirect3DSurface9* pDstSurface)
	{
		// Setup the layout for our fullscreen quad. (not necessary)

		edgesDetectionPass(pSrcColorTexture, INPUT_COLOR);
		//blendingWeightsCalculationPass();
		//neighborhoodBlendingPass(pSrcColorTexture);
		return D3DERR_INVALIDCALL;
	}
	void PostProcessSMAA::onCreateDevice(IDirect3DDevice9* pd3dDevice)
	{
		Init(pd3dDevice, SHADER_SAMPLE_H, 800, 600);
	}
}