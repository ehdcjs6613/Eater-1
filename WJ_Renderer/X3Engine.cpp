#include "OneCompile.h"
#include "DDSTextureLoader11.h"
#include "DirectXDefine.h"
#include "DirectXDevice.h"
#include "DirectXDeviceContext.h"
#include "DirectXSwapChain.h"
#include "DirectXRasterizerState.h"
#include "DirectXAdapter.h"
#include "GraphicsEngine.h"
#include "SharedData.h"
#include "XRenderer.h"
#include "X3Engine.h"
#include "Grahpics2D.h"



X3Engine::X3Engine() : m_pDevice(nullptr), m_pDeviceContext(nullptr) 
{
	m_pDevice = new DirectXDevice();
	m_pDeviceContext = new DirectXDeviceContext();

	//HR(m_pDeviceContext->CreateDeviceContext(m_pDevice->m_pDX11Device));

	m_pSwapChain = new DirectXSwapChain(m_pDevice->m_pDX11Device);
	m_pRenderer = new XRenderer();
	m_pRasterizerState = new DirectXRasterizerState();
	m_pRasterizerSolid = new DirectXRasterizerState();
	m_pRasterizerWire = new DirectXRasterizerState();
	m_pAdapter = new DirectXAdapter();
	
}

X3Engine::~X3Engine()
{

}

void X3Engine::Initialize(HWND _hWnd, int screenWidth, int screenHeight)
{



	m_hWnd		= _hWnd;
	m_iWidth	= screenWidth;
	m_iHeight	= screenHeight;

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
	HR(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory));

	// Use the factory to create an adapter for the primary graphics interface (video card).
	//팩토리 객체를 사용해서 에서 기본 그래픽 인터페이스용 어댑터(비디오 카드)를 만듭니다.
	HR(factory->EnumAdapters(0, &adapter));

	// Enumerate the primary adapter output (monitor).
	// 기본 어댑터 출력(모니터)을 열거합니다.
	HR(adapter->EnumOutputs(0, &adapterOutput));

	// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
	//어댑터 출력(모니터)에 대한 DXGI_FORMAT_R8G8B8A8_UNORM 디스플레이 형식에 맞는 모드 수를 가져옵니다.
	HR(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL));

	// Create a list to hold all the possible display modes for this monitor/video card combination.
	// 이 모니터/비디오 카드 조합에 사용 가능한 모든 디스플레이 모드를 보유할 목록을 만듭니다.
	displayModeList = new DXGI_MODE_DESC[numModes];

	if (nullptr == displayModeList){ return; }

	// Now fill the display mode list structures.
	// 이제 디스플레이 목록 구조를 채웁니다.
	HR(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList));

	// Now go through all the display modes and find the one that matches the screen width and height.
	// When a match is found store the numerator and denominator of the refresh rate for that monitor.
	//
	// 이제 모든 디스플레이 모드를 살펴보고 화면 폭과 높이에 맞는 모드를 찾습니다.
	// 일치 항목이 발견되면 해당 모니터의 새로 고침 빈도의 분자와 분모를 저장합니다.
	for (i = 0; i < numModes; i++)
	{
		if (displayModeList[i].Width == (unsigned int)m_iWidth)
		{
			if (displayModeList[i].Height == (unsigned int)m_iHeight)
			{
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
			}
		}
	}

	// Get the adapter (video card) description.
	// 어댑터(비디오 카드) 설명을 가져옵니다.
	HR(adapter->GetDesc(&adapterDesc));

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
	swapChainDesc.BufferDesc.Width	= m_iWidth;
	swapChainDesc.BufferDesc.Height = m_iHeight;

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
	swapChainDesc.OutputWindow = m_hWnd;

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
	swapChainDesc.Flags = 0;

	// Set the feature level to DirectX 11.
	m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

	// 스왑 체인과 Device를 같이 생성. (D2D를 지원하기 위해 옵션으로 BGRA 를 셋팅 해 두었다.)
	D3D11CreateDeviceAndSwapChain
	(
		NULL, D3D_DRIVER_TYPE_HARDWARE, 
		NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		&m_FeatureLevel, 1,
		D3D11_SDK_VERSION, 
		&swapChainDesc, &m_pSwapChain->m_pSwapChain, &m_pDevice->m_pDX11Device, NULL, &m_pDeviceContext->m_pDX11DeviceContext
	);

	// Get the pointer to the back buffer.
	(m_pSwapChain->GetSwapChain()->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr));

	// Create the render target view with the back buffer pointer.
	m_pDevice->GetDevice()->CreateRenderTargetView
	(
		backBufferPtr, NULL, &m_pRenderer->m_pRenderTarget[0]
	);

	// Release pointer to the back buffer as we no longer need it.
	SAFE_RELEASE(backBufferPtr);

	// Initialize the description of the depth buffer.
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	depthBufferDesc.Width = m_iWidth;
	depthBufferDesc.Height = m_iHeight;
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
	(m_pDevice->GetDevice()->CreateTexture2D(&depthBufferDesc, NULL, &m_pRenderer->m_pDepthStencil_Buffer));
	
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
	(m_pDevice->GetDevice()->CreateDepthStencilState(&depthStencilDesc, &m_pRenderer->m_pDepthStencil_State));

	// Set the depth stencil state.
	m_pDeviceContext->GetDeviceContext()->OMSetDepthStencilState(m_pRenderer->GetDepthStencil_State(), 1);

	// Initialize the depth stencil view.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	// Create the depth stencil view.
	m_pDevice->m_pDX11Device->CreateDepthStencilView
	(
		m_pRenderer->m_pDepthStencil_Buffer, 
		&depthStencilViewDesc, &m_pRenderer->m_pDepthStencil_View
	);

	/// 렌더타겟뷰, 뎁스/스탠실뷰를 파이프라인에 바인딩한다.
	m_pDeviceContext->GetDeviceContext()->OMSetRenderTargets
	(
		1, &m_pRenderer->m_pRenderTarget[0], m_pRenderer->GetDepthStencil_View()
	);

	// Setup the raster description which will determine how and what polygons will be drawn.
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
	(m_pDevice->GetDevice()->CreateRasterizerState(&rasterDesc, &m_pRasterizerState->m_pFrameRS));

	// Now set the rasterizer state.
	m_pDeviceContext->GetDeviceContext()->RSSetState( m_pRasterizerState->GetFrameRS());

	// Setup the viewport for rendering.
	// 뷰포트의 렌더링을 위해 세팅합니다
	viewport.Width	  = (float)m_iWidth;
	viewport.Height	  = (float)m_iHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	// Create the viewport. 뷰포트를 만듭니다.
	m_pDeviceContext->GetDeviceContext()->RSSetViewports(1, &viewport);

	
	// Render State
	CreateRenderState();

	// 어댑터 정보를 얻는다.
	m_pAdapter->GetAdapter();

	m_pAdapter->GetAdapterInfo();

	m_pGraphics2D = new Grahpics2D(m_hWnd, m_pSwapChain->m_pSwapChain);

}

Indexbuffer* X3Engine::CreateIndexBuffer(ParserData::Model* mModel)
{
	return nullptr;
}

Vertexbuffer* X3Engine::CreateVertexBuffer(ParserData::Model* mModel)
{
	return nullptr;
}

void X3Engine::CreateTextureBuffer()
{
}

void X3Engine::OnReSize(float Change_Width, float Change_Height)
{
	/// 바뀐 화면의 사이즈를 저장해 준뒤에
	m_iWidth = Change_Width;
	m_iHeight = Change_Height;
	/// 화면을 나타내는 예전의 view를 삭제하고 현재것으로 새로 생성한다.
	

	/// 재구성 하는데 필요한 정보들 => 랜더타겟의 뷰, 스탠실 뷰,버퍼


}

void X3Engine::Render(std::queue<MeshData*>* meshList, GlobalData* global)
{
	m_pRenderer->Render_Begin(m_pDeviceContext->m_pDX11DeviceContext);
	
	m_pRenderer->Render_Update(m_pDeviceContext->m_pDX11DeviceContext);

	m_pRenderer->Render_End(m_pDeviceContext->m_pDX11DeviceContext);


}

void X3Engine::CreateRenderState()
{
	this->m_pRasterizerSolid->Create(this->m_pDevice->GetDevice(), StateRS::eSolid);
	this->m_pRasterizerWire->Create(this->m_pDevice->GetDevice(), StateRS::eWireFrame);
}

void X3Engine::DrawSystemStatus()
{
	// 피쳐레벨
	int _yPos = 50;
	int _Text_Offset = 21;
	
	m_pGraphics2D->Push_DrawText({ 10, _yPos }, 500, 1, 0, 0, 1, 20, (TCHAR*)L"Description: %s", m_pAdapter->GetAdapter().Description);
	m_pGraphics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 1, 0, 1, 20, (TCHAR*)L"VendorID: %u", m_pAdapter->GetAdapter().VendorId);
	m_pGraphics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 1, 0, 1, 20, (TCHAR*)L"DeviceID: %u", m_pAdapter->GetAdapter().DeviceId);
	m_pGraphics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 1, 0, 1, 20, (TCHAR*)L"SubSysID: %u", m_pAdapter->GetAdapter().SubSysId);
	m_pGraphics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 1, 0, 1, 20, (TCHAR*)L"Revision: %u", m_pAdapter->GetAdapter().Revision);
	m_pGraphics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 0, 1, 1, 20, (TCHAR*)L"VideoMemory: %lu MB", m_pAdapter->GetAdapter().DedicatedVideoMemory / 1024 / 1024);
	m_pGraphics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 0, 1, 1, 20, (TCHAR*)L"SystemMemory: %lu MB", m_pAdapter->GetAdapter().DedicatedSystemMemory / 1024 / 1024);
	m_pGraphics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 0, 1, 1, 20, (TCHAR*)L"SharedSysMemory: %lu MB", m_pAdapter->GetAdapter().SharedSystemMemory / 1024 / 1024);
	m_pGraphics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 1, 1, 0, 1, 20, (TCHAR*)L"AdpaterLuid: %u.%d", m_pAdapter->GetAdapter().AdapterLuid.HighPart, m_pAdapter->GetAdapter().AdapterLuid.LowPart);

}

void X3Engine::SetTextureSRV(SharedRenderData* _SRD)
{
	//if (!_SRD->Ambient_Texture.empty())
	//{
	//	for (auto k : _SRD->Ambient_Texture)
	//	{
	//		// 텍스쳐 생성을 위한 임시 객체
	//		ID3D11Resource* Texture_Resource = nullptr;
	//		// 텍스쳐 SRV
	//		ID3D11ShaderResourceView* DX11_SRV = nullptr;
	//		// 텍스쳐 정보 셋팅.
	//		CreateWICTextureFromFile(m_pDevice->GetDevice(), k.second->Texture_Path.c_str(), &Texture_Resource, &DX11_SRV);
	//		ReleaseCOM(Texture_Resource);
	//
	//		k.second->Texture_SRV = DX11_SRV;
	//	}
	//}
	//
	//if (!_SRD->Emissive_Texture.empty())
	//{
	//	for (auto k : _SRD->Emissive_Texture)
	//	{
	//		// 텍스쳐 생성을 위한 임시 객체
	//		ID3D11Resource* Texture_Resource = nullptr;
	//		// 텍스쳐 SRV
	//		ID3D11ShaderResourceView* DX11_SRV = nullptr;
	//		// 텍스쳐 정보 셋팅.
	//		CreateWICTextureFromFile(m_pDevice->GetDevice(), k.second->Texture_Path.c_str(), &Texture_Resource, &DX11_SRV);
	//		ReleaseCOM(Texture_Resource);
	//
	//		k.second->Texture_SRV = DX11_SRV;
	//	}
	//}
	//
	//if (!_SRD->Diffuse_Texture.empty())
	//{
	//	for (auto k : _SRD->Diffuse_Texture)
	//	{
	//		// 텍스쳐 생성을 위한 임시 객체
	//		ID3D11Resource* Texture_Resource = nullptr;
	//		// 텍스쳐 SRV
	//		ID3D11ShaderResourceView* DX11_SRV = nullptr;
	//		// 텍스쳐 정보 셋팅.
	//		CreateWICTextureFromFile(m_pDevice->GetDevice(), k.second->Texture_Path.c_str(), &Texture_Resource, &DX11_SRV);
	//		ReleaseCOM(Texture_Resource);
	//
	//		k.second->Texture_SRV = DX11_SRV;
	//	}
	//}
	//
	//if (!_SRD->Specular_Texture.empty())
	//{
	//	for (auto k : _SRD->Specular_Texture)
	//	{
	//		// 텍스쳐 생성을 위한 임시 객체
	//		ID3D11Resource* Texture_Resource = nullptr;
	//		// 텍스쳐 SRV
	//		ID3D11ShaderResourceView* DX11_SRV = nullptr;
	//		// 텍스쳐 정보 셋팅.
	//		CreateWICTextureFromFile(m_pDevice->GetDevice(), k.second->Texture_Path.c_str(), &Texture_Resource, &DX11_SRV);
	//		ReleaseCOM(Texture_Resource);
	//
	//		k.second->Texture_SRV = DX11_SRV;
	//	}
	//}
	//
	//if (!_SRD->NormalMap_Texture.empty())
	//{
	//	for (auto k : _SRD->NormalMap_Texture)
	//	{
	//		// 텍스쳐 생성을 위한 임시 객체
	//		ID3D11Resource* Texture_Resource = nullptr;
	//		// 텍스쳐 SRV
	//		ID3D11ShaderResourceView* DX11_SRV = nullptr;
	//		// 텍스쳐 정보 셋팅.
	//		CreateWICTextureFromFile(m_pDevice->GetDevice(), k.second->Texture_Path.c_str(), &Texture_Resource, &DX11_SRV);
	//		ReleaseCOM(Texture_Resource);
	//
	//		k.second->Texture_SRV = DX11_SRV;
	//	}
	//}
}

void X3Engine::Release()
{
	delete m_pGraphics2D;
	m_pGraphics2D = nullptr;
}
