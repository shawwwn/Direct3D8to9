#include "PostProcess.h"

namespace PP {
	// struct definition
	PostProcess::PostProcess()
	{
		m_pEffect=NULL;
		m_hTexSource=NULL;
		m_hTexScene=NULL;
	}
	PostProcess::~PostProcess() {}
	HRESULT PostProcess::Init(IDirect3DDevice9* pDevice, UINT resourceRef)
	{
		HRESULT hr;
		//hr = D3DXCreateEffectFromFile(pDevice, pSrcFile, NULL, NULL,
		//	                          0, // D3DXSHADER_DEBUG | D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT
		//							  NULL, &m_pEffect, NULL);
		hr = D3DXCreateEffectFromResource(pDevice, GetCurrentModule(), MAKEINTRESOURCE(resourceRef), NULL, NULL,
			                          0, // D3DXSHADER_DEBUG | D3DXSHADER_FORCE_VS_SOFTWARE_NOOPT
									  NULL, &m_pEffect, NULL);
		if(FAILED(hr))
			return hr;
		
		// Get the PostProcess technique handle
		m_hTPostProcess = m_pEffect->GetTechniqueByName("PostProcess");

		// Obtain the handles to all texture objects in the effect
		m_hTexScene = m_pEffect->GetParameterByName(NULL, "g_txSceneColor");
		m_hTexSource = m_pEffect->GetParameterByName(NULL, "g_txSrcColor");

		return D3D_OK;
	}
	HRESULT PostProcess::Cleanup()
	{
		m_pEffect->Release();
		return D3D_OK;
	}


	#pragma region Standard Procedure Functions
	void PostProcess::onCreateDevice(IDirect3DDevice9* pd3dDevice)
	{
		Init(pd3dDevice, SHADER_BLOOM_H);
	}
	void PostProcess::onLostDevice()
	{
		m_pEffect->OnLostDevice();
	}
	void PostProcess::onResetDevice(IDirect3DDevice9* pd3dDevice)
	{
		m_pEffect->OnResetDevice();
	}
	void PostProcess::onDestroy(IDirect3DDevice9* pd3dDevice)
	{
		Cleanup();
	}
	#pragma endregion
}