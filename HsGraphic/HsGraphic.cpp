#include "Grahpics2D.h"
#include "GraphicsEngine.h"
#include "HsGraphic.h"
#include "HsEngineHelper.h"
#include "ParserData.h"
#include "EngineData.h"
//#include "ShaderManager.h"
//#include "RenderingManager.h"
#include "DirectXDefine.h"
#include "Grahpics2D.h"
#include "HsDefine.h"
#include "Data.h"
#include <vector>

using namespace DirectX;

HsGraphic::HsGraphic()
{
	hwnd = 0;

	Device			= nullptr;
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

	
	m_p2DSupport = new Grahpics2D();
	m_p2DSupport->initialize(hwnd, mSwapChain);

	m_p2DSupport->LoadBitMap(L"../Image/apple_1.png",L"../Image/apple_1.png");
	m_p2DSupport->LoadBitMap(L"../Image/atk_1.png",L"../Image/atk_1.png");
	//매니저들 생성
;	//mShaderManager = new ShaderManager();
	//mRenderManager = new RenderingManager();
	//
	//mShaderManager->Initialize(Device, DeviceContext);
}

Indexbuffer* HsGraphic::CreateIndexBuffer(ParserData::Model* mModel)
{

	ID3D11Buffer* mIB = nullptr;
	Indexbuffer* indexbuffer = new Indexbuffer();

	//모델의 계수
	int ModelCount = (int)mModel->m_MeshList.size();
	int Icount =  (int)mModel->m_MeshList[0]->m_IndexList.size();
	std::vector<ParserData::IndexList*> IndexList = mModel->m_MeshList[0]->m_IndexList;


	//인덱스 버퍼를 생성한다
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * Icount;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &IndexList[0];
	//HR(Device->CreateBuffer(&ibd, &iinitData, &mIB));

	//인덱스버퍼를 보낼수있도록 변경
	indexbuffer->IndexBufferPointer = mIB;
	indexbuffer->size = sizeof(ID3D11Buffer);

	return indexbuffer;
}

Vertexbuffer* HsGraphic::CreateVertexBuffer(ParserData::Model* mModel)
{
	ID3D11Buffer* mVB = nullptr;
	Vertexbuffer* vertexbuffer = new Vertexbuffer();

	//모델의 계수
	int ModelCount = (int)mModel->m_MeshList.size();
	int Vcount = (int)mModel->m_MeshList[0]->m_VertexList.size();
	std::vector<ParserData::Vertex*> VertexList = mModel->m_MeshList[0]->m_VertexList;
	

	std::vector<Deferred32> temp;
	temp.resize(Vcount);
	for (int i = 0; i < Vcount; i++)
	{
		temp[i].Pos			= VertexList[i]->m_Pos;
		temp[i].Nomal		= VertexList[i]->m_Normal;
		temp[i].Tex			={ VertexList[i]->m_U ,VertexList[i]->m_V};
		temp[i].Tangent		= VertexList[i]->m_Tanget;
	}



	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Deferred32) * Vcount;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &temp[0];
	//HR(Device->CreateBuffer(&vbd, &vinitData, &mVB));
	

	vertexbuffer->VertexbufferPointer = mVB;
	vertexbuffer->size = sizeof(ID3D11Buffer);

	return vertexbuffer;
}

void HsGraphic::CreateRenderTarget()
{
	//D3D에 연결된 랜더타겟과 뎁스스텐실 을 생성한다

	ID3D11Texture2D* backBuffer;
	mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
	if (nullptr == backBuffer) { return; }
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
	if (nullptr == mDepthStencilBuffer) { return; }
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

	//HR(Device->CreateRasterizerState(&solidDesc, &mSolid));


	D3D11_RASTERIZER_DESC wireframeDesc;
	ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
	wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
	wireframeDesc.CullMode = D3D11_CULL_BACK;
	wireframeDesc.FrontCounterClockwise = false;
	wireframeDesc.DepthClipEnable = true;

	//HR(Device->CreateRasterizerState(&wireframeDesc, &mWireframe));
}

void HsGraphic::CreateDevice()
{
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	unsigned int numModes, i, numerator, denominator;
	unsigned long long stringLength;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	int error;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ID3D11Texture2D* backBufferPtr;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_RASTERIZER_DESC rasterDesc;

	D3D11_VIEWPORT viewport;
	float fieldOfView, screenAspect;
	// DXGI 팩토리 생성.

	HRESULT hr = S_OK;
	hr = (CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory));

	// Use the factory to create an adapter for the primary graphics interface (video card).
	//팩토리 객체를 사용해서 에서 기본 그래픽 인터페이스용 어댑터(비디오 카드)를 만듭니다.
	hr = (factory->EnumAdapters(0, &adapter));

	// Enumerate the primary adapter output (monitor).
	// 기본 어댑터 출력(모니터)을 열거합니다.
	hr = (adapter->EnumOutputs(0, &adapterOutput));

	// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
	//어댑터 출력(모니터)에 대한 DXGI_FORMAT_R8G8B8A8_UNORM 디스플레이 형식에 맞는 모드 수를 가져옵니다.
	hr = (adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL));

	// Create a list to hold all the possible display modes for this monitor/video card combination.
	// 이 모니터/비디오 카드 조합에 사용 가능한 모든 디스플레이 모드를 보유할 목록을 만듭니다.
	displayModeList = new DXGI_MODE_DESC[numModes];

	if (nullptr == displayModeList) { return; }

	// Now fill the display mode list structures.
	// 이제 디스플레이 목록 구조를 채웁니다.
	hr = (adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList));

	// Now go through all the display modes and find the one that matches the screen width and height.
	// When a match is found store the numerator and denominator of the refresh rate for that monitor.
	//
	// 이제 모든 디스플레이 모드를 살펴보고 화면 폭과 높이에 맞는 모드를 찾습니다.
	// 일치 항목이 발견되면 해당 모니터의 새로 고침 빈도의 분자와 분모를 저장합니다.
	for (i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == (unsigned int)WinSizeX)
		{
			if (displayModeList[i].Height == (unsigned int)WinSizeY)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}
	// Get the adapter (video card) description.
	// 어댑터(비디오 카드) 설명을 가져옵니다.
	hr = (adapter->GetDesc(&adapterDesc));

	// 비디오(그래픽)카드 메모리를 MB 단위로 바꿔준다.
	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	// Release the display mode list.
	//디스플레이 모드 목록을 해제합니다.
	delete[] displayModeList;
	displayModeList = 0;

	// Release the adapter output.
	// 어댑터(그래픽카드) 출력을 해제합니다.()
	SAFE_RELEASE(adapterOutput);

	// 어댑터를 풉니다.
	SAFE_RELEASE(adapter);

	// 팩토리객체를 해제시킵니다.
	SAFE_RELEASE(factory);

	// Initialize the swap chain description.
	// 스왑체인에 대한 설명을 초기화합니다.
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Set to a single back buffer.
	// 단일 백버퍼로 설정합니다.
	swapChainDesc.BufferCount = 1;

	// 백 버퍼의 폭과 높이를 설정합니다.
	// 
	swapChainDesc.BufferDesc.Width = WinSizeX;
	swapChainDesc.BufferDesc.Height = WinSizeY;

	// Set regular 32-bit surface for the back buffer.
	// 백 버퍼의 일반 32비트 표면을 설정합니다.
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Set the refresh rate of the back buffer.
	// 백 버퍼의 새로 고침 빈도를 설정합니다

	//// Vsync 지원
	//swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
	//swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;

	// Vsync 미지원
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	// Set the usage of the back buffer.
	//백 버퍼의 사용량을 설정합니다.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// Set the handle for the window to render to.
	// 렌더링할 창의 핸들을 설정합니다
	swapChainDesc.OutputWindow = hwnd;

	// Turn multisampling off.
	// 멀티샘플링을 끕니다.
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	/// 풀 스크린 모드.
	swapChainDesc.Windowed = true;

	// Set the scan line ordering and scaling to unspecified.
	//스캔 라인 순서 및 배율을 지정되지 않음으로 설정합니다.
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Discard the back buffer contents after presenting.
	// 백 버퍼 내용물은 프레젠테이션 후 폐기하십시오.
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Don't set the advanced flags.
	//  플래그는 세우지않는다
	swapChainDesc.Flags = false;

	// Set the feature level to DirectX 11.
	// 형상 레벨을 DirectX 11로 설정
	m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

	// 스왑 체인과 Device를 같이 생성. (D2D를 지원하기 위해 옵션으로 BGRA 를 셋팅 해 두었다.)
	D3D11CreateDeviceAndSwapChain
	(
		NULL, D3D_DRIVER_TYPE_HARDWARE,
		NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		&m_FeatureLevel, 1,
		D3D11_SDK_VERSION,
		&swapChainDesc, &mSwapChain, &Device, NULL, &DeviceContext
	);

	// Get the pointer to the back buffer.
	//포인터를 뒤쪽 버퍼로 가져갑니다.
	(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr));

	if (nullptr == backBufferPtr) { return; }

	// Create the render target view with the back buffer pointer.
	// 백 버퍼 포인터를 사용하여 렌더 대상 뷰를 작성합니다.
	Device->CreateRenderTargetView
	(
		backBufferPtr, NULL, &mRenderTargetView
	);

	// Release pointer to the back buffer as we no longer need it.
	// 더 이상 필요하지 않으므로 후면 버퍼에 대한 삭제 함수입니다.
	SAFE_RELEASE(backBufferPtr);

	// Initialize the description of the depth buffer.
	// 깊이버퍼에 대한 설명을 초기화 합니다.
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	// 깊이 버퍼에 대한 설명을 설정합니다.
	depthBufferDesc.Width = WinSizeX;
	depthBufferDesc.Height = WinSizeY;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	// Create the texture for the depth buffer using the filled out description.
	Device->CreateTexture2D(&depthBufferDesc, NULL, &mDepthStencilBuffer);

	// Initialize the description of the stencil state.
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	Device->CreateDepthStencilState(&depthStencilDesc, &mDepthStencilState);

	// Set the depth stencil state.
	DeviceContext->OMSetDepthStencilState(mDepthStencilState, 1);

	// Initialize the depth stencil view.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	if (nullptr == mDepthStencilBuffer) { return; }
	// Create the depth stencil view.
	// 뎁스스텐실 뷰를 만듭니다.
	Device->CreateDepthStencilView
	(
		mDepthStencilBuffer,
		&depthStencilViewDesc, &mDepthStencilView
	);

	/// 렌더타겟뷰, 뎁스/스탠실뷰를 파이프라인에 바인딩한다.
	DeviceContext->OMSetRenderTargets
	(
		1, &mRenderTargetView, mDepthStencilView
	);

	// Setup the raster description which will determine how and what polygons will be drawn.
	// 그릴 폴리곤과 방법을 결정하는 래스터 설명을 설정합니다.
	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	// 방금 작성한 설명에서 래스터라이저 상태를 만듭니다
	(Device->CreateRasterizerState(&rasterDesc, &mResterizer));

	// Now set the rasterizer state.
	//이제 래스터라이저 상태를 설정합니다.
	DeviceContext->RSSetState(mResterizer);

	// Setup the viewport for rendering.
	// 뷰포트의 렌더링을 위해 세팅합니다
	viewport.Width = (float)WinSizeX;
	viewport.Height = (float)WinSizeY;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	// Create the viewport. 뷰포트를 만듭니다.

	DeviceContext->RSSetViewports(1, &viewport);


	GetAdapterInfo();


	m_p2DSupport = new Grahpics2D();
	m_p2DSupport->initialize(hwnd, mSwapChain);

	m_p2DSupport->LoadBitMap(L"../Image/apple_1.png", L"../Image/apple_1.png");
	m_p2DSupport->LoadBitMap(L"../Image/atk_1.png", L"../Image/atk_1.png");
	
}

void HsGraphic::BeginRender()
{
	//엔진 랜더링 시작
	float Color[4] = { 0.5f, 0.0f, 0.0f, 1.0f };
	DeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
	DeviceContext->ClearRenderTargetView(mRenderTargetView, Color);
	DeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	DeviceContext->RSSetViewports(1, &mScreenViewport);
}

void HsGraphic::EngineRender()
{
	int _yPos = 50;
	int _Text_Offset = 21;
	//엔진 랜더링
	m_p2DSupport->Push_DrawText({ 10, _yPos }, 500, 1, 0, 0, 1, 20, L"Description: %s", m_AdapterDesc.Description);
	m_p2DSupport->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 1, 0, 1, 20,L"VendorID: %u", m_AdapterDesc.VendorId);
	m_p2DSupport->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 1, 0, 1, 20,L"DeviceID: %u", m_AdapterDesc.DeviceId);
	m_p2DSupport->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 1, 0, 1, 20,L"SubSysID: %u", m_AdapterDesc.SubSysId);
	m_p2DSupport->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 1, 0, 1, 20,L"Revision: %u", m_AdapterDesc.Revision);
	m_p2DSupport->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 0, 1, 1, 20,L"VideoMemory: %lu MB",	 m_AdapterDesc.DedicatedVideoMemory / 1024 / 1024);
	m_p2DSupport->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 0, 1, 1, 20,L"SystemMemory: %lu MB",	 m_AdapterDesc.DedicatedSystemMemory / 1024 / 1024);
	m_p2DSupport->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 0, 1, 1, 20,L"SharedSysMemory: %lu MB", m_AdapterDesc.SharedSystemMemory / 1024 / 1024);
	m_p2DSupport->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 1, 1, 0, 1, 20,L"AdpaterLuid: %u.%d",      m_AdapterDesc.AdapterLuid.HighPart, m_AdapterDesc.AdapterLuid.LowPart);

	m_p2DSupport->Push_DrawImage
	(
		L"../Image/apple_1.png", //name
		{ 1000,1 },				//Image Position
		{ 1,1 },				//Image Scale//
		0,
		1.0f,
		{ 0,0 }, //POS
		{ 0.1f, 0.1f }, //SCALE/
		0,
		1.0f
	);
	m_p2DSupport->Push_DrawSprite
	(
		L"../Image/atk_1.png", //name
		{ 1000,400 },				//Image Position
		{ 1,1 },				//Image Scale//
		0,
		1.0f,
		{ 0,0 }, //POS
		{ 1.0f, 1.0f }, //SCALE/
		0,
		1.0f,
		6,
		171,
		144
	);

}

void HsGraphic::EndRender()
{
	m_p2DSupport->Draw_AllImage();
	m_p2DSupport->Draw_AllSprite();
	m_p2DSupport->Draw_AllText();
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

DXGI_ADAPTER_DESC1 HsGraphic::GetAdapter()
{
	
	return this->m_AdapterDesc;
}

HRESULT HsGraphic::GetAdapterInfo()
{
	// DXGI버전별로 다름
	IDXGIAdapter1* pAdapter = NULL;
	IDXGIFactory1* pFactory = NULL;

	HRESULT hr = S_OK;

	// DXGIFactory 개체 생성(DXGI.lib 필요)
	if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&pFactory)))
	{
		return E_FAIL;
	}

	hr = pFactory->EnumAdapters1(0, &pAdapter);

	if (hr != DXGI_ERROR_NOT_FOUND)
	{
		pAdapter->GetDesc1(&m_AdapterDesc);
	}
	SAFE_RELEASE(pAdapter);
	SAFE_RELEASE(pFactory);

	return hr;
}

TextureBuffer* HsGraphic::CreateTextureBuffer(std::string path)
{
	ID3D11ShaderResourceView* Textures = nullptr;
	ID3D11Resource* texResource = nullptr;

	CString _path = path.c_str();
	 
	//if (CreateDDSTextureFromFile(Device, _path, &texResource, &Textures, 0))
	//{
	//	return nullptr;
	//}
	
	//TextureBuffer* buffer = new TextureBuffer();
	//buffer->TextureBufferPointer = Textures;
	//buffer->size = sizeof(ID3D11ShaderResourceView);
	//
	//texResource->Release();

	//return buffer;
	return nullptr;
}

void HsGraphic::OnReSize(int Change_Width, int Change_Height)
{
	WinSizeX = Change_Width;
	WinSizeY = Change_Height;

	assert(DeviceContext);
	assert(Device);
	assert(mSwapChain);

	mRenderTargetView->Release();	//랜더타겟 삭제
	mDepthStencilView->Release();	//뎁스스텐실 삭제

	mRenderTargetView = nullptr;
	mDepthStencilView = nullptr;

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

	EngineRender();

	EndRender();
}

void HsGraphic::Delete()
{
	mWireframe->Release();
	mSolid->Release();

	//mShaderManager;
	//mRenderManager;
}


