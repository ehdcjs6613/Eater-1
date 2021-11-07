#include "GraphicsEngine.h"
#include "HsGraphic.h"
#include "HsEngineHelper.h"
#include "ParserData.h"
#include "EngineData.h"
#include "ShaderManager.h"
#include "RenderingManager.h"
#include "BufferData.h"
#include "InputLayout.h"
#include "HsDefine.h"
#include "TextureBase.h"
#include <vector>
#include "Data.h"

using namespace DirectX;

HsGraphic::HsGraphic()
{
	hwnd = 0;
	Device				= nullptr;
	DeviceContext		= nullptr;
	mRenderTargetView	= nullptr;
	mDepthStencilView	= nullptr;
	mScreenViewport		= D3D11_VIEWPORT();
	mSwapChain			= nullptr;


	//윈도우 사이즈
	WinSizeX = 0;
	WinSizeY = 0;

	mWireframe	= nullptr;
	mSolid		= nullptr;
}

HsGraphic::~HsGraphic()
{
	
}

void HsGraphic::Initialize(HWND _hWnd, int screenWidth, int screenHeight)
{
	hwnd = _hWnd;
	WinSizeX = screenWidth;
	WinSizeY = screenHeight;

	//엔진 디바이스를 생성
	CreateDevice();

	//랜더타겟과 상태를 생성
	CreateRenderTarget();
	CreateRenderState();

	//매니저들 생성
	mShaderManager = new ShaderManager();		//쉐이더를 가져오고 저장하는 클래스
	mRenderManager = new RenderingManager();	//랜더링을 해주는 클래스
	
	mShaderManager->Initialize(Device, DeviceContext);
}

Indexbuffer* HsGraphic::CreateIndexBuffer(ParserData::Mesh* mModel)
{

	ID3D11Buffer* mIB = nullptr;
	Indexbuffer* indexbuffer = new Indexbuffer();

	//모델의 계수
	int ModelCount = (int)mModel->m_IndexList.size();
	int Icount =  (int)mModel->m_IndexList.size();

	std::vector<UINT> index;
	index.resize(Icount * 3);

	int j = 0;
	for (int i = 0 ;i < Icount; i++)
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
	ibd.ByteWidth = sizeof(UINT) * index.size();
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &index[0];
	Device->CreateBuffer(&ibd, &iinitData, &mIB);

	//인덱스버퍼를 보낼수있도록 변경
	indexbuffer->IndexBufferPointer = mIB;
	indexbuffer->size = sizeof(ID3D11Buffer);

	return indexbuffer;
}

Vertexbuffer* HsGraphic::CreateVertexBuffer(ParserData::Mesh* mModel)
{
	ID3D11Buffer* mVB = nullptr;
	Vertexbuffer* vertexbuffer = new Vertexbuffer();

	

	//모델의 계수
	int Vcount = mModel->m_VertexList.size();
	mModel->m_VertexList;
	

	std::vector<Deferred32> temp;
	temp.resize(Vcount);
	for (int i = 0; i < Vcount; i++)
	{
		temp[i].Pos			= mModel->m_VertexList[i]->m_Pos;
		temp[i].Nomal		= mModel->m_VertexList[i]->m_Normal;
		temp[i].Tex			={ mModel->m_VertexList[i]->m_U ,mModel->m_VertexList[i]->m_V};
		temp[i].Tangent		= mModel->m_VertexList[i]->m_Tanget;
	}



	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Deferred32) * Vcount;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &temp[0];
	Device->CreateBuffer(&vbd, &vinitData, &mVB);
	

	vertexbuffer->VertexbufferPointer = mVB;
	vertexbuffer->size = sizeof(ID3D11Buffer);

	return vertexbuffer;
}

ID3D11RenderTargetView* HsGraphic::GetEngineRTV()
{
	return mRenderTargetView;
}

ID3D11DepthStencilView* HsGraphic::GetEngineDSV()
{
	return mDepthStencilView;
}

void HsGraphic::CreateRenderTarget()
{
	//D3D에 연결된 랜더타겟과 뎁스스텐실 을 생성한다
	
	ID3D11Texture2D* backBuffer;
	mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
	Device->CreateRenderTargetView(backBuffer, 0, &mRenderTargetView);
	backBuffer->Release();

	ID3D11Texture2D* mDepthStencilBuffer = nullptr;
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = WinSizeX;						//텍스쳐의 너비 (텍셀단위) 텍셀??
	depthStencilDesc.Height = WinSizeY;						//텍스쳐의 높이 (텍셀단위) 텍셀??
	depthStencilDesc.MipLevels = 1;							//밉맵수준의 개수
	depthStencilDesc.ArraySize = 1;							//택스처 배열의 텍스처 개수*깊이*스텐실 버퍼의 경우 텍스처 하나만필요

	//텍셀의 형식을 뜻하는 필드로 DXGI_FORMAT 열거형의 값들 중 하나를 지정한다
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;					//SampleDesc = 다중표본 개수와 품질수듄을 서술하는 구조체
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;			//텍스처의 용도를 뜻하는 필드
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;	//자원을 파이프라인에 어떤식으로 묶을것인지
	depthStencilDesc.CPUAccessFlags = 0;					//CPU가 자원을 접근하는 방식을 결정하는 플래그를 지정
	depthStencilDesc.MiscFlags = 0;


	Device->CreateTexture2D(&depthStencilDesc, 0, &mDepthStencilBuffer);
	Device->CreateDepthStencilView(mDepthStencilBuffer, 0, &mDepthStencilView);
	DeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);

	//ViewPort
	mScreenViewport.TopLeftX = 0;
	mScreenViewport.TopLeftY = 0;
	mScreenViewport.Width = static_cast<float>(WinSizeX);
	mScreenViewport.Height = static_cast<float>(WinSizeY);
	mScreenViewport.MinDepth = 0.0f;
	mScreenViewport.MaxDepth = 1.0f;

	DeviceContext->RSSetViewports(1, &mScreenViewport);
}

void HsGraphic::CreateRenderState()
{
	//각종 상태를 생성해준다

	D3D11_RASTERIZER_DESC solidDesc;
	ZeroMemory(&solidDesc, sizeof(D3D11_RASTERIZER_DESC));
	solidDesc.FillMode = D3D11_FILL_SOLID;
	solidDesc.CullMode = D3D11_CULL_BACK;
	solidDesc.FrontCounterClockwise = false;
	solidDesc.DepthClipEnable = true;

	Device->CreateRasterizerState(&solidDesc, &mSolid);


	D3D11_RASTERIZER_DESC wireframeDesc;
	ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
	wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
	wireframeDesc.CullMode = D3D11_CULL_BACK;
	wireframeDesc.FrontCounterClockwise = false;
	wireframeDesc.DepthClipEnable = true;

	Device->CreateRasterizerState(&wireframeDesc, &mWireframe);
}

void HsGraphic::CreateDevice()
{
	UINT createDeviceFlags = 0;
	D3D_FEATURE_LEVEL featureLevel;

	HRESULT hr = D3D11CreateDevice
	(
		0,							//디스플레이 어뎁터  0 = 디폴트 
		D3D_DRIVER_TYPE_HARDWARE,	// ???
		0,							// 소프트웨어 구동기 지정
		createDeviceFlags,			// ???
		0,							// 점검순서
		0,							// ???
		D3D11_SDK_VERSION,			//항상 D3D11_SDK_VERSION 을 지정
		&Device,					//함수가 생성한장치 돌려줌
		&featureLevel,				//null 값으로 한경우 지원하는 가장 높은 기능수준으로
		&DeviceContext			//원래값 돌려줌
	);

	//생성 여부
	if (FAILED(hr))
	{
		return;
	}

	//버전확인
	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		//MessageBox(0, L"Direct3D LEVEL 11", 0, MB_OK);
		return;
	}


	//4xMSAA 품질 수준 지원 점검??
	//하드웨어가 4xMSAA를 위한 품질 수준을 지원하는지 점검

	UINT m4xMsaaQuality;
	Device->CheckMultisampleQualityLevels
	(
		DXGI_FORMAT_R8G8_B8G8_UNORM,
		4,
		&m4xMsaaQuality
	);

	//assert를 몰라서 써놓음
	//assert는 조건이 맞지않을때 프로그램을 중단하며 참일때는 계속 실행시킴
	//assert(m4xMsaaQuality > 0);

	//교환 사슬 설정?
	//구조체 값 설정
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	//BufferDesc = 생성하고자 하는 후면 버퍼의 속성들을 서술하는 개별적인 구조체

	sd.BufferCount = 1;  //교환 사슬에서 사용할 후면 버퍼의 개수
	sd.BufferDesc.Width = WinSizeX;
	sd.BufferDesc.Height = WinSizeY;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //버퍼의 용도
	sd.OutputWindow = hwnd; //랜더링 결과를 표시할 창의 핸들

	//sampleDesc = 다중 표본화를 이해 추출할 표본 개수와 품질수준
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;	//
	sd.Windowed = true;			//윈도우 창모드를 원하면 true 전체모드 false

	//교환 사슬의 생성

	//이과정에서 오류를 피하려면 장치의 생성에 쓰인 IDXGIFactory 인스턴스를 사용해야한다
	//그리고 그 인스턴스를 얻으려면 다음과 같이 일련의 COM 질의 과정을 거쳐야함..
	IDXGIDevice* dxgiDevice = 0;
	Device->QueryInterface
	(
		__uuidof(IDXGIDevice),
		(void**)&dxgiDevice
	);


	IDXGIAdapter* dxgiAdapter = 0;
	dxgiDevice->GetParent
	(
		__uuidof(IDXGIAdapter),
		(void**)&dxgiAdapter
	);

	//IDXGIFactory 인터페이스 얻음
	IDXGIFactory* dxgiFactory = 0;
	dxgiAdapter->GetParent
	(
		__uuidof(IDXGIFactory),
		(void**)&dxgiFactory
	);

	//사슬 교환 생성
	dxgiFactory->CreateSwapChain(Device, &sd, &mSwapChain);

	//필요없는건 삭제
	dxgiAdapter->Release();
	dxgiDevice->Release();
	dxgiFactory->Release();
}

void HsGraphic::BeginRender()
{
	//엔진 랜더링 시작
	float DeepDarkGray[4] = { 1.0f, 1.0f, 0.0f, 1.0f };
	DeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
	DeviceContext->ClearRenderTargetView(mRenderTargetView, DeepDarkGray);
	DeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	DeviceContext->RSSetViewports(1, &mScreenViewport);
}

void HsGraphic::EngineRender()
{
	


}

void HsGraphic::EndRender()
{
	//엔진 랜더링 종료
	mSwapChain->Present(0, 0);
}

int HsGraphic::GetAspectRatio()
{
	int width = WinSizeX;
	int Height = WinSizeY;
	int Ratio = width / Height;
	return  Ratio;
}

TextureBuffer* HsGraphic::CreateTextureBuffer(std::string path)
{
	ID3D11ShaderResourceView* Textures = nullptr;
	ID3D11Resource* texResource = nullptr;


	std::wstring _path = std::wstring(path.begin(), path.end());
	const wchar_t* w_path = _path.c_str();

	if (CreateDDSTextureFromFile(Device, w_path, &texResource, &Textures, 0))
	{
		return nullptr;
	}
	
	TextureBuffer* buffer = new TextureBuffer();
	buffer->TextureBufferPointer = Textures;
	buffer->size = sizeof(ID3D11ShaderResourceView);	
	texResource->Release();

	return buffer;
}

void HsGraphic::OnReSize(int Change_Width, int Change_Height)
{
	WinSizeX = Change_Width;
	WinSizeY = Change_Height;

	assert(DeviceContext);
	assert(Device);
	assert(mSwapChain);

	//랜더타겟 삭제
	if (mRenderTargetView != nullptr)
	{
		mRenderTargetView->Release();
		mRenderTargetView = nullptr;
	}

	//뎁스스텐실 삭제
	if (mDepthStencilView != nullptr)
	{
		mDepthStencilView->Release();	
		mDepthStencilView = nullptr;
	}


	//스왑체인 재설정
	mSwapChain->ResizeBuffers(1, WinSizeX, WinSizeY, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

	//뎁스스텐실 랜더타겟 재생성
	CreateRenderTarget();

	//재설정
	DeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
	DeviceContext->RSSetViewports(1, &mScreenViewport);
}

void HsGraphic::Render(std::queue<MeshData*>* meshList, GlobalData* global)
{
	BeginRender();


	while (meshList->size() != 0)
	{
		UINT stride = sizeof(Deferred32);
		UINT offset = 0;
		MeshData* Mesh = meshList->front();
		
		if (Mesh->ObjType == OBJECT_TYPE::Camera)
		{
			//카메라 상수버퍼 값 대입
			ID3D11Buffer* buffer = mShaderManager->GetConstantBuffer("CameraBuffer");
			CameraBuffer temp;
			temp.view = XMMatrixTranspose(*global->mViewMX);
			temp.proj = XMMatrixTranspose(*global->mProj);

			DeviceContext->UpdateSubresource(buffer, 0, nullptr, &temp, 0, 0);
			DeviceContext->VSSetConstantBuffers(0, 1, &buffer);
			DeviceContext->PSSetConstantBuffers(0, 1, &buffer);
			meshList->pop();
			continue;
		}
		

		//매쉬 데이터 삽입
		ID3D11Buffer* buffer = mShaderManager->GetConstantBuffer("ObjectBuffer");
		ObjectBuffer temp;
		temp.world = XMMatrixTranspose(Mesh->mWorld);

		DeviceContext->UpdateSubresource(buffer, 0, nullptr, &temp, 0, 0);
		DeviceContext->VSSetConstantBuffers(1, 1, &buffer);
		DeviceContext->PSSetConstantBuffers(1, 1, &buffer);




		if (Mesh->IB == nullptr && Mesh->VB == nullptr)
		{
			meshList->pop();
			continue;
		}

		ID3D11Buffer* IBuffer = reinterpret_cast<ID3D11Buffer*>(Mesh->IB->IndexBufferPointer);
		ID3D11Buffer* VBuffer = reinterpret_cast<ID3D11Buffer*>(Mesh->VB->VertexbufferPointer);

		//버텍스버퍼 인덱스버퍼 넣기
		DeviceContext->IASetVertexBuffers(0, 1, &VBuffer, &stride, &offset);
		DeviceContext->IASetIndexBuffer(IBuffer, DXGI_FORMAT_R32_UINT, 0);

		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DeviceContext->RSSetState(mWireframe);

		//ps,vs쉐이더,Layout 데이터 가져오기
		ShaderData Sdata = mShaderManager->GetShader("texture");
		ID3D11SamplerState* SamplerData = mShaderManager->GetSampler("Basic");


		//데이터 넣기
		DeviceContext->IASetInputLayout(Sdata.Layout);
		DeviceContext->VSSetShader(Sdata.VertexShader, NULL, 0);
		DeviceContext->PSSetShader(Sdata.PixelShader, NULL, 0);


		DeviceContext->PSSetSamplers(0, 1, &SamplerData);
		DeviceContext->PSSetSamplers(0, 1, &SamplerData);


		DeviceContext->DrawIndexed(Mesh->indexCount, 0, 0);

		meshList->pop();
	}

	

	EndRender();
}

void HsGraphic::Delete()
{
	mWireframe->Release();
	mSolid->Release();

	//
	//mRenderManager;
}


