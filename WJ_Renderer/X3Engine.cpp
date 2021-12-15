//#include <wrl/client.h>
#include "OneCompile.h"
#include "EngineData.h"
#include "Effects.h"
#include "InputLayout.h"
#include "WICTextureLoader.h"
#include "XVertex.h"
#include "DirectXDefine.h"
#include "DirectXDevice.h"
#include "DirectXDeviceContext.h"
#include "DirectXSwapChain.h"
#include "DirectXRasterizerState.h"
#include "DirectXAdapter.h"
#include "DirectXRenderTargeter.h"
#include "DirectXSamplerState.h"
#include "../DirectX2DSupporter/Grahpics2D.h"
#include "ParserData.h"
#include "ResourcesData.h"
#include "CBox.h"
#include "../Physics/Collider.h"
#include "../Physics/BoxCollider.h"
#include "../Physics/SphereCollider.h"
#include "../EditorLib/ColliderExporter.h"
#include "X3Engine.h"

//스마트포인터 인클르드

/*
	
*/
// 초기화 부분.
X3Engine::X3Engine() : 
	m_pDevice(nullptr), 
	m_pDeviceContext(nullptr) , 
	m_ArrColor{ 0.5f, 0.5f, 0.35f, 1.0f },
	m_XVertexShader{},
	m_XPexelShader{},
	m_pVertexBuffer(nullptr),
	m_CBox(nullptr)
	//mWorld{},
	//mView{},
	//mProj{},
	//m_FX(nullptr),
	//mTech(nullptr),
	//mfxWorldViewProj(nullptr),
	//mInputLayout(nullptr),
	//NormalDSS(nullptr)
{

	//생성 부분
	m_pDevice = new DirectXDevice();
	m_pDeviceContext = new DirectXDeviceContext();
	m_pSamplerState = new DirectXSamplerState();
	
	m_pRasterizerState = new DirectXRasterizerState();
	m_pRasterizerSolid = new DirectXRasterizerState();
	m_pRasterizerWire = new DirectXRasterizerState();
	m_pAdapter = new DirectXAdapter();
	m_pRenderTargeter = new DirectXRenderTargeter();
	m_CBox = new CBox();
	m_BoxCollider = new BoxCollider();
	//m_SphereCollider = new SphereCollider();
	m_ColliderExporter = new ColliderExporter();

	this->m_pDirectXSwapChain = new DirectXSwapChain(m_pDevice->GetDevice());

	m_ColliderExporter->PushInfo(m_BoxCollider);
}

X3Engine::~X3Engine()
{

}

void X3Engine::Initialize(HWND _hWnd, int _iWidth, int _iHeight)
{

	///이제는 쓰이지 않는다.
#pragma region 이제는 쓰이지 않는다
	m_hWnd = _hWnd;
	m_pDevice->CreateSize(_iWidth, _iHeight);
		//백버퍼를 반환하여 팩토리를 초기화합니다.
	ID3D11Texture2D* backBufferPtr = m_pDevice->CreateInitFactory(m_videoCardMemory);
	//스왑체인을 초기화 해줍니다.
	DXGI_SWAP_CHAIN_DESC swapChainDesc(m_pDevice->CreateInitSwapChain(m_hWnd));

	// Set the feature level to DirectX 11.
	// 형상 레벨을 DirectX 11로 설정
	// 스왑체인을 만들어 줍니다.
	m_pDirectXSwapChain->MakeASwapChain(m_pDevice->GetDevice(), m_pDeviceContext->GetDeviceContext(), swapChainDesc);

	///뎁스 = (깊이)

	//렌더 타겟을 만들어줍니다.
	m_pRenderTargeter->Create(m_pDevice->GetDevice(), m_pDirectXSwapChain->GetSwapChain());
	//디바이스에 뎁스버퍼를 만들어줍니다.
	m_pDevice->CreateDepthBuffer(m_pDepthStencil_Buffer);
	m_pDevice->CreateDepthStencilState(m_pDeviceContext->GetDeviceContext(), m_pDepthStencil_State);
	//뎁스스텐실 뷰를 위한 조건들을 넣어줍니다.
	m_pDevice->CreateDepthStencilView
	(
		m_pDeviceContext->GetDeviceContext(),
		m_pDepthStencil_View,
		m_pDepthStencil_Buffer,
		m_pRenderTargeter->m_pRenderTarget
	);
	//레스터라이저를 만들어줍니다.
	m_pDevice->CreateResterize(m_pDeviceContext->GetDeviceContext(), m_pRasterizerState->GetFrameRS());
	//뷰포트를 만들어줍니다.

	(m_ViewPort) = m_pDevice->CreateViewPort(m_pDeviceContext->GetDeviceContext());
	//샘플러 스테이트를 만들어줍니다.
	m_pSamplerState->CreateDXSamplerState(m_pDevice->GetDevice());

	///


	// Render State
	CreateRenderState();

	// 어댑터 정보를 얻는다.
	m_pAdapter->GetAdapter();

	m_pAdapter->GetAdapterInfo();



	if (nullptr == m_pDirectXSwapChain->GetSwapChain())
	{

	}
	
	InitializeShaders();
#pragma endregion 이제안씀.

}

Indexbuffer* X3Engine::CreateIndexBuffer(ParserData::Mesh* mModel)
{
	ID3D11Buffer* mIB = nullptr;
	Indexbuffer* indexbuffer = new Indexbuffer();

	//모델의 계수
	size_t ModelCount = (int)mModel->m_IndexList.size();
	size_t Icount = (int)mModel->m_IndexList.size();

	std::vector<UINT> index;
	index.resize(Icount * 3);

	int j = 0;
	for (int i = 0; i < Icount; i++)
	{
		index[j] = mModel->m_IndexList[i]->m_Index[0];
		j++;
		index[j] = mModel->m_IndexList[i]->m_Index[1];
		j++;
		index[j] = mModel->m_IndexList[i]->m_Index[2];
		j++;
	}


	//인덱스 버퍼를 생성한다
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * (UINT)index.size();
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &index[0];
	m_pDevice->GetDevice()->CreateBuffer(&ibd, &iinitData, &mIB);

	//인덱스버퍼를 보낼수있도록 변경
	indexbuffer->IndexBufferPointer = mIB;
	//indexbuffer->size = sizeof(ID3D11Buffer);

	return indexbuffer;
}

Vertexbuffer* X3Engine::CreateVertexBuffer(ParserData::Mesh* mModel)
{
	ID3D11Buffer* mVB = nullptr;
	Vertexbuffer* vertexbuffer = new Vertexbuffer();

	//모델의 계수
	size_t Vcount = mModel->m_VertexList.size();

	std::vector<XVertexDef> temp;
	temp.resize(Vcount);
	for (int i = 0; i < Vcount; i++)
	{
		temp[i].Pos = mModel->m_VertexList[i]->m_Pos;
		temp[i].Nomal = mModel->m_VertexList[i]->m_Normal;
		temp[i].Tex =  mModel->m_VertexList[i]->m_UV;
		temp[i].Tangent = mModel->m_VertexList[i]->m_Tanget;
	}



	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(XVertexDef) * (UINT)Vcount;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &temp[0];
	m_pDevice->GetDevice()->CreateBuffer(&vbd, &vinitData, &mVB);


	vertexbuffer->VertexbufferPointer = mVB;
	//vertexbuffer->size = sizeof(ID3D11Buffer);

	return vertexbuffer;
}

TextureBuffer* X3Engine::CreateTextureBuffer(std::string path)
{
	// string to wstring
	std::wstring W_Path;
	W_Path.assign(path.begin(), path.end());

	TextureBuffer* _TextureBuffer = new TextureBuffer();

	// 텍스쳐 생성을 위한 임시 객체
	ID3D11Resource* Texture_Resource = nullptr;
	// 텍스쳐 SRV
	ID3D11ShaderResourceView* DX11_SRV = nullptr;
	// 텍스쳐 정보 셋팅.
	DirectX::CreateWICTextureFromFile(m_pDevice->GetDevice(), W_Path.c_str(), &Texture_Resource, &DX11_SRV);
	ReleaseCOM(Texture_Resource);

	_TextureBuffer->TextureBufferPointer = _TextureBuffer;

	return _TextureBuffer;
}



void X3Engine::OnReSize(int Change_Width, int Change_Height)
{
}

void X3Engine::Delete()
{
}

void X3Engine::Render(std::queue<MeshData*>* meshList, GlobalData* global)
{
	if (GetAsyncKeyState(VK_RETURN) & 8001)
	{
		//
		m_ColliderExporter->Export();
	}
	//렌더링시작의 순서.
	//나중에 렌더 큐? 같은걸로 해보자,
	m_pDeviceContext->GetDeviceContext()->RSSetViewports(1, &this->m_ViewPort);

	mView = DirectX::SimpleMath::Matrix(*global->mViewMX);
	mProj = DirectX::SimpleMath::Matrix(*global->mProj);

	//m_pViewGrid->Update(&mView, &mProj);

	m_CBox->Update(mView, mProj);
	m_CBox->Render(meshList);

	//m_BoxCollider->Update();
	////const DirectX::XMFLOAT4X4 _WorldTM = {  };
	DirectX::XMMATRIX r = XMMatrixIdentity();
	m_BoxCollider->Translasion(&r);
	m_BoxCollider->Draw(mView, mProj);
	m_BoxCollider->Rnder();
	//
	////m_SphereCollider->Translasion(&r);
	//m_SphereCollider->Draw(mView, mProj);
	//m_SphereCollider->Rnder();

	//m_BoxCol->Update(mView, mProj);
	//m_BoxCol->Render(meshList);
	

	///2D렌더링 처리
	



}

void X3Engine::SetViewPort(void* VPT, int Change_Width, int Change_Height)
{
	(this->m_ViewPort) = *(D3D11_VIEWPORT*)VPT;
}

void X3Engine::SetDevice(void* Devie, void* DevieContext)
{
	m_pDevice->SetDevice(reinterpret_cast<ID3D11Device*>(Devie));
	m_pDeviceContext->SetDeviceContext(reinterpret_cast<ID3D11DeviceContext*>(DevieContext));

	//렌더스테이트를 생성한다.
	this->CreateRenderState();
	
	Effects::InitAll(m_pDevice->GetDevice());
	InputLayouts::InitAll(m_pDevice->GetDevice());

	m_CBox->Initialize(m_pDevice->GetDevice(), m_pDeviceContext->GetDeviceContext());
	m_BoxCollider->Initialize(m_pDevice->GetDevice(), m_pDeviceContext->GetDeviceContext());
	//m_SphereCollider->Initialize(m_pDevice->GetDevice(), m_pDeviceContext->GetDeviceContext());

}

void X3Engine::CreateRenderState()
{
	this->m_pRasterizerSolid->Create(this->m_pDevice->GetDevice(), StateRS::eSolid);
	this->m_pRasterizerWire->Create(this->m_pDevice->GetDevice(), StateRS::eWireFrame);
}

void X3Engine::DrawSystemStatus()
{
	// 피쳐레벨

}

void X3Engine::SetTextureSRV(SharedRenderData* _SRD)
{

}

void X3Engine::Release()
{

}

void X3Engine::InitializeShaders()
{
	std::wstring shaderFoler;


#pragma region DetermineShaderPath

#ifdef _DEBUG //Debug
#ifdef _WIN64 //x64
	shaderFoler = L"../x64/Debug/";
#else		  //x86
	shaderFoler = L"../Debug/";
#endif // _WIN64
#else	//Release
#ifdef _WIN64 //x64
	shaderFoler = L"../x64/Release/";
#else
	shaderFoler = L"../Release/";
#endif // _WIN64 //x64

#endif // _DEBUG

#pragma endregion

	/// ============================ 쉐이더의 초기화 부분 ===================================== //

	//현재 이 코드(hlsl 쉐이더 초기화 함수)는 사용하지 않는다.
	/*
	// Color Shader

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0,DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,0,0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,0 } ,
		{ "COLOR",		0,DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,0 } ,
	};
	*/
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0,DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,0,0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,0 } ,
		{ "TEXCOORD",	0,DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,0 } ,
	};

	
	//UINT numElements = ARRAYSIZE(layout, numElements);
	UINT numElements = ARRAYSIZE(layout);

	if (0 != m_XVertexShader.Initialize(m_pDevice->GetDevice(), shaderFoler + L"vertexShaders.cso", layout, numElements))
	{
		return;
	}
	if (0 != m_XPexelShader.Initialize(m_pDevice->GetDevice(), shaderFoler + L"pixelShaders.cso", layout, numElements))
	{
		return;
	}
}


HRESULT X3Engine::BeginRender()
{
	HRESULT hr = S_OK;

	
	return hr;
}

HRESULT X3Engine::LoopRender()
{
	HRESULT hr = S_OK;

	return hr;
}

HRESULT X3Engine::EndRender()
{
	HRESULT hr = S_OK;
	//m_pGrahpics2D->Draw_AllText();
	//m_pGrahpics2D->Draw_AllImage();
	//m_pGrahpics2D->Draw_AllSprite();

	return hr;
}


