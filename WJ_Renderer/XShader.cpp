#include "OneCompile.h"
#include "XShader.h"
#include <d3d11.h>

#include <d3dcompiler.h>

/// <summary>
/// 버텍스 셰이더이다.
/// </summary>
/// <param name="_pDevice"></param>
/// <param name="_wShaderPath"></param>
/// <param name="_InputElementDESC"></param>
/// <param name="_NumElement"></param>
/// <returns></returns>
bool XVertexShader::Initialize(ID3D11Device* _pDevice, std::wstring _wShaderPath, D3D11_INPUT_ELEMENT_DESC* _InputElementDESC, UINT _NumElement)
{
	HRESULT hr =S_OK;

	hr = D3DReadFileToBlob
	(
		_wShaderPath.c_str(), &this->m_pVertexShaderBuffer
	);

	hr = _pDevice->CreateVertexShader
	(
		this->m_pVertexShaderBuffer->GetBufferPointer(),
		this->m_pVertexShaderBuffer->GetBufferSize(),
		nullptr,
		&this->m_pShader
	);

	hr = _pDevice->
		CreateInputLayout
		(
			_InputElementDESC, _NumElement, m_pVertexShaderBuffer->GetBufferPointer(),
			(m_pVertexShaderBuffer)->GetBufferSize(),
			&(m_pInputLayout)
		);

	if (FAILED(hr))
	{
		return true;
	}

	return false;
}

ID3D11VertexShader* XVertexShader::GetShader()
{
	return (this->m_pShader);
}

ID3D10Blob* XVertexShader::GetBuffer()
{
	return (this->m_pVertexShaderBuffer);
}

ID3D11InputLayout* XVertexShader::GetInputLayout()
{
	return (this->m_pInputLayout);
}

/// <summary>
/// 픽셀 셰이더이다.
/// </summary>
/// <param name="_pDevice"></param>
/// <param name="_wShaderPath"></param>
/// <param name="_InputElementDESC"></param>
/// <param name="_NumElement"></param>
/// <returns></returns>

bool XPixelShader::Initialize(ID3D11Device* _pDevice, std::wstring _wShaderPath, D3D11_INPUT_ELEMENT_DESC* _InputElementDESC, UINT _NumElement)
{
	HRESULT hr = S_OK;

	hr = D3DReadFileToBlob
	(
		_wShaderPath.c_str(), &this->m_pPixelShaderBuffer
	);

	hr = _pDevice->CreatePixelShader
	(
		this->m_pPixelShaderBuffer->GetBufferPointer(),
		this->m_pPixelShaderBuffer->GetBufferSize(),
		nullptr,
		&this->m_pShader
	);


	if (FAILED(hr))
	{
		MessageBox(NULL,
			L"NO SHADER", L"Error", MB_OK);
		return true;
	}

	return false;
}

ID3D11PixelShader* XPixelShader::GetShader()
{
	return (this->m_pShader);
}

ID3D10Blob* XPixelShader::GetBuffer()
{
	return (this->m_pPixelShaderBuffer);;
}
