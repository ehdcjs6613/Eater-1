#include "ShaderManager.h"
#include "HsDefine.h"
#include "HsEngineHelper.h"
#include <vector>

ShaderManager::ShaderManager()
{
	mDevice			= nullptr;
	DeviceContext	= nullptr;
}

ShaderManager::~ShaderManager()
{
	mDevice			= nullptr;
	DeviceContext	= nullptr;
}

void ShaderManager::Initialize(ID3D11Device* Device, ID3D11DeviceContext* DeviceContext)
{
	mDevice = Device;
	DeviceContext = DeviceContext;

	ShaderPath = "../Shader/HS/";

	LoadShader("texture_vs.hlsl","texture_ps","texture");
}

bool ShaderManager::LoadShader(std::string vsFileName, std::string psFileName, std::string ShaderName)
{
	ShaderList.insert({ShaderName,ShaderData()});

	//���ؽ� ���̴��� �ε��Ѵ� (��ǲ ���̾ƿ��� ���⼭)
	if (LoadVertexShader(vsFileName, ShaderName) == false)
	{
		//�����Ѵٸ�
	}

	//�ȼ� ���̴��� �ε��Ѵ�
	if (LoadPixelShader(psFileName, ShaderName) == false)
	{
		//�����Ѵٸ�
	}
	


	return false;
}

bool ShaderManager::CreateSampler(std::string SamplerName)
{
	return false;
}

bool ShaderManager::SetShaderFilePath(std::string path)
{
	return false;
}

bool ShaderManager::CreateInputLayout(std::string shaderName, ID3D10Blob* vertexBuffer)
{
	//����� ���� ��������
	D3D11_SHADER_DESC desc;
	HR(ReFlector->GetDesc(&desc));

	//���̴� ���̾ƿ� ������ ������
	UINT inputLayCount = desc.InputParameters;

	//���̾ƿ� ������ŭ �迭����� �����
	std::vector<D3D11_INPUT_ELEMENT_DESC> DescList;
	DescList.resize((int)inputLayCount);

	//ó�� ���°��� 0�������� ���⶧����
	int TypeSize = 0;

	for (int i = 0; i < inputLayCount; i++)
	{
		//�Ѱ��� ���̾ƿ� ����ü�� ������
		D3D11_SIGNATURE_PARAMETER_DESC desc;
		ReFlector->GetInputParameterDesc(i, &desc);

		BYTE numberMask = desc.Mask;
		int number = (int)desc.ComponentType;
		DXGI_FORMAT FormatNumver = FindFormat(number, numberMask, desc);


		//�Ѱ��� ���̾ƿ� ����ü�� �ֱ�
		DescList[i].SemanticName			= desc.SemanticName;
		DescList[i].SemanticIndex			= 0;
		DescList[i].Format					= FormatNumver;
		DescList[i].InputSlot				= 0;
		DescList[i].AlignedByteOffset		= TypeSize;
		DescList[i].InputSlotClass			= D3D11_INPUT_PER_VERTEX_DATA;
		DescList[i].InstanceDataStepRate	= 0;

		//�Ѱ��� �ϼ��� �Ǿ��� �ڷ����� ���� �˷���� �������� �״������� �����⶧����
		switch (numberMask)
		{
		case 0b00000001:	//float
			TypeSize += 4; 
			break;
		case 0b00000011:	//float2
			TypeSize += 8; 
			break;
		case 0b00000111:	//float3
			TypeSize += 12; 
			break;
		case 0b00001111:	//float4
			TypeSize += 16; 
			break;
		}
	}
	
	//���̾ƿ� ����ü�� ���� �ٳ־��� �������ش�
	ID3D10Blob* vertexShaderBuffer = vertexBuffer;
	ID3D11InputLayout* m_layout = nullptr;
	HRESULT result;


	result = mDevice->CreateInputLayout
	(
		&DescList[0],
		inputLayCount,
		vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(),
		&m_layout
	);

	//���п��θ� Ȯ��
	if (FAILED(result))
	{
		ShaderList[shaderName].Layout = nullptr;
		return false;
	}
	else
	{
		ShaderList[shaderName].Layout = m_layout;
		return true;
	}
}

DXGI_FORMAT ShaderManager::FindFormat(int number, BYTE Mask, D3D11_SIGNATURE_PARAMETER_DESC desc)
{
	DXGI_FORMAT FormatType = DXGI_FORMAT();

	if (number == D3D_REGISTER_COMPONENT_FLOAT32)
	{
		number + 1;
		switch (Mask)
		{
		case 0b00000001:
			FormatType = DXGI_FORMAT_R32_FLOAT;
			break;
		case 0b00000011:
			FormatType = DXGI_FORMAT_R32G32_FLOAT;
			break;
		case 0b00000111:
			FormatType = DXGI_FORMAT_R32G32B32_FLOAT;
			break;
		case 0b00001111:
			FormatType = DXGI_FORMAT_R32G32B32A32_FLOAT;
			break;
		default:
			break;
		}
	}
	else if (number == D3D_REGISTER_COMPONENT_UINT32)
	{
		switch (Mask)
		{
		case 0b00000001:
			FormatType = DXGI_FORMAT_R32_UINT;
			break;
		case 0b00000011:
			FormatType = DXGI_FORMAT_R32G32_UINT;
			break;
		case 0b00000111:
			FormatType = DXGI_FORMAT_R32G32B32_UINT;
			break;
		case 0b00001111:
			FormatType = DXGI_FORMAT_R32G32B32A32_UINT;
			break;
		default:
			break;
		}
	}
	else if (number == D3D_REGISTER_COMPONENT_SINT32)
	{
		switch (Mask)
		{
		case 0b00000001:
			FormatType = DXGI_FORMAT_R32_SINT;
			break;
		case 0b00000011:
			FormatType = DXGI_FORMAT_R32G32_SINT;
			break;
		case 0b00000111:
			FormatType = DXGI_FORMAT_R32G32B32_SINT;
			break;
		case 0b00001111:
			FormatType = DXGI_FORMAT_R32G32B32A32_SINT;
			break;
		default:
			break;
		}
	}
	return FormatType;
}

bool ShaderManager::LoadVertexShader(std::string vsFileName, std::string ShaderName)
{
	HRESULT result;
	ID3D11VertexShader* m_vertexShader;
	ID3D10Blob* _vertexShaderBuffer;

	//string ���� LPCTSTR������ �ٲ���
	std::string temp = "";
	temp += ShaderPath;
	temp += vsFileName;
	CString lpctpath = temp.c_str();
	LPCTSTR path = lpctpath;

	//�÷��� ����
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef DEBUG
	dwShaderFlags |= D3DCOMPILE_DEBUG;
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif 

	//���ý� ���̴��� �ε� �Ѵ�
	result = D3DCompileFromFile
	(
		path,								//���̴� �ڵ尡 ����ִ� �����̸�
		NULL,								//���̴� ��ũ�θ� ���� ������������� NULL
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	//�⺻���� �ڵ鷯�� ���� ������ (�⺻�� NULL)
		"main",								//���̴� ������ ���۵Ǵ� ���̴� ������ �Լ��� �̸�
		"vs_5_0",							//�������� ���̴� ��� ����
		dwShaderFlags,						//������ ���̴� �÷��� 1
		0,									//������ ���̴� �÷��� 2
		&_vertexShaderBuffer,				//��ȯ��
		NULL								//�����޼��� ��ȯ��
	);
	//�����ϸ� ����..
	if (FAILED(result))
	{
		return false;
	}


	//��Ŀ�� ����
	ID3D11ClassLinkage* g_pPsClassLinkage = nullptr;
	mDevice->CreateClassLinkage(&g_pPsClassLinkage);


	//���۷� ���� ���� ���̴��� �����Ѵ�
	result = mDevice->CreateVertexShader
	(
		_vertexShaderBuffer->GetBufferPointer(), //�����ϵ� ���̴��� ���� ������
		_vertexShaderBuffer->GetBufferSize(),	//�����ϵ� �������̴��� ũ��
		g_pPsClassLinkage,						//Ŭ���� ��ũ �������̽��� ���� ������
		&m_vertexShader							//ID3D11VertexShader �������̽��� ���� ������ �ּ�
	);


	//�����ϸ� ����..
	if (FAILED(result))
	{
		ShaderList[ShaderName].VertexShader = nullptr;
		return false;
	}
	else
	{
		//���ؽ� ���̴��� �־��ش�
		ShaderList[ShaderName].VertexShader = m_vertexShader;
	}

	//���̴� ���÷����� ���� �غ�
	HR(D3DReflect(_vertexShaderBuffer->GetBufferPointer(),_vertexShaderBuffer->GetBufferSize(),
		IID_ID3D11ShaderReflection,(void**)&ReFlector));



	
	//��ǲ���̾ƿ��� �����Ѵ�
	if (CreateInputLayout(ShaderName, _vertexShaderBuffer) == false)
	{
		return false;
	}



	//������۸� �����Ѵ� �̹� �ִ� ���۶�� ������������..
	//CreateConstantBuffer();

	//���÷��� �����Ѵ� �̹��ִ� ���÷���� ���������ʴ´�
//	CreateSamPler(ShaderName);

	//������ ��� �о����� ����
	ReFlector->Release();
	ReFlector = nullptr;

	return true;
}

bool ShaderManager::LoadPixelShader(std::string psFileName, std::string ShaderName)
{
	HRESULT result;
	ID3D11PixelShader* m_pixelShader = nullptr;
	ID3D10Blob* pixelShaderBuffer = nullptr;

	std::string temp = "";
	temp += ShaderPath;
	temp += psFileName;
	CString lpctpath = temp.c_str();
	LPCTSTR path = lpctpath;

	//�÷��� ����
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef DEBUG
	dwShaderFlags |= D3DCOMPILE_DEBUG;
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif 

	result = D3DCompileFromFile
	(
		path,
		NULL,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"ps_5_0",
		dwShaderFlags,
		0,
		&pixelShaderBuffer,
		NULL
	);

	//�����ϸ� ����..
	if (FAILED(result))
	{
		return false;
	}

	//��Ŀ�� ����
	ID3D11ClassLinkage* g_pPsClassLinkage = nullptr;
	mDevice->CreateClassLinkage(&g_pPsClassLinkage);


	// ���ۿ��� �ȼ� ���̴��� �����մϴ�.
	result = mDevice->CreatePixelShader
	(
		pixelShaderBuffer->GetBufferPointer(),
		pixelShaderBuffer->GetBufferSize(),
		g_pPsClassLinkage,
		&m_pixelShader
	);


	HR(D3DReflect(pixelShaderBuffer->GetBufferPointer(),pixelShaderBuffer->GetBufferSize(),
		IID_ID3D11ShaderReflection,(void**)&ReFlector));


	g_pPsClassLinkage->Release();
	//�����ϸ� ����..
	if (FAILED(result))
	{
		return false;
	}
	else
	{
		ShaderList[ShaderName].PixelShader = m_pixelShader;
		return true;
	}
}
