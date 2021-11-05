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


	//������ ������
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

	//���� ����̽��� ����
	CreateDevice();

	//����Ÿ�ٰ� ���¸� ����
	CreateRenderTarget();
	CreateRenderState();

	
	m_p2DSupport = new Grahpics2D();
	m_p2DSupport->initialize(hwnd, mSwapChain);

	m_p2DSupport->LoadBitMap(L"../Image/apple_1.png",L"../Image/apple_1.png");
	m_p2DSupport->LoadBitMap(L"../Image/atk_1.png",L"../Image/atk_1.png");
	//�Ŵ����� ����
;	//mShaderManager = new ShaderManager();
	//mRenderManager = new RenderingManager();
	//
	//mShaderManager->Initialize(Device, DeviceContext);
}

Indexbuffer* HsGraphic::CreateIndexBuffer(ParserData::Model* mModel)
{

	ID3D11Buffer* mIB = nullptr;
	Indexbuffer* indexbuffer = new Indexbuffer();

	//���� ���
	int ModelCount = (int)mModel->m_MeshList.size();
	int Icount =  (int)mModel->m_MeshList[0]->m_IndexList.size();
	std::vector<ParserData::IndexList*> IndexList = mModel->m_MeshList[0]->m_IndexList;


	//�ε��� ���۸� �����Ѵ�
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * Icount;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &IndexList[0];
	//HR(Device->CreateBuffer(&ibd, &iinitData, &mIB));

	//�ε������۸� �������ֵ��� ����
	indexbuffer->IndexBufferPointer = mIB;
	indexbuffer->size = sizeof(ID3D11Buffer);

	return indexbuffer;
}

Vertexbuffer* HsGraphic::CreateVertexBuffer(ParserData::Model* mModel)
{
	ID3D11Buffer* mVB = nullptr;
	Vertexbuffer* vertexbuffer = new Vertexbuffer();

	//���� ���
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
	//D3D�� ����� ����Ÿ�ٰ� �������ٽ� �� �����Ѵ�

	ID3D11Texture2D* backBuffer;
	mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
	if (nullptr == backBuffer) { return; }
	Device->CreateRenderTargetView(backBuffer, 0, &mRenderTargetView);
	backBuffer->Release();

	ID3D11Texture2D* mDepthStencilBuffer = nullptr;
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = WinSizeX;						//�ؽ����� �ʺ� (�ؼ�����) �ؼ�??
	depthStencilDesc.Height = WinSizeY;						//�ؽ����� ���� (�ؼ�����) �ؼ�??
	depthStencilDesc.MipLevels = 1;							//�Ӹʼ����� ����
	depthStencilDesc.ArraySize = 1;							//�ý�ó �迭�� �ؽ�ó ����*����*���ٽ� ������ ��� �ؽ�ó �ϳ����ʿ�

	//�ؼ��� ������ ���ϴ� �ʵ�� DXGI_FORMAT �������� ���� �� �ϳ��� �����Ѵ�
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;					//SampleDesc = ����ǥ�� ������ ǰ�������� �����ϴ� ����ü
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;			//�ؽ�ó�� �뵵�� ���ϴ� �ʵ�
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;	//�ڿ��� ���������ο� ������� ����������
	depthStencilDesc.CPUAccessFlags = 0;					//CPU�� �ڿ��� �����ϴ� ����� �����ϴ� �÷��׸� ����
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
	//���� ���¸� �������ش�

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
	// DXGI ���丮 ����.

	HRESULT hr = S_OK;
	hr = (CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory));

	// Use the factory to create an adapter for the primary graphics interface (video card).
	//���丮 ��ü�� ����ؼ� ���� �⺻ �׷��� �������̽��� �����(���� ī��)�� ����ϴ�.
	hr = (factory->EnumAdapters(0, &adapter));

	// Enumerate the primary adapter output (monitor).
	// �⺻ ����� ���(�����)�� �����մϴ�.
	hr = (adapter->EnumOutputs(0, &adapterOutput));

	// Get the number of modes that fit the DXGI_FORMAT_R8G8B8A8_UNORM display format for the adapter output (monitor).
	//����� ���(�����)�� ���� DXGI_FORMAT_R8G8B8A8_UNORM ���÷��� ���Ŀ� �´� ��� ���� �����ɴϴ�.
	hr = (adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL));

	// Create a list to hold all the possible display modes for this monitor/video card combination.
	// �� �����/���� ī�� ���տ� ��� ������ ��� ���÷��� ��带 ������ ����� ����ϴ�.
	displayModeList = new DXGI_MODE_DESC[numModes];

	if (nullptr == displayModeList) { return; }

	// Now fill the display mode list structures.
	// ���� ���÷��� ��� ������ ä��ϴ�.
	hr = (adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList));

	// Now go through all the display modes and find the one that matches the screen width and height.
	// When a match is found store the numerator and denominator of the refresh rate for that monitor.
	//
	// ���� ��� ���÷��� ��带 ���캸�� ȭ�� ���� ���̿� �´� ��带 ã���ϴ�.
	// ��ġ �׸��� �߰ߵǸ� �ش� ������� ���� ��ħ ���� ���ڿ� �и� �����մϴ�.
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
	// �����(���� ī��) ������ �����ɴϴ�.
	hr = (adapter->GetDesc(&adapterDesc));

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
	swapChainDesc.BufferDesc.Width = WinSizeX;
	swapChainDesc.BufferDesc.Height = WinSizeY;

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
	swapChainDesc.OutputWindow = hwnd;

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

	// Set the feature level to DirectX 11.
	// ���� ������ DirectX 11�� ����
	m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

	// ���� ü�ΰ� Device�� ���� ����. (D2D�� �����ϱ� ���� �ɼ����� BGRA �� ���� �� �ξ���.)
	D3D11CreateDeviceAndSwapChain
	(
		NULL, D3D_DRIVER_TYPE_HARDWARE,
		NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		&m_FeatureLevel, 1,
		D3D11_SDK_VERSION,
		&swapChainDesc, &mSwapChain, &Device, NULL, &DeviceContext
	);

	// Get the pointer to the back buffer.
	//�����͸� ���� ���۷� �������ϴ�.
	(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferPtr));

	if (nullptr == backBufferPtr) { return; }

	// Create the render target view with the back buffer pointer.
	// �� ���� �����͸� ����Ͽ� ���� ��� �並 �ۼ��մϴ�.
	Device->CreateRenderTargetView
	(
		backBufferPtr, NULL, &mRenderTargetView
	);

	// Release pointer to the back buffer as we no longer need it.
	// �� �̻� �ʿ����� �����Ƿ� �ĸ� ���ۿ� ���� ���� �Լ��Դϴ�.
	SAFE_RELEASE(backBufferPtr);

	// Initialize the description of the depth buffer.
	// ���̹��ۿ� ���� ������ �ʱ�ȭ �մϴ�.
	ZeroMemory(&depthBufferDesc, sizeof(depthBufferDesc));

	// Set up the description of the depth buffer.
	// ���� ���ۿ� ���� ������ �����մϴ�.
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
	// �������ٽ� �並 ����ϴ�.
	Device->CreateDepthStencilView
	(
		mDepthStencilBuffer,
		&depthStencilViewDesc, &mDepthStencilView
	);

	/// ����Ÿ�ٺ�, ����/���ĽǺ並 ���������ο� ���ε��Ѵ�.
	DeviceContext->OMSetRenderTargets
	(
		1, &mRenderTargetView, mDepthStencilView
	);

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
	(Device->CreateRasterizerState(&rasterDesc, &mResterizer));

	// Now set the rasterizer state.
	//���� �����Ͷ����� ���¸� �����մϴ�.
	DeviceContext->RSSetState(mResterizer);

	// Setup the viewport for rendering.
	// ����Ʈ�� �������� ���� �����մϴ�
	viewport.Width = (float)WinSizeX;
	viewport.Height = (float)WinSizeY;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	// Create the viewport. ����Ʈ�� ����ϴ�.

	DeviceContext->RSSetViewports(1, &viewport);


	GetAdapterInfo();


	m_p2DSupport = new Grahpics2D();
	m_p2DSupport->initialize(hwnd, mSwapChain);

	m_p2DSupport->LoadBitMap(L"../Image/apple_1.png", L"../Image/apple_1.png");
	m_p2DSupport->LoadBitMap(L"../Image/atk_1.png", L"../Image/atk_1.png");
	
}

void HsGraphic::BeginRender()
{
	//���� ������ ����
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
	//���� ������
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
	//���� ������ ����
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
	// DXGI�������� �ٸ�
	IDXGIAdapter1* pAdapter = NULL;
	IDXGIFactory1* pFactory = NULL;

	HRESULT hr = S_OK;

	// DXGIFactory ��ü ����(DXGI.lib �ʿ�)
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

	mRenderTargetView->Release();	//����Ÿ�� ����
	mDepthStencilView->Release();	//�������ٽ� ����

	mRenderTargetView = nullptr;
	mDepthStencilView = nullptr;

	//����ü�� �缳��
	mSwapChain->ResizeBuffers(1, WinSizeX, WinSizeY, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

	//�������ٽ� ����Ÿ�� �����
	CreateRenderTarget();

	//�缳��
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


