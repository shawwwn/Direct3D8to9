#include "PostProcessSMAA.h"

#pragma region This stuff is for loading headers from resources
class ID3D9IncludeResource : public ID3DXInclude {
    public:
        STDMETHOD(Open)(THIS_ D3DXINCLUDE_TYPE, LPCSTR pFileName, LPCVOID, LPCVOID *ppData, UINT *pBytes)  {
            std::stringstream s;
            s << pFileName;
			HMODULE currentModule = GetCurrentModule();
            HRSRC src = FindResource(currentModule, s.str().c_str(), RT_RCDATA);
            HGLOBAL res = LoadResource(currentModule, src);

            *pBytes = SizeofResource(currentModule, src);
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
		m_MaxSearchSteps=8;
		m_MaxSearchStepsDiag=8;
	}
	PostProcessSMAA::~PostProcessSMAA()
	{
	}

	HRESULT PostProcessSMAA::initPermanentResources(IDirect3DDevice9* pDevice, UINT width, UINT height)
	{
		m_pDevice = pDevice;

		return D3D_OK;
	}
	HRESULT PostProcessSMAA::initTemporaryResources(IDirect3DDevice9* pDevice, UINT width, UINT height)
	{
		m_deviceWidth = width;
		m_deviceHeight = height;

		#pragma region Load shader
		// Setup the defines for compiling the effect.
		std::vector<D3DXMACRO> defines;
		std::stringstream s;
		// Setup pixel size macro
		/* For newer version
		s << "float4(1.0 / " << width << ", 1.0 / " << height << ", " << width << ", " << height << ")";
		std::string pixelSizeText = s.str();
		D3DXMACRO renderTargetMetricsMacro = { "SMAA_RT_METRICS", pixelSizeText.c_str() };
		defines.push_back(renderTargetMetricsMacro);
		*/
		s << "float2(1.0 / " << width << ", 1.0 / " << height << ")";
		std::string pixelSizeText = s.str();
		D3DXMACRO pixelSizeMacro = { "SMAA_PIXEL_SIZE", pixelSizeText.c_str() };
		defines.push_back(pixelSizeMacro);

		// Setup preset macro
		/* For newer version
		D3DXMACRO presetMacros[] = {
			{ "SMAA_PRESET_LOW", nullptr },
			{ "SMAA_PRESET_MEDIUM", nullptr },
			{ "SMAA_PRESET_HIGH", nullptr },
			{ "SMAA_PRESET_ULTRA", nullptr },
			{ "SMAA_PRESET_CUSTOM", nullptr }
		};
		*/
		D3DXMACRO presetMacros[] = {
			{ "SMAA_PRESET_LOW", "1" },
			{ "SMAA_PRESET_MEDIUM", "1" },
			{ "SMAA_PRESET_HIGH", "1" },
			{ "SMAA_PRESET_ULTRA", "1" },
			{ "SMAA_PRESET_CUSTOM", "1" }
		};
		defines.push_back(presetMacros[int(1)]);	// choose quaility - SMAA_PRESET_MEDIUM
		// End macro
		D3DXMACRO null = { nullptr, nullptr };
		defines.push_back(null);

		// Setup the flags for the effect.
		DWORD flags = D3DXFX_NOT_CLONEABLE;
		#ifdef D3DXFX_LARGEADDRESS_HANDLE
		flags |= D3DXFX_LARGEADDRESSAWARE;
		#endif

		// Load shader
		#ifdef SMAA_ALLOW_LOCAL_FILES
		D3DXCreateEffectFromFile(pDevice, "SMAA.fx", &defines.front(), NULL, flags, NULL, &m_pEffect, NULL);
		#else
		ID3D9IncludeResource includeResource;
		D3DXCreateEffectFromResource(pDevice, GetCurrentModule(), "SMAA.fx", &defines.front(), &includeResource, flags, NULL, &m_pEffect, NULL);
		#endif

		// Create some handles for techniques and variables.
		m_hThresholdHandle = m_pEffect->GetParameterByName(NULL, "threshld");
		m_hMaxSearchStepsHandle = m_pEffect->GetParameterByName(NULL, "maxSearchSteps");
		//m_hMaxSearchStepsDiagHandle = m_pEffect->GetParameterByName(NULL, "maxSearchStepsDiag");
		//m_hCornerRoundingHandle = m_pEffect->GetParameterByName(NULL, "cornerRounding");
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
		#pragma endregion

		#pragma region Initialize vertices
		// Vertex declaration for rendering the typical fullscreen quad later on
		const D3DVERTEXELEMENT9 vertexElements[3] = {
			{ 0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0, 12, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,  0 },
			D3DDECL_END()
		};
		pDevice->CreateVertexDeclaration(vertexElements, &m_pVertDeclPP);

		// Set up our typical aligned fullscreen quad
		D3DXVECTOR2 pixelSize = D3DXVECTOR2(1.0f / float(width), 1.0f / float(height));
		float temp_quad[4][5] = {
			{ -1.0f - pixelSize.x,  1.0f + pixelSize.y, 0.5f, 0.0f, 0.0f },
			{  1.0f - pixelSize.x,  1.0f + pixelSize.y, 0.5f, 1.0f, 0.0f },
			{ -1.0f - pixelSize.x, -1.0f + pixelSize.y, 0.5f, 0.0f, 1.0f },
			{  1.0f - pixelSize.x, -1.0f + pixelSize.y, 0.5f, 1.0f, 1.0f }
		};
		memcpy(m_Quad, temp_quad, sizeof(temp_quad));
		#pragma endregion

		#pragma region Create textures
		// Create Textures
		m_pDevice->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pEdgeTexture, NULL);
        m_pEdgeTexture->GetSurfaceLevel(0, &m_pEdgeSurface);
		m_pDevice->CreateTexture(width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pBlendTexture, NULL);
        m_pBlendTexture->GetSurfaceLevel(0, &m_pBlendSurface);

		// Load the precomputed textures.
		loadAreaTex();
		loadSearchTex();
		#pragma endregion
		return D3D_OK;
	}
	HRESULT PostProcessSMAA::releaseTemporaryResources()
	{
		SAFE_RELEASE(m_pEffect);
		SAFE_RELEASE(m_pVertDeclPP);
		SAFE_RELEASE(m_pEdgeSurface);
		SAFE_RELEASE(m_pEdgeTexture);
		SAFE_RELEASE(m_pBlendTexture);
		SAFE_RELEASE(m_pBlendSurface);
		SAFE_RELEASE(m_pAreaTexture);
		SAFE_RELEASE(m_pSearchTexture);
		return D3D_OK;
	}
	void PostProcessSMAA::loadAreaTex()
	{
	#ifndef SMAA_USE_DDS_PRECOMPUTED_TEXTURES
		D3DXIMAGE_INFO info;
		#ifdef SMAA_ALLOW_LOCAL_FILES
		D3DXGetImageInfoFromFile("AreaTexDX9.dds", &info);
		D3DXCreateTextureFromFileEx(m_pDevice, "AreaTexDX9.dds", info.Width, info.Height, 1, 0, D3DFMT_A8L8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, &info, NULL, &m_pAreaTexture);
		#else
		HMODULE currentModule = GetCurrentModule();
		D3DXGetImageInfoFromResource(currentModule, "AreaTexDX9.dds", &info);
		D3DXCreateTextureFromResourceEx(m_pDevice, currentModule, "AreaTexDX9.dds", info.Width, info.Height, 1, 0, D3DFMT_A8L8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, &info, NULL, &m_pAreaTexture);
		#endif
	#else
		m_pDevice->CreateTexture(AREATEX_WIDTH, AREATEX_HEIGHT, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8L8, D3DPOOL_DEFAULT, &m_pAreaTexture, NULL);
		D3DLOCKED_RECT rect;
		m_pAreaTexture->LockRect(0, &rect, NULL, D3DLOCK_DISCARD);
		for (int i = 0; i < AREATEX_HEIGHT; i++)
			CopyMemory(((char *) rect.pBits) + i * rect.Pitch, areaTexBytes + i * AREATEX_PITCH, AREATEX_PITCH);
		m_pAreaTexture->UnlockRect(0);
	#endif
	}
	void PostProcessSMAA::loadSearchTex()
	{
	#ifndef SMAA_USE_DDS_PRECOMPUTED_TEXTURES
		D3DXIMAGE_INFO info;
		#ifdef SMAA_ALLOW_LOCAL_FILES
		D3DXGetImageInfoFromFile("SearchTex.dds", &info);
		D3DXCreateTextureFromFileEx(m_pDevice, "SearchTex.dds", info.Width, info.Height, 1, 0, D3DFMT_L8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, &info, NULL, &m_pSearchTexture);
		#else
		HMODULE currentModule = GetCurrentModule();
		D3DXGetImageInfoFromResource(currentModule, "SearchTex.dds", &info);
		D3DXCreateTextureFromResourceEx(m_pDevice, currentModule, "SearchTex.dds", info.Width, info.Height, 1, 0, D3DFMT_L8, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0, &info, NULL, &m_pSearchTexture);
		#endif
	#else
		m_pDevice->CreateTexture(SEARCHTEX_WIDTH, SEARCHTEX_HEIGHT, 1, D3DUSAGE_DYNAMIC, D3DFMT_L8, D3DPOOL_DEFAULT, &m_pSearchTexture, NULL);
		D3DLOCKED_RECT rect;
		m_pSearchTexture->LockRect(0, &rect, NULL, D3DLOCK_DISCARD);
		for (int i = 0; i < SEARCHTEX_HEIGHT; i++)
			CopyMemory(((char *) rect.pBits) + i * rect.Pitch, searchTexBytes + i * SEARCHTEX_PITCH, SEARCHTEX_PITCH);
		m_pSearchTexture->UnlockRect(0);
	#endif
	}
	void PostProcessSMAA::edgesDetectionPass(IDirect3DTexture9 *edges, Input input)
	{
		D3DPERF_BeginEvent(D3DCOLOR_XRGB(0, 0, 0), L"SMAA: 1st pass");
		HRESULT hr;

		// Set the render target and clear both the color and the stencil buffers.
		m_pDevice->SetRenderTarget(0, m_pEdgeSurface);
		m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

		// Setup variables.
		m_pEffect->SetFloat(m_hThresholdHandle, m_Threshold);
		m_pEffect->SetFloat(m_hMaxSearchStepsHandle, float(m_MaxSearchSteps));
		//m_pEffect->SetFloat(m_hMaxSearchStepsDiagHandle, float(m_MaxSearchStepsDiag));
		//m_pEffect->SetFloat(m_hCornerRoundingHandle, m_CornerRounding);

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
		m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_Quad, sizeof(m_Quad[0]));
		m_pEffect->EndPass();
		m_pEffect->End();

		D3DPERF_EndEvent();
	}
	void PostProcessSMAA::blendingWeightsCalculationPass() 
	{
		D3DPERF_BeginEvent(D3DCOLOR_XRGB(0, 0, 0), L"SMAA: 2nd pass");
		HRESULT hr;

		// Set the render target and clear it.
		m_pDevice->SetRenderTarget(0, m_pBlendSurface);
		m_pDevice->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

		// Setup the variables and the technique (yet again).
		m_pEffect->SetTexture(m_hEdgesTexHandle, m_pEdgeTexture);
		m_pEffect->SetTexture(m_hAreaTexHandle, m_pAreaTexture);
		m_pEffect->SetTexture(m_hSearchTexHandle, m_pSearchTexture);
		m_pEffect->SetTechnique(m_hBlendWeightCalculationHandle);

		// And here we go!
		UINT passes;
		m_pEffect->Begin(&passes, 0);
		m_pEffect->BeginPass(0);
		m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_Quad, sizeof(m_Quad[0]));
		m_pEffect->EndPass();
		m_pEffect->End();

		D3DPERF_EndEvent();
	}
	void PostProcessSMAA::neighborhoodBlendingPass(IDirect3DTexture9 *src, IDirect3DSurface9 *dst)
	{
		D3DPERF_BeginEvent(D3DCOLOR_XRGB(0, 0, 0), L"SMAA: 3rd pass");
		HRESULT hr;

		// Blah blah blah
		m_pDevice->SetRenderTarget(0, dst);
		m_pEffect->SetTexture(m_hColorTexHandle, src);
		m_pEffect->SetTexture(m_hBlendTexHandle, m_pBlendTexture);
		m_pEffect->SetTechnique(m_hNeighborhoodBlendingHandle);

		// Yeah! We will finally have the antialiased image :D
		UINT passes;
		m_pEffect->Begin(&passes, 0);
		m_pEffect->BeginPass(0);
		m_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_Quad, sizeof(m_Quad[0]));
		m_pEffect->EndPass();
		m_pEffect->End();

		D3DPERF_EndEvent();
	}
	HRESULT PostProcessSMAA::Render(IDirect3DTexture9* pSrcColorTexture, IDirect3DSurface9* pDstSurface)
	{
		m_pDevice->BeginScene();
		// Setup the layout for our fullscreen quad.
		m_pDevice->SetVertexDeclaration(m_pVertDeclPP);

		edgesDetectionPass(pSrcColorTexture, INPUT_COLOR);
		blendingWeightsCalculationPass();
		neighborhoodBlendingPass(pSrcColorTexture, pDstSurface);
		m_pDevice->EndScene();
		return D3D_OK;
	}
	void PostProcessSMAA::onCreateDevice(IDirect3DDevice9* pd3dDevice, UINT width, UINT height)
	{
		initPermanentResources(pd3dDevice, width, height);
		initTemporaryResources(pd3dDevice, width, height);
	}
	void PostProcessSMAA::onLostDevice()
	{
		releaseTemporaryResources();
	}
	void PostProcessSMAA::onResetDevice(IDirect3DDevice9* pd3dDevice, UINT width, UINT height)
	{
		initTemporaryResources(pd3dDevice, width, height);
	}
}