#pragma once
class DirectXSamplerState
{
public:
	//
	ID3D11SamplerState* m_pSamplerState;
public:
	DirectXSamplerState();
	~DirectXSamplerState();
private:
public:
	void CreateDXSamplerState(ID3D11Device* _pDevice);
	ID3D11SamplerState* GetSamplerState();
};

