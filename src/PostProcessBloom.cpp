#include "PostProcessBloom.h"

namespace PP {
	PostProcessBloom::PostProcessBloom() {}
	PostProcessBloom::~PostProcessBloom() {}
	HRESULT PostProcessBloom::initPermanentResources(IDirect3DDevice9* pDevice, UINT width, UINT height)
	{
		m_pDevice = pDevice;

		HRESULT hr;
		hr = D3DXCreateEffectFromResource(pDevice, GetCurrentModule(), "PP_ColorBloomH.fx", NULL, NULL, 0, NULL, &m_pEffect, NULL);
		if(FAILED(hr))
			return hr;
		m_hTPostProcess = m_pEffect->GetTechniqueByName("PostProcess");
		m_hTexScene = m_pEffect->GetParameterByName(NULL, "g_txSceneColor");
		m_hTexSource = m_pEffect->GetParameterByName(NULL, "g_txSrcColor");

		return D3D_OK;
	}

	#pragma region Standard Procedure Functions
	void PostProcessBloom::onCreateDevice(IDirect3DDevice9* pd3dDevice, UINT width, UINT height)
	{
		initPermanentResources(pd3dDevice, width, height);
		initTemporaryResources(pd3dDevice, width, height);
	}
	#pragma endregion
}