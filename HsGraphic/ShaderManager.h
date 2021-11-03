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

	//초기화
	void Initialize(ID3D11Device* Device,ID3D11DeviceContext* DeviceContext);
	//쉐이더 로드
	bool LoadShader(std::string vsFileName, std::string psFileName, std::string ShaderName);
	//쉐이더 경로 
	bool SetShaderFilePath(std::string path);

	//인풋 레이아웃을 만든다
	bool CreateInputLayout(std::string shaderName, ID3D10Blob* vertexBuffer);
private:
	//로드 버택스 쉐이더
	bool LoadVertexShader(std::string vsFileName, std::string ShaderName);
	//로드 픽셀 쉐이더
	bool LoadPixelShader(std::string psFileName, std::string ShaderName);
	//샘플러 생성
	bool CreateSampler(std::string SamplerName);
	//Format 찾기
	DXGI_FORMAT FindFormat(int number, BYTE size, D3D11_SIGNATURE_PARAMETER_DESC desc);
private:
	ID3D11Device*			mDevice;
	ID3D11DeviceContext*	DeviceContext;

	ID3D11ShaderReflection* ReFlector;
	std::string ShaderPath;

	
	std::map<std::string, ShaderData> ShaderList;
};