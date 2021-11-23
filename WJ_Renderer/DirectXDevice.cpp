#include "OneCompile.h"
#include "DirectXDefine.h"
#include "DirectXDevice.h"

DirectXDevice::DirectXDevice() : m_iWidth(1920), m_iHeight(1080),m_pDX11Device(nullptr)
{
	
	
}

DirectXDevice::~DirectXDevice()
{
	m_pDX11Device->Release();
}


void DirectXDevice::SetDevice(ID3D11Device* _v)
{
	if (nullptr == m_pDX11Device) { m_pDX11Device = std::move(_v); }
}

ID3D11Device* DirectXDevice::GetDevice()
{
	
	return m_pDX11Device;
}

int DirectXDevice::GetWidth()
{
	return this->m_iWidth;
}

int DirectXDevice::GetHeight()
{
	return this->m_iHeight;
}

void DirectXDevice::CreateSize(int _width, int _height)
{
	m_iWidth  = _width;
	m_iHeight = _height;
}

ID3D11Texture2D* DirectXDevice::CreateInitFactory(int& _vedioCard)
{
	// 이부분은 필요한가?..
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	UINT numModes, i, numerator, denominator;
	unsigned long long stringLength;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	int error;
	
	ID3D11Texture2D* backBufferPtr = nullptr;
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

	if (nullptr == displayModeList) { return nullptr; }

	// Now fill the display mode list structures.
	// 이제 디스플레이 목록 구조를 채웁니다.
	HR(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList));

	// Now go through all the display modes and find the one that matches the screen width and height.
	// When a match is found store the numerator and denominator of the refresh rate for that monitor.
	//
	// 이제 모든 디스플레이 모드를 살펴보고 화면 폭과 높이에 맞는 모드를 찾습니다.
	// 일치 항목이 발견되면 해당 모니터의 새로 고침 빈도의 분자와 분모를 저장합니다.
	for (i = 0; i < (UINT)numModes; i++)
	{
		if (displayModeList[i].Width == m_iWidth)
		{
			if (displayModeList[i].Height == (UINT)m_iHeight)
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
	_vedioCard = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

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

	return backBufferPtr;
}

DXGI_SWAP_CHAIN_DESC DirectXDevice::CreateInitSwapChain(HWND _hWnd)
{
	// Initialize the swap chain description.
	// 스왑체인에 대한 설명을 초기화합니다.
	DXGI_SWAP_CHAIN_DESC swapChainDesc;

	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Set to a single back buffer.
	// 단일 백버퍼로 설정합니다.
	swapChainDesc.BufferCount = 1;

	// 백 버퍼의 폭과 높이를 설정합니다.
	// 
	swapChainDesc.BufferDesc.Width = m_iWidth;
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
	swapChainDesc.OutputWindow = _hWnd;

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

	return swapChainDesc;
}



void DirectXDevice::CreateDepthBuffer(ID3D11Texture2D* _pDepthStencilBuffer)
{
	// Set up the description of the depth buffer.
	// 깊이 버퍼에 대한 설명을 설정합니다.
	HRESULT hr;

	D3D11_TEXTURE2D_DESC depthStencilDesc;

	ZeroMemory(&depthStencilDesc, sizeof(D3D11_TEXTURE2D_DESC));

	// Set up the description of the depth buffer.
	depthStencilDesc.Width = m_iWidth;
	depthStencilDesc.Height = m_iHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	// Create the texture for the depth buffer using the filled out description.
	// 작성한 설명을 사용하여 깊이 버퍼의 텍스처를 만듭니다.
	hr = (m_pDX11Device->CreateTexture2D
	(
		&depthStencilDesc,
		0,
		&_pDepthStencilBuffer)
	);
}
void DirectXDevice::CreateDepthStencilState(ID3D11DeviceContext* _pDeviceContext, ID3D11DepthStencilState* _pDepthStencilState)
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;

	// Initialize the description of the stencil state.
	// 스텐실의 상태를 초기화합니다.
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	// 스텐실의 상태를 설정합니다.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	///뎁스 설정하는 스테이트
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	/*
		D3D11_COMPARISON_NEVER
		절대 비교를 통과하지 마십시오.
		D3D11_COMPARISON_LESS
		원본 데이터가 대상 데이터보다 작으면 비교가 통과됩니다.
		D3D11_COMPARISON_EQUAL
		원본 데이터가 대상 데이터와 같으면 비교가 통과됩니다.
		D3D11_COMPARISON_LESS_EQUAL
		원본 데이터가 대상 데이터보다 작거나 같으면 비교가 통과됩니다.
		D3D11_COMPARISON_GREATER
		원본 데이터가 대상 데이터보다 크면 비교가 통과됩니다.
		D3D11_COMPARISON_NOT_EQUAL
		원본 데이터가 대상 데이터와 같지 않으면 비교가 통과됩니다.
		D3D11_COMPARISON_GREATER_EQUAL
		원본 데이터가 대상 데이터보다 크거나 같으면 비교가 통과됩니다.
		D3D11_COMPARISON_ALWAYS
		항상 비교를 통과하십시오.
	*/
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	// 픽셀이 전면인 경우 스텐실 작동.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	// 픽셀이 역향인 경우 스텐실 작업.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	// 깊이 스텐실 상태를 만듭니다.
	m_pDX11Device->CreateDepthStencilState(&depthStencilDesc, &_pDepthStencilState);

	//깊이 스텐실 상태를 설정합니다.
	_pDeviceContext->OMSetDepthStencilState(_pDepthStencilState, true);
}

void DirectXDevice::CreateDepthStencilView
(
	ID3D11DeviceContext* _pDeviceContext, 
	ID3D11DepthStencilView* _pDepthStencilView,
	ID3D11Texture2D* _pDepthStencilBuffer,
	ID3D11RenderTargetView* _pRenderTarget

)
{
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;

	// Initialize the depth stencil view.
	// 뎁스 스텐실 뷰를 초기화합니다.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	if (nullptr == _pDepthStencilBuffer) { return; }
	// Create the depth stencil view.
	// 뎁스스텐실 뷰를 만듭니다.
	m_pDX11Device->CreateDepthStencilView
	(
		_pDepthStencilBuffer,
		&depthStencilViewDesc, &_pDepthStencilView
	);

	/// 렌더타겟뷰, 뎁스/스탠실뷰를 파이프라인에 바인딩한다.
	_pDeviceContext->OMSetRenderTargets
	(
		1, 
		&_pRenderTarget,
		_pDepthStencilView
	);

	

	
}

void DirectXDevice::CreateResterize(ID3D11DeviceContext* _pDeviceContext, ID3D11RasterizerState* _pRasterizerState)
{
	//레스터 설명의 구조체
	D3D11_RASTERIZER_DESC rasterDesc;
	ZeroMemory(&rasterDesc, sizeof(D3D11_RASTERIZER_DESC));

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
	(this->m_pDX11Device->CreateRasterizerState(&rasterDesc, &_pRasterizerState));

	// Now set the rasterizer state.
	//이제 래스터라이저 상태를 설정합니다.
	_pDeviceContext->RSSetState(_pRasterizerState);
}

D3D11_VIEWPORT DirectXDevice::CreateViewPort(ID3D11DeviceContext* _pDeviceContext)
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	// Setup the viewport for rendering.
	// 뷰포트의 렌더링을 위해 세팅합니다
	viewport.Width = (float)m_iWidth;
	viewport.Height = (float)m_iHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	// Create the viewport. 뷰포트를 만듭니다.
	_pDeviceContext->RSSetViewports(1, &viewport);

	return viewport;
}


