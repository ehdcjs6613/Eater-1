#pragma once
#include <string>
#include "d3dcommon.h"
#include "d3d11shader.h"
#include "dxgiformat.h"
#include "Data.h"
#include <map>

struct ID3D11Device;
struct ID3D11DeviceContext;
class ShaderManager 
{
public:
	ShaderManager();
	~ShaderManager();

	//�ʱ�ȭ
	void Initialize(ID3D11Device* Device,ID3D11DeviceContext* DeviceContext);
	//���̴� �ε�
	bool LoadShader(std::string vsFileName, std::string psFileName, std::string ShaderName);
	//���̴� ��� 
	bool SetShaderFilePath(std::string path);

	//��ǲ ���̾ƿ��� �����
	bool CreateInputLayout(std::string shaderName, ID3D10Blob* vertexBuffer);
private:
	//�ε� ���ý� ���̴�
	bool LoadVertexShader(std::string vsFileName, std::string ShaderName);
	//�ε� �ȼ� ���̴�
	bool LoadPixelShader(std::string psFileName, std::string ShaderName);
	//���÷� ����
	bool CreateSampler(std::string SamplerName);
	//Format ã��
	DXGI_FORMAT FindFormat(int number, BYTE size, D3D11_SIGNATURE_PARAMETER_DESC desc);
private:
	ID3D11Device*			mDevice;
	ID3D11DeviceContext*	DeviceContext;

	ID3D11ShaderReflection* ReFlector;
	std::string ShaderPath;

	
	std::map<std::string, ShaderData> ShaderList;
};