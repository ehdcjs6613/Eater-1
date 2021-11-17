#pragma once
#include <d3d11shader.h>
#include <string>
#include "d3dcommon.h"
#include "Data.h"
#include <map>


struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11ShaderReflection;
class ShaderManager 
{
public:
	ShaderManager();
	~ShaderManager();

	//�ʱ�ȭ
	void Initialize(ID3D11Device* mDevice,ID3D11DeviceContext* DeviceContext);
	//���̴� �ε�
	bool LoadShader(std::string vsFileName, std::string psFileName, std::string ShaderName);

	//���̴� ��������
	ShaderData GetShader(std::string name);
	//���÷� ��������
	ID3D11SamplerState* GetSampler(std::string name);
	//������� ��������
	ID3D11Buffer* GetConstantBuffer(std::string name);
private:
	//�ε� ���ý� ���̴�
	bool LoadVertexShader(std::string vsFileName, std::string ShaderName);
	//�ε� �ȼ� ���̴�
	bool LoadPixelShader(std::string psFileName, std::string ShaderName);
	//���÷� ����
	bool CreateSampler();
	//��ǲ ���̾ƿ��� �����
	bool CreateInputLayout(std::string shaderName, ID3D10Blob* vertexBuffer);
	//������۸� �����
	bool CreateConstantBuffer();
	//Format ã��
	DXGI_FORMAT FindFormat(int number, BYTE size, D3D11_SIGNATURE_PARAMETER_DESC desc);
private:
	ID3D11Device*			Device;
	ID3D11DeviceContext*	DeviceContext;

	ID3D11ShaderReflection* ReFlector;
	std::string ShaderPath;


	//���̴� ����
	std::map<std::string, ShaderData> ShaderList;
	//���÷� ����
	std::map<std::string, ID3D11SamplerState*>  SamplerList;
	//���ؽ�Ʈ ����
	std::map<std::string, ID3D11Buffer*> CbufferList;
};