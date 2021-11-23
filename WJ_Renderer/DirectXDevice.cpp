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
	// �̺κ��� �ʿ��Ѱ�?..
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

	// DXGI ���丮 ����.
 	HR(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory));

	// Use the factory to create an adapter for the primary graphics interface (video card).
	//���丮 ��ü�� ����ؼ� ���� �⺻ �׷��� �������̽��� �����(���� ī��)�� ����ϴ�.
	HR(factory->EnumAdapters(0, &adapter));

	// Enumerate the primary adapter output (monitor).
	// �⺻ ����� ���(�����)�� �����մϴ�.
	HR(adapter->EnumOutputs(0, &adapterOutput));

	// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
	//����� ���(�����)�� ���� DXGI_FORMAT_R8G8B8A8_UNORM ���÷��� ���Ŀ� �´� ��� ���� �����ɴϴ�.
	HR(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL));

	// Create a list to hold all the possible display modes for this monitor/video card combination.
	// �� �����/���� ī�� ���տ� ��� ������ ��� ���÷��� ��带 ������ ����� ����ϴ�.
	displayModeList = new DXGI_MODE_DESC[numModes];

	if (nullptr == displayModeList) { return nullptr; }

	// Now fill the display mode list structures.
	// ���� ���÷��� ��� ������ ä��ϴ�.
	HR(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList));

	// Now go through all the display modes and find the one that matches the screen width and height.
	// When a match is found store the numerator and denominator of the refresh rate for that monitor.
	//
	// ���� ��� ���÷��� ��带 ���캸�� ȭ�� ���� ���̿� �´� ��带 ã���ϴ�.
	// ��ġ �׸��� �߰ߵǸ� �ش� ������� ���� ��ħ ���� ���ڿ� �и� �����մϴ�.
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
	// �����(���� ī��) ������ �����ɴϴ�.
	HR(adapter->GetDesc(&adapterDesc));

	// ����(�׷���)ī�� �޸𸮸� MB ������ �ٲ��ش�.
	_vedioCard = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

	// Release the display mode list.
	//���÷��� ��� ����� �����մϴ�.
	delete[] displayModeList;
	displayModeList = 0;

	// Release the adapter output.
	// �����(�׷���ī��) ����� �����մϴ�.()
	SAFE_RELEASE(adapterOutput);

	// ����͸� Ǳ�ϴ�.
	SAFE_RELEASE(adapter);

	// ���丮��ü�� ������ŵ�ϴ�.
	SAFE_RELEASE(factory);

	return backBufferPtr;
}

DXGI_SWAP_CHAIN_DESC DirectXDevice::CreateInitSwapChain(HWND _hWnd)
{
	// Initialize the swap chain description.
	// ����ü�ο� ���� ������ �ʱ�ȭ�մϴ�.
	DXGI_SWAP_CHAIN_DESC swapChainDesc;

	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Set to a single back buffer.
	// ���� ����۷� �����մϴ�.
	swapChainDesc.BufferCount = 1;

	// �� ������ ���� ���̸� �����մϴ�.
	// 
	swapChainDesc.BufferDesc.Width = m_iWidth;
	swapChainDesc.BufferDesc.Height = m_iHeight;

	// Set regular 32-bit surface for the back buffer.
	// �� ������ �Ϲ� 32��Ʈ ǥ���� �����մϴ�.
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Set the refresh rate of the back buffer.
	// �� ������ ���� ��ħ �󵵸� �����մϴ�

	//// Vsync ����
	//swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
	//swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;

	// Vsync ������
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	// Set the usage of the back buffer.
	//�� ������ ��뷮�� �����մϴ�.
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// Set the handle for the window to render to.
	// �������� â�� �ڵ��� �����մϴ�
	swapChainDesc.OutputWindow = _hWnd;

	// Turn multisampling off.
	// ��Ƽ���ø��� ���ϴ�.
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	/// Ǯ ��ũ�� ���.
	swapChainDesc.Windowed = true;

	// Set the scan line ordering and scaling to unspecified.
	//��ĵ ���� ���� �� ������ �������� �������� �����մϴ�.
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Discard the back buffer contents after presenting.
	// �� ���� ���빰�� ���������̼� �� ����Ͻʽÿ�.
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// Don't set the advanced flags.
	//  �÷��״� �������ʴ´�
	swapChainDesc.Flags = false;

	return swapChainDesc;
}



void DirectXDevice::CreateDepthBuffer(ID3D11Texture2D* _pDepthStencilBuffer)
{
	// Set up the description of the depth buffer.
	// ���� ���ۿ� ���� ������ �����մϴ�.
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
	// �ۼ��� ������ ����Ͽ� ���� ������ �ؽ�ó�� ����ϴ�.
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
	// ���ٽ��� ���¸� �ʱ�ȭ�մϴ�.
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));

	// Set up the description of the stencil state.
	// ���ٽ��� ���¸� �����մϴ�.
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

	///���� �����ϴ� ������Ʈ
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	/*
		D3D11_COMPARISON_NEVER
		���� �񱳸� ������� ���ʽÿ�.
		D3D11_COMPARISON_LESS
		���� �����Ͱ� ��� �����ͺ��� ������ �񱳰� ����˴ϴ�.
		D3D11_COMPARISON_EQUAL
		���� �����Ͱ� ��� �����Ϳ� ������ �񱳰� ����˴ϴ�.
		D3D11_COMPARISON_LESS_EQUAL
		���� �����Ͱ� ��� �����ͺ��� �۰ų� ������ �񱳰� ����˴ϴ�.
		D3D11_COMPARISON_GREATER
		���� �����Ͱ� ��� �����ͺ��� ũ�� �񱳰� ����˴ϴ�.
		D3D11_COMPARISON_NOT_EQUAL
		���� �����Ͱ� ��� �����Ϳ� ���� ������ �񱳰� ����˴ϴ�.
		D3D11_COMPARISON_GREATER_EQUAL
		���� �����Ͱ� ��� �����ͺ��� ũ�ų� ������ �񱳰� ����˴ϴ�.
		D3D11_COMPARISON_ALWAYS
		�׻� �񱳸� ����Ͻʽÿ�.
	*/
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing.
	// �ȼ��� ������ ��� ���ٽ� �۵�.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing.
	// �ȼ��� ������ ��� ���ٽ� �۾�.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create the depth stencil state.
	// ���� ���ٽ� ���¸� ����ϴ�.
	m_pDX11Device->CreateDepthStencilState(&depthStencilDesc, &_pDepthStencilState);

	//���� ���ٽ� ���¸� �����մϴ�.
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
	// ���� ���ٽ� �並 �ʱ�ȭ�մϴ�.
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));

	// Set up the depth stencil view description.
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	if (nullptr == _pDepthStencilBuffer) { return; }
	// Create the depth stencil view.
	// �������ٽ� �並 ����ϴ�.
	m_pDX11Device->CreateDepthStencilView
	(
		_pDepthStencilBuffer,
		&depthStencilViewDesc, &_pDepthStencilView
	);

	/// ����Ÿ�ٺ�, ����/���ĽǺ並 ���������ο� ���ε��Ѵ�.
	_pDeviceContext->OMSetRenderTargets
	(
		1, 
		&_pRenderTarget,
		_pDepthStencilView
	);

	

	
}

void DirectXDevice::CreateResterize(ID3D11DeviceContext* _pDeviceContext, ID3D11RasterizerState* _pRasterizerState)
{
	//������ ������ ����ü
	D3D11_RASTERIZER_DESC rasterDesc;
	ZeroMemory(&rasterDesc, sizeof(D3D11_RASTERIZER_DESC));

	// Setup the raster description which will determine how and what polygons will be drawn.
	// �׸� ������� ����� �����ϴ� ������ ������ �����մϴ�.
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
	// ��� �ۼ��� ������ �����Ͷ����� ���¸� ����ϴ�
	(this->m_pDX11Device->CreateRasterizerState(&rasterDesc, &_pRasterizerState));

	// Now set the rasterizer state.
	//���� �����Ͷ����� ���¸� �����մϴ�.
	_pDeviceContext->RSSetState(_pRasterizerState);
}

D3D11_VIEWPORT DirectXDevice::CreateViewPort(ID3D11DeviceContext* _pDeviceContext)
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	// Setup the viewport for rendering.
	// ����Ʈ�� �������� ���� �����մϴ�
	viewport.Width = (float)m_iWidth;
	viewport.Height = (float)m_iHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	// Create the viewport. ����Ʈ�� ����ϴ�.
	_pDeviceContext->RSSetViewports(1, &viewport);

	return viewport;
}


