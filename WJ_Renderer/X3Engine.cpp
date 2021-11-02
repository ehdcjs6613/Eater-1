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

	if (nullptr == displayModeList){ return; }

	// Now fill the display mode list structures.
	// ���� ���÷��� ��� ������ ä��ϴ�.
	HR(adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList));

	// Now go through all the display modes and find the one that matches the screen width and height.
	// When a match is found store the numerator and denominator of the refresh rate for that monitor.
	//
	// ���� ��� ���÷��� ��带 ���캸�� ȭ�� ���� ���̿� �´� ��带 ã���ϴ�.
	// ��ġ �׸��� �߰ߵǸ� �ش� ������� ���� ��ħ ���� ���ڿ� �и� �����մϴ�.
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
	// �����(���� ī��) ������ �����ɴϴ�.
	HR(adapter->GetDesc(&adapterDesc));

	// ����(�׷���)ī�� �޸𸮸� MB ������ �ٲ��ش�.
	m_videoCardMemory = (int)(adapterDesc.DedicatedVideoMemory / 1024 / 1024);

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

	// Initialize the swap chain description.
	// ����ü�ο� ���� ������ �ʱ�ȭ�մϴ�.
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// Set to a single back buffer.
	// ���� ����۷� �����մϴ�.
	swapChainDesc.BufferCount = 1;

	// �� ������ ���� ���̸� �����մϴ�.
	// 
	swapChainDesc.BufferDesc.Width	= m_iWidth;
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
	swapChainDesc.OutputWindow = m_hWnd;

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
	swapChainDesc.Flags = 0;

	// Set the feature level to DirectX 11.
	m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

	// ���� ü�ΰ� Device�� ���� ����. (D2D�� �����ϱ� ���� �ɼ����� BGRA �� ���� �� �ξ���.)
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

	/// ����Ÿ�ٺ�, ����/���ĽǺ並 ���������ο� ���ε��Ѵ�.
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
	// ����Ʈ�� �������� ���� �����մϴ�
	viewport.Width	  = (float)m_iWidth;
	viewport.Height	  = (float)m_iHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	// Create the viewport. ����Ʈ�� ����ϴ�.
	m_pDeviceContext->GetDeviceContext()->RSSetViewports(1, &viewport);

	
	// Render State
	CreateRenderState();

	// ����� ������ ��´�.
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
	/// �ٲ� ȭ���� ����� ������ �صڿ�
	m_iWidth = Change_Width;
	m_iHeight = Change_Height;
	/// ȭ���� ��Ÿ���� ������ view�� �����ϰ� ��������� ���� �����Ѵ�.
	

	/// �籸�� �ϴµ� �ʿ��� ������ => ����Ÿ���� ��, ���Ľ� ��,����


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
	// ���ķ���
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
	//		// �ؽ��� ������ ���� �ӽ� ��ü
	//		ID3D11Resource* Texture_Resource = nullptr;
	//		// �ؽ��� SRV
	//		ID3D11ShaderResourceView* DX11_SRV = nullptr;
	//		// �ؽ��� ���� ����.
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
	//		// �ؽ��� ������ ���� �ӽ� ��ü
	//		ID3D11Resource* Texture_Resource = nullptr;
	//		// �ؽ��� SRV
	//		ID3D11ShaderResourceView* DX11_SRV = nullptr;
	//		// �ؽ��� ���� ����.
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
	//		// �ؽ��� ������ ���� �ӽ� ��ü
	//		ID3D11Resource* Texture_Resource = nullptr;
	//		// �ؽ��� SRV
	//		ID3D11ShaderResourceView* DX11_SRV = nullptr;
	//		// �ؽ��� ���� ����.
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
	//		// �ؽ��� ������ ���� �ӽ� ��ü
	//		ID3D11Resource* Texture_Resource = nullptr;
	//		// �ؽ��� SRV
	//		ID3D11ShaderResourceView* DX11_SRV = nullptr;
	//		// �ؽ��� ���� ����.
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
	//		// �ؽ��� ������ ���� �ӽ� ��ü
	//		ID3D11Resource* Texture_Resource = nullptr;
	//		// �ؽ��� SRV
	//		ID3D11ShaderResourceView* DX11_SRV = nullptr;
	//		// �ؽ��� ���� ����.
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
