#include "MultiRenderEngine.h"
#include "EngineData.h"
#include "GraphicsEngine.h"
#include "MacroDefine.h"
#include "TextureBase.h"
#include "InputLayoutData.h"
#include <iostream>
#include <d3d11.h>

#pragma comment(lib, "dxguid.lib") 
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")


MultiRenderEngine* MultiRenderEngine::m_Engine = nullptr;

MultiRenderEngine::MultiRenderEngine()
{
	m_Device		= nullptr;
	m_DeviceContext = nullptr;
	m_SwapChain		= nullptr;
	m_ViewPort		= nullptr;

	m_RenderTargetView = nullptr;
	m_DepthStencilView = nullptr;

	m_ScreenHeight	= 0;
	m_ScreenWidth	= 0;

	m_Hwnd = NULL;
}

MultiRenderEngine::~MultiRenderEngine()
{
	Test00->Delete();
	Test01->Delete();
}

MultiRenderEngine* MultiRenderEngine::Initialize(HWND hwnd, int screenWidth, int screenHeight)
{
	m_Engine = new MultiRenderEngine();

	//����̽��� ���ؽ�Ʈ�� �����Ѵ�
	m_Engine->CreateDevice(hwnd, screenWidth, screenHeight);

	//����ü�ο� �پ��ִ� ����Ÿ���� �����Ѵ�
	m_Engine->Create_SwapChain_RenderTarget();
	return m_Engine;
}

BOOL MultiRenderEngine::SplitWindow(int _Horizontal, int _Vertical)
{
	// �̹� �ɰ��� ������ ���.. (���� ��� �������� �𸣰����� �ϴ� ���Ƴ���)
	if (!Split_Window.empty())							
	{
		std::cout << "[MultiRenderEngine::SplitWindow() ����] �̹� Split�� Window�� �����մϴ�. (�ߺ�ȣ��)" << std::endl;
		return false;
	}
	// ������ �ִ� ������ �ʰ��� ��� false ����..
	if (_Horizontal > MAX_HORIZONTAL)
	{
		std::cout << "[MultiRenderEngine::SplitWindow() ����]" << MAX_HORIZONTAL << " �� �̻��� Horizontal ������ �Ұ����մϴ�." << std::endl;
		return false;
	}
	if (_Vertical > MAX_VERTICAL)
	{
		std::cout << "[MultiRenderEngine::SplitWindow() ����]" << MAX_VERTICAL << " �� �̻��� Vertical ������ �Ұ����մϴ�." << std::endl;
		return false;
	}
	if ((_Horizontal * _Vertical) > MAX_SPLIT_TARGET)
	{
		std::cout << "[MultiRenderEngine::SplitWindow() ����]" << MAX_SPLIT_TARGET << " �� �̻��� Window Split�� �Ұ����մϴ�." << std::endl;
		std::cout << " ���� �Է°� => Horizontal : " << _Horizontal << "\tVertical : " << _Vertical << std::endl;
		return false;
	}

	//for (int i = 0; i < 4; i++)
	//{
	//	//¦�� Ȧ�� �Ǻ�
	//	int num = i % 2;
	//	if (num == 0)
	//	{
	//		int startX = i * m_ScreenWidth;
	//		int StartY = i * m_ScreenHeight;
	//
	//		int Width = m_ScreenWidth / _Horizontal;
	//		int Height = m_ScreenHeight / _Vertical;
	//
	//		TextureBase* temp00 = Create_RenderTarget(startX, StartY, Width, Height);
	//	}
	//	else
	//	{
	//		int startX = i * m_ScreenWidth;
	//		int StartY = i * m_ScreenHeight;
	//
	//		int Width = m_ScreenWidth / _Horizontal;
	//		int Height = m_ScreenHeight / _Vertical;
	//
	//		TextureBase* temp00 = Create_RenderTarget(startX, StartY, Width, Height);
	//	}
	//}

	Test00 = Create_RenderTarget(0, 0, 400, 400);
	Test01 = Create_RenderTarget(400, 400, 800, 800);


	for (int i = 0; i < _Horizontal * _Vertical; i++)
	{
		/// RenderTargetView �� �����ؼ� ID3D11RenderTargetView* �ڸ��� �Ҵ��صθ� ��.
		Split_Window.insert({i, {Test00->GetRTV(), nullptr}});
		/// �ڷ����� �򰥸��Ŵٸ� ������ �����Ͻø�˴ϴ�..
		//std::pair<int, std::pair<ID3D11RenderTargetView*, GraphicEngine*>> InsertData = { i, {nullptr, nullptr} };
		//Split_Window.emplace(InsertData);
	}

	// ������ ����Ÿ���� ������ ����.
	return Split_Window.size();
}

BOOL MultiRenderEngine::RegisterRenderer(GraphicEngine* _Renderer, std::string _Engine_Name)
{
	// �̹� �����ϴ� �����̶�� return false;
	if (Registered_Engine_List.find(_Engine_Name) != Registered_Engine_List.end())
	{
		std::cout << "[MultiRenderEngine::RegisterRenderer() ����] �̹� ��ϵ� Graphic Engine�� �����մϴ�. (�ߺ�ȣ��)" << std::endl;
		return false;
	}

	// �Ҵ���� ������ ����Ʈ�� ����س��´�.
	Registered_Engine_List.insert({ _Engine_Name, _Renderer });

	//����̽��� ����̽� ���ؽ�Ʈ�� �־��ش�
	_Renderer->SetDevice(m_Device, m_DeviceContext);
	_Renderer->SetRenderTarget(Test00->GetRTV(), Test00->GetDSV(),Test00->GetView());
	return true;
}

BOOL MultiRenderEngine::SetRenderer(int _ViewPort_Number, std::string _Engine_Name)
{
	// �����찡 �����Ǿ����� ������� return false;
	if (!Split_Window.empty()) 
	{ 
		std::cout << "[MultiRenderEngine::SetRenderer() ����] ���� Split Window �� ���� �ʾҽ��ϴ�." << std::endl;
		return false; 
	}

	/// �Է¹��� ����Ʈ�� �����͸� �޾ƿ´�.
	auto Split_Window_Data = Split_Window.find(_ViewPort_Number);
	// ���� �������� ���� ����Ʈ index�� ȣ���ϰԵȴٸ� false�� ����.
	if (Split_Window_Data == Split_Window.end())
	{
		std::cout << "[MultiRenderEngine::SetRenderer() ����] �߸��� ViewPort Number�� ȣ���ϼ̽��ϴ�." << std::endl;
		std::cout << " ���� ������ ViewPort ���� => " << Split_Window.size() << std::endl;
		return false;
	}

	/// �Է¹��� ������ �����͸� �޾ƿ´�.
	auto Find_Engine_Ptr = Registered_Engine_List.find(_Engine_Name);
	// ���� ��ϵ��� ���� ������ ȣ���Ѵٸ�..
	if (Find_Engine_Ptr == Registered_Engine_List.end())
	{
		std::cout << "[MultiRenderEngine::SetRenderer() ����] ��ϵ��� ���� Engine�� ȣ���ϼ̽��ϴ�. ���� RegisterRenderer() �� ���� �׷��� ������ ������ּ���." << std::endl;
		return false;
	}

	/// �ش��ϴ� ����Ʈ�� ������ ��Ī��Ų��.
	GraphicEngine* Target_Engine = Find_Engine_Ptr->second;
	Split_Window_Data->second.second = Target_Engine;

	/// ���⼭ ��!!!!!!!!!!!!!!!!!! ������ ViewPort�� �����.
	ID3D11RenderTargetView* Target_ViewPort = Split_Window_Data->second.first;
	// ex) Target_Engine->SetViewPort(Target_ViewPort); �̷�������..

	return true;
}

void MultiRenderEngine::Render(std::queue<MeshData*>* meshList, GlobalData* global)
{
	BeginRender();

	Registered_Engine_List["����"]->Render(meshList, global);
	//for (auto _Renderer : Split_Window)
	//{
	//	//Registered_Engine_List["����"]->Render(meshList, global);
	//	/// ���������� VeiwPort ���� ������ ���ִ��� �ؾߵȴ�..
	//	// ex) _Renderer.second.second->Render(meshList, global);
	//}


	EndRender();
}

void MultiRenderEngine::Delete()
{
	Registered_Engine_List.clear();
	Split_Window.clear();
}



Vertexbuffer* MultiRenderEngine::CreateVertexBuffer(ParserData::Mesh* mModel)
{
	
	///��Ű���̾��� �⺻ ������Ʈ�� ��������
	ID3D11Buffer* mVB = nullptr;
	Vertexbuffer* vertexbuffer = new Vertexbuffer();

	//������ , �븻, uv, ź��Ÿ ���� �о��
	std::vector<Deferred32> temp;
	int Vcount = mModel->m_VertexList.size();
	temp.resize(Vcount);
	for (int i = 0; i < Vcount; i++)
	{
		temp[i].Pos = mModel->m_VertexList[i]->m_Pos;
		temp[i].Nomal = mModel->m_VertexList[i]->m_Normal;
		temp[i].Tex = { mModel->m_VertexList[i]->m_U ,mModel->m_VertexList[i]->m_V };
		temp[i].Tangent = mModel->m_VertexList[i]->m_Tanget;
	}


	//���� ����
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Deferred32) * Vcount;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &temp[0];
	m_Device->CreateBuffer(&vbd, &vinitData, &mVB);

	vertexbuffer->VertexbufferPointer = mVB;

	/////////////////////////////////////////////////// �߿��� ���־��ּ���
	vertexbuffer->VertexDataSize = sizeof(Deferred32);
	//////////////////////////////////////////////////
	return vertexbuffer;
}

Indexbuffer* MultiRenderEngine::CreateIndexBuffer(ParserData::Mesh* mModel)
{
	ID3D11Buffer* mIB = nullptr;
	Indexbuffer* indexbuffer = new Indexbuffer();

	//���� ���
	int IndexFaceCount = (int)mModel->m_IndexList.size();
	int IndexCount = IndexFaceCount * 3;

	std::vector<UINT> index;
	index.resize(IndexCount);

	int j = 0;
	for (int i = 0; i < IndexFaceCount; i++)
	{
		index[j] = mModel->m_IndexList[i]->m_Index[0];
		j++;
		index[j] = mModel->m_IndexList[i]->m_Index[1];
		j++;
		index[j] = mModel->m_IndexList[i]->m_Index[2];
		j++;
	}

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * IndexCount;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &index[0];

	m_Device->CreateBuffer(&ibd, &iinitData, &mIB);

	indexbuffer->IndexBufferPointer = mIB;

	return indexbuffer;
}

void MultiRenderEngine::CreateDevice(HWND hwnd,int screenWidth, int screenHeight)
{
	//������ �ޱ�
	m_ScreenHeight	= screenHeight;
	m_ScreenWidth	= screenWidth;
	m_Hwnd = hwnd;

	UINT createDeviceFlags = 0;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// ���� ü�� ������ �ʱ�ȭ..
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// swapChainDesc�� ���� �� ���۷� ����..
	swapChainDesc.BufferCount = 1;

	// �� ������ �ʺ�� ���̸� ����..
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;

	// �� ���ۿ� �Ϲ� 32 ��Ʈ ǥ���� ����..
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// �� ������ ������� ����..
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	// ��ĵ ���� ���� �� ������ �������� �������� ����..
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// �� ������ ��� ����..
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	swapChainDesc.OutputWindow = (HWND)hwnd;

	// ��Ƽ ���ø��� ���ϴ�..
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = true;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// �߰� �÷��� ���� �� ��..
	swapChainDesc.Flags = createDeviceFlags;

	// featureLevel�� DirectX 11�� ����..
	D3D_FEATURE_LEVEL featurelevel = D3D_FEATURE_LEVEL_11_0;

	// ���� ü��, Direct3D ��ġ �� Direct3D ��ġ ���ؽ�Ʈ ����..
	/// MSDN���� SwapChain �� Device �� �ѹ��� �������ִ� �Լ��� ������..
	HR(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featurelevel, 1,
		D3D11_SDK_VERSION, &swapChainDesc, &m_SwapChain, &m_Device, NULL, &m_DeviceContext));
}

void MultiRenderEngine::Create_SwapChain_RenderTarget()
{
	///����ü�ΰ� ����� ����Ÿ�ٰ� �������ٽ��� ����

	ID3D11Texture2D* backBuffer;
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
	HR(m_Device->CreateRenderTargetView(backBuffer, 0, &m_RenderTargetView));
	backBuffer->Release();

	ID3D11Texture2D* mDepthStencilBuffer = nullptr;
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width		= m_ScreenHeight;
	depthStencilDesc.Height		= m_ScreenWidth;
	depthStencilDesc.MipLevels	= 1;							
	depthStencilDesc.ArraySize	= 1;							

	
	depthStencilDesc.Format				= DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count	= 1;					
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage				= D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags			= D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags		= 0;
	depthStencilDesc.MiscFlags			= 0;


	m_Device->CreateTexture2D(&depthStencilDesc, 0, &mDepthStencilBuffer);
	HR(m_Device->CreateDepthStencilView(mDepthStencilBuffer, 0, &m_DepthStencilView));
	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

	//ViewPort
	m_ViewPort = new D3D11_VIEWPORT();
	m_ViewPort->TopLeftX	= 0;
	m_ViewPort->TopLeftY	= 0;
	m_ViewPort->Width		= static_cast<float>(m_ScreenWidth);
	m_ViewPort->Height		= static_cast<float>(m_ScreenHeight);
	m_ViewPort->MinDepth	= 0.0f;
	m_ViewPort->MaxDepth	= 1.0f;
}

TextureBase* MultiRenderEngine::Create_RenderTarget(int StartX, int StartY, int Width, int Height)
{
	TextureBase* temp = new TextureBase();
	temp->Initialize(m_Device, m_DeviceContext);
	temp->Create(StartX, StartY, Width, Height);
	return temp;
}

void MultiRenderEngine::BeginRender()
{
	ID3D11DepthStencilView* mPostDSV = Test00->GetDSV();
	ID3D11RenderTargetView* mPostRTV = Test00->GetRTV();
	D3D11_VIEWPORT*			mPostVP = Test00->GetView();

	m_DeviceContext->OMSetRenderTargets(1, &mPostRTV, mPostDSV);
	m_DeviceContext->RSSetViewports(1, mPostVP);

	//Ŭ����
	XMVECTORF32 DeepDarkGray = { 1, 1, 0, 1.0f };
	m_DeviceContext->ClearRenderTargetView(mPostRTV, DeepDarkGray);
	m_DeviceContext->ClearDepthStencilView(mPostDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void MultiRenderEngine::EndRender()
{
	//������������� ������Ʈ �������� mPostRTV ���⿡ �׷�����������
	ID3D11DepthStencilView* ENGINE_DSV	= m_DepthStencilView;
	ID3D11RenderTargetView* ENGINE_RTV	= m_RenderTargetView;
	D3D11_VIEWPORT			ENGINE_VP	= *m_ViewPort;
	
	//���� ����ü�ο� ����� ����۷� �������ְ� Ŭ����
	XMVECTORF32 DeepDarkGray = { 1.0f, 1.0f, 0.0f, 1.0f };
	m_DeviceContext->OMSetRenderTargets(1, &ENGINE_RTV, ENGINE_DSV);
	
	
	m_DeviceContext->RSSetViewports(1, &ENGINE_VP);
	m_DeviceContext->ClearRenderTargetView(ENGINE_RTV, DeepDarkGray);
	m_DeviceContext->ClearDepthStencilView(ENGINE_DSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	//���� ������ ����
	m_SwapChain->Present(0, 0);
}


