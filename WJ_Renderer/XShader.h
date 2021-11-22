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


	//���̴��̴�.
	ID3D11VertexShader* m_pShader;
	//�������̴��� �����ϱ� ���� ������ �߰�
	ID3D10Blob* m_pVertexShaderBuffer;
	//��ǲ���̾ƿ�
	ID3D11InputLayout* m_pInputLayout;
};

class XPixelShader
{
public:
	bool Initialize(ID3D11Device* _pDevice, std::wstring _wShaderPath, D3D11_INPUT_ELEMENT_DESC* _InputElementDESC, UINT _NumElement);
	ID3D11PixelShader* GetShader();
	ID3D10Blob*		   GetBuffer();
public:


	//���̴��̴�.
	ID3D11PixelShader* m_pShader;
	//�������̴��� �����ϱ� ���� ������ �߰�
	ID3D10Blob* m_pPixelShaderBuffer;
};
 