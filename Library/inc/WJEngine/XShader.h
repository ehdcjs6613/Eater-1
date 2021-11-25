#pragma once
#include <string>

class XVertexShader
{
public:
	bool Initialize(ID3D11Device* _pDevice, std::wstring _wShaderPath, D3D11_INPUT_ELEMENT_DESC* _InputElementDESC,UINT _NumElement);
	ID3D11VertexShader*			GetShader();
	ID3D10Blob*					GetBuffer();
	ID3D11InputLayout*			GetInputLayout();
public:


	//셰이더이다.
	ID3D11VertexShader* m_pShader;
	//정점셰이더를 저장하기 위한 변수를 추가
	ID3D10Blob* m_pVertexShaderBuffer;
	//인풋레이아웃
	ID3D11InputLayout* m_pInputLayout;
};

class XPixelShader
{
public:
	bool Initialize(ID3D11Device* _pDevice, std::wstring _wShaderPath, D3D11_INPUT_ELEMENT_DESC* _InputElementDESC, UINT _NumElement);
	ID3D11PixelShader* GetShader();
	ID3D10Blob*		   GetBuffer();
public:


	//셰이더이다.
	ID3D11PixelShader* m_pShader;
	//정점셰이더를 저장하기 위한 변수를 추가
	ID3D10Blob* m_pPixelShaderBuffer;
};
 