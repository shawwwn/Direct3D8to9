#include "PostProcessBloom.h"

namespace PP {
	// struct definition
	PostProcessBloom::PostProcessBloom() {}
	PostProcessBloom::~PostProcessBloom() {}
	HRESULT PostProcessBloom::Init(IDirect3DDevice9* pDevice, UINT resourceRef)
	{
		m_pDevice = pDevice;
		HRESULT hr;
		hr = D3DXCreateEffectFromResource(m_pDevice, GetCurrentModule(), MAKEINTRESOURCE(resourceRef), 
											NULL, NULL, 0, NULL, &m_pEffect, NULL);
		if(FAILED(hr))
			return hr;
		m_hTPostProcess = m_pEffect->GetTechniqueByName("PostProcess");
		m_hTexScene = m_pEffect->GetParameterByName(NULL, "g_txSceneColor");
		m_hTexSource = m_pEffect->GetParameterByName(NULL, "g_txSrcColor");

		return D3D_OK;
	}


	#pragma region Standard Procedure Functions
	void PostProcessBloom::onCreateDevice(IDirect3DDevice9* pd3dDevice)
	{
		Init(pd3dDevice, SHADER_BLOOM_H);
	}
	#pragma endregion
}