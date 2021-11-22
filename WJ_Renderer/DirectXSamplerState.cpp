#include "OneCompile.h"
#include "DirectXSamplerState.h"

DirectXSamplerState::DirectXSamplerState() : m_pSamplerState(nullptr)
{
}

DirectXSamplerState::~DirectXSamplerState()
{
}

void DirectXSamplerState::CreateDXSamplerState(ID3D11Device* _pDevice)
{
	HRESULT hr = S_OK;

	m_pSamplerState = nullptr;

	D3D11_SAMPLER_DESC samplerdesc;
	ZeroMemory(&samplerdesc, sizeof(D3D11_SAMPLER_DESC));
	samplerdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerdesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerdesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerdesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerdesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerdesc.MinLOD = 0;
	samplerdesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = _pDevice->CreateSamplerState(&samplerdesc, &m_pSamplerState);

	if (FAILED(hr)) { return ; }


}

ID3D11SamplerState* DirectXSamplerState::GetSamplerState()
{
	return this->m_pSamplerState;
}
