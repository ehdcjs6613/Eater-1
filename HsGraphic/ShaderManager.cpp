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

	//버텍스 쉐이더를 로드한다 (인풋 레이아웃도 여기서)
	if (LoadVertexShader(vsFileName, ShaderName) == false)
	{
		//실패한다면
	}

	//픽셀 쉐이더를 로드한다
	if (LoadPixelShader(psFileName, ShaderName) == false)
	{
		//실패한다면
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
	//쉐디어 정보 가져오기
	D3D11_SHADER_DESC desc;
	HR(ReFlector->GetDesc(&desc));

	//쉐이더 레이아웃 개수를 가져옴
	UINT inputLayCount = desc.InputParameters;

	//레이아웃 개수만큼 배열사이즈를 잡아줌
	std::vector<D3D11_INPUT_ELEMENT_DESC> DescList;
	DescList.resize((int)inputLayCount);

	//처음 들어가는곳은 0번쨰부터 들어가기때문에
	int TypeSize = 0;

	for (int i = 0; i < inputLayCount; i++)
	{
		//한개의 레이아웃 구조체를 생성함
		D3D11_SIGNATURE_PARAMETER_DESC desc;
		ReFlector->GetInputParameterDesc(i, &desc);

		BYTE numberMask = desc.Mask;
		int number = (int)desc.ComponentType;
		DXGI_FORMAT FormatNumver = FindFormat(number, numberMask, desc);


		//한개의 레이아웃 구조체값 넣기
		DescList[i].SemanticName			= desc.SemanticName;
		DescList[i].SemanticIndex			= 0;
		DescList[i].Format					= FormatNumver;
		DescList[i].InputSlot				= 0;
		DescList[i].AlignedByteOffset		= TypeSize;
		DescList[i].InputSlotClass			= D3D11_INPUT_PER_VERTEX_DATA;
		DescList[i].InstanceDataStepRate	= 0;

		//한개가 완성이 되었고 자료형의 끝을 알려줘야 다음놈이 그다음으로 들어오기때문에
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
	
	//레이아웃 구조체의 값은 다넣었고 생성해준다
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

	//실패여부를 확인
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

	//string 형을 LPCTSTR형으로 바꿔줌
	std::string temp = "";
	temp += ShaderPath;
	temp += vsFileName;
	CString lpctpath = temp.c_str();
	LPCTSTR path = lpctpath;

	//플래그 설정
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef DEBUG
	dwShaderFlags |= D3DCOMPILE_DEBUG;
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif 

	//버택스 쉐이더를 로드 한다
	result = D3DCompileFromFile
	(
		path,								//쉐이더 코드가 들어있는 파일이름
		NULL,								//쉐이더 매크로를 정의 사용하지않으면 NULL
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	//기본포함 핸들러에 대한 포인터 (기본값 NULL)
		"main",								//쉐이더 실행이 시작되는 쉐이더 진입점 함수의 이름
		"vs_5_0",							//컴파일할 쉐이더 대상 버전
		dwShaderFlags,						//컴파일 쉐이더 플레그 1
		0,									//컴파일 쉐이더 플레그 2
		&_vertexShaderBuffer,				//반환값
		NULL								//에러메세지 반환값
	);
	//실패하면 리턴..
	if (FAILED(result))
	{
		return false;
	}


	//링커를 생성
	ID3D11ClassLinkage* g_pPsClassLinkage = nullptr;
	mDevice->CreateClassLinkage(&g_pPsClassLinkage);


	//버퍼로 부터 정점 쉐이더를 생성한다
	result = mDevice->CreateVertexShader
	(
		_vertexShaderBuffer->GetBufferPointer(), //컴파일된 쉐이더의 대한 포인터
		_vertexShaderBuffer->GetBufferSize(),	//컴파일된 정점쉐이더의 크기
		g_pPsClassLinkage,						//클래스 링크 인터페이스에 대한 포인터
		&m_vertexShader							//ID3D11VertexShader 인터페이스에 대한 포인터 주소
	);


	//실패하면 리턴..
	if (FAILED(result))
	{
		ShaderList[ShaderName].VertexShader = nullptr;
		return false;
	}
	else
	{
		//버텍스 쉐이더를 넣어준다
		ShaderList[ShaderName].VertexShader = m_vertexShader;
	}

	//쉐이더 리플렉션을 위한 준비
	HR(D3DReflect(_vertexShaderBuffer->GetBufferPointer(),_vertexShaderBuffer->GetBufferSize(),
		IID_ID3D11ShaderReflection,(void**)&ReFlector));



	
	//인풋레이아웃을 생성한다
	if (CreateInputLayout(ShaderName, _vertexShaderBuffer) == false)
	{
		return false;
	}



	//상수버퍼를 생성한다 이미 있는 버퍼라면 생성하지않음..
	//CreateConstantBuffer();

	//샘플러를 생성한다 이미있는 샘플러라면 생성하지않는다
//	CreateSamPler(ShaderName);

	//파일을 모두 읽었으니 삭제
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

	//플래그 설정
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

	//실패하면 리턴..
	if (FAILED(result))
	{
		return false;
	}

	//링커를 생성
	ID3D11ClassLinkage* g_pPsClassLinkage = nullptr;
	mDevice->CreateClassLinkage(&g_pPsClassLinkage);


	// 버퍼에서 픽셀 쉐이더를 생성합니다.
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
	//실패하면 리턴..
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
