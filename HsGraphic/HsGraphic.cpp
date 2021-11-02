#include "GraphicsEngine.h"
#include "HsGraphic.h"
#include "ParserData.h"
#include "EngineData.h"
#include "HsDefine.h"
#include <vector>
#include "Data.h"

using namespace DirectX;

HsGraphic::HsGraphic()
{
	hwnd = 0;

	m_device			= nullptr;
	m_deviceContext		= nullptr;
	m_renderTargetView	= nullptr;
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

	UINT createDeviceFlags = 0;
	D3D_FEATURE_LEVEL featureLevel;

	HRESULT hr = D3D11CreateDevice
	(
		0,							//���÷��� ���  0 = ����Ʈ 
		D3D_DRIVER_TYPE_HARDWARE,	// ???
		0,							// ����Ʈ���� ������ ����
		createDeviceFlags,			// ???
		0,							// ���˼���
		0,							// ???
		D3D11_SDK_VERSION,			//�׻� D3D11_SDK_VERSION �� ����
		&m_device,					//�Լ��� ��������ġ ������
		&featureLevel,				//null ������ �Ѱ�� �����ϴ� ���� ���� ��ɼ�������
		&m_deviceContext			//������ ������
	);

	//���� ����
	if (FAILED(hr))
	{
		return;
	}
	
	//����Ȯ��
	if (featureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MessageBox(0, L"Direct3D LEVEL 11", 0, MB_OK);
		return;
	}
	
	
	//4xMSAA ǰ�� ���� ���� ����??
	//�ϵ��� 4xMSAA�� ���� ǰ�� ������ �����ϴ��� ����
	
	UINT m4xMsaaQuality;
	m_device->CheckMultisampleQualityLevels
	(
		DXGI_FORMAT_R8G8_B8G8_UNORM,
		4,
		&m4xMsaaQuality
	);
	
	//assert�� ���� �����
	//assert�� ������ ���������� ���α׷��� �ߴ��ϸ� ���϶��� ��� �����Ŵ
	//assert(m4xMsaaQuality > 0);
	
	//��ȯ �罽 ����?
	//����ü �� ����
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	//BufferDesc = �����ϰ��� �ϴ� �ĸ� ������ �Ӽ����� �����ϴ� �������� ����ü
	
	sd.BufferCount = 1;  //��ȯ �罽���� ����� �ĸ� ������ ����
	sd.BufferDesc.Width = WinSizeX;
	sd.BufferDesc.Height = WinSizeY;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //������ �뵵
	sd.OutputWindow = hwnd; //������ ����� ǥ���� â�� �ڵ�
	
	//sampleDesc = ���� ǥ��ȭ�� ���� ������ ǥ�� ������ ǰ������
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;	//
	sd.Windowed = true;			//������ â��带 ���ϸ� true ��ü��� false
	
	//��ȯ �罽�� ����
	
	//�̰������� ������ ���Ϸ��� ��ġ�� ������ ���� IDXGIFactory �ν��Ͻ��� ����ؾ��Ѵ�
	//�׸��� �� �ν��Ͻ��� �������� ������ ���� �Ϸ��� COM ���� ������ ���ľ���..
	IDXGIDevice* dxgiDevice = 0;
	m_device->QueryInterface
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
	
	//IDXGIFactory �������̽� ����
	IDXGIFactory* dxgiFactory = 0;
	dxgiAdapter->GetParent
	(
		__uuidof(IDXGIFactory),
		(void**)&dxgiFactory
	);
	
	//�罽 ��ȯ ����
	dxgiFactory->CreateSwapChain(m_device, &sd, &mSwapChain);
	
	//�ʿ���°� ����
	dxgiAdapter->Release();
	dxgiDevice->Release();
	dxgiFactory->Release();

	CreateRenderTarget();
	CreateRenderState();
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
	HR(m_device->CreateBuffer(&ibd, &iinitData, &mIB));

	//�ε������۸� �������ֵ��� ����
	indexbuffer->IndexBufferPointer = mIB;
	indexbuffer->size = sizeof(mIB);


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
	HR(m_device->CreateBuffer(&vbd, &vinitData, &mVB));
	

	vertexbuffer->VertexbufferPointer = mVB;
	vertexbuffer->size = sizeof(mVB);

	return vertexbuffer;
}

void HsGraphic::CreateRenderTarget()
{
	ID3D11Texture2D* backBuffer;
	mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
	HR(m_device->CreateRenderTargetView(backBuffer, 0, &m_renderTargetView));
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


	m_device->CreateTexture2D(&depthStencilDesc, 0, &mDepthStencilBuffer);
	HR(m_device->CreateDepthStencilView(mDepthStencilBuffer, 0, &mDepthStencilView));
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, mDepthStencilView);

	//ViewPort
	mScreenViewport.TopLeftX = 0;
	mScreenViewport.TopLeftY = 0;
	mScreenViewport.Width = static_cast<float>(WinSizeX);
	mScreenViewport.Height = static_cast<float>(WinSizeY);
	mScreenViewport.MinDepth = 0.0f;
	mScreenViewport.MaxDepth = 1.0f;

	m_deviceContext->RSSetViewports(1, &mScreenViewport);
}

void HsGraphic::CreateRenderState()
{
	D3D11_RASTERIZER_DESC solidDesc;
	ZeroMemory(&solidDesc, sizeof(D3D11_RASTERIZER_DESC));
	solidDesc.FillMode = D3D11_FILL_SOLID;
	solidDesc.CullMode = D3D11_CULL_BACK;
	solidDesc.FrontCounterClockwise = false;
	solidDesc.DepthClipEnable = true;

	HR(m_device->CreateRasterizerState(&solidDesc, &mSolid));


	D3D11_RASTERIZER_DESC wireframeDesc;
	ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
	wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
	wireframeDesc.CullMode = D3D11_CULL_BACK;
	wireframeDesc.FrontCounterClockwise = false;
	wireframeDesc.DepthClipEnable = true;

	HR(m_device->CreateRasterizerState(&wireframeDesc, &mWireframe));
}

void HsGraphic::BeginRender()
{
	//���� ������ ����
	float DeepDarkGray[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, mDepthStencilView);
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, DeepDarkGray);
	m_deviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_deviceContext->RSSetViewports(1, &mScreenViewport);
}

void HsGraphic::EngineRender()
{
	//���� ������


}

void HsGraphic::EndRender()
{
	//���� ������ ����
	HR(mSwapChain->Present(0, 0));
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

	CString _path = path.c_str();
	 
	if ( FAILED(DirectX::CreateDDSTextureFromFile(m_device, _path, &texResource, &Textures, 0)))
	{
		CString mError = "�ؽ��� �ҷ�������� :" + _path;
		MessageBox(0, mError, 0, 0);
		return nullptr;
	}
	
	
	
	
	
	
	
	texResource->Release();

	return nullptr;
}

void HsGraphic::OnReSize(int Change_Width, int Change_Height)
{
	WinSizeX = Change_Width;
	WinSizeY = Change_Height;

	assert(m_deviceContext);
	assert(m_device);
	assert(mSwapChain);

	m_renderTargetView->Release();	//����Ÿ�� ����
	mDepthStencilView->Release();	//�������ٽ� ����

	m_renderTargetView = nullptr;
	mDepthStencilView = nullptr;

	//����ü�� �缳��
	mSwapChain->ResizeBuffers(1, WinSizeX, WinSizeY, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

	//�������ٽ� ����Ÿ�� �����
	CreateRenderTarget();

	//�缳��
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, mDepthStencilView);
	m_deviceContext->RSSetViewports(1, &mScreenViewport);
}

void HsGraphic::Render(std::queue<MeshData*>* meshList, GlobalData* global)
{
	BeginRender();

	EngineRender();

	EndRender();
}

void HsGraphic::Delete()
{
	int num = 0;
}


