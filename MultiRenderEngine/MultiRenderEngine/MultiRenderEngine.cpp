#include "MultiRenderEngine.h"
#include "EngineData.h"
#include "GraphicsEngine.h"
#include "MacroDefine.h"
#include "InputLayoutData.h"

#include <iostream>
#include <d3d11.h>


#ifdef _WIN64
#ifdef _DEBUG
#pragma comment( lib, "DirectXTK_x64d.lib" )
#else
#pragma comment( lib, "DirectXTK_x64r.lib" )
#endif
#endif

//�ؽ��Ŀ�
#include "DDSTextureLoader.h"
#include "WICTextureLoader.h"


#pragma comment(lib, "dxguid.lib") 
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")

MultiRenderEngine* MultiRenderEngine::m_Engine = nullptr;

MultiRenderEngine::MultiRenderEngine()
{
	m_Device = nullptr;
	m_DeviceContext = nullptr;
	m_SwapChain = nullptr;
	m_ViewPort = nullptr;

	m_RenderTargetView = nullptr;
	m_DepthStencilView = nullptr;

	m_ScreenHeight = 0;
	m_ScreenWidth = 0;

	Split_X_Count = 0;
	Split_Y_Count = 0;

	WindowCount = 0;
	m_Hwnd = NULL;

}

MultiRenderEngine::~MultiRenderEngine()
{


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

	//����Ʈ�� ���� ���ø� �� ��ŭ �������ְ� �����Ѵ�
	ViewPortSetting(_Horizontal, _Vertical);

	return (BOOL)Split_Window.size();
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
	return true;
}

BOOL MultiRenderEngine::SetRenderer(int _ViewPort_Number, std::string _Engine_Name)
{
	// �����찡 �����Ǿ����� ������� return false;
	if (Split_Window.empty())
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
	D3D11_VIEWPORT* Target_ViewPort = Split_Window_Data->second.first;
	Target_Engine->SetViewPort(Target_ViewPort, m_ScreenWidth, m_ScreenHeight);
	// ex) Target_Engine->SetViewPort(Target_ViewPort); �̷�������..


	return true;
}

MULTIENGINE_DLL BOOL MultiRenderEngine::OnResize(int Change_Width, int Change_Height)
{
	m_ScreenWidth = Change_Width;
	m_ScreenHeight = Change_Height;

	assert(m_DeviceContext);
	assert(m_Device);
	assert(m_SwapChain);

	//����Ÿ�� ����
	if (m_RenderTargetView != nullptr)
	{
		m_RenderTargetView->Release();
		m_RenderTargetView = nullptr;
	}

	//�������ٽ� ����
	if (m_DepthStencilView != nullptr)
	{
		m_DepthStencilView->Release();
		m_DepthStencilView = nullptr;
	}


	//����ü�� �缳��
	m_SwapChain->ResizeBuffers(1, m_ScreenWidth, m_ScreenHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

	//�������ٽ� ����Ÿ�� �����
	Create_SwapChain_RenderTarget();

	//�缳��
	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

	//���� ����ִ� �������� ����Ʈ ������ �ٽ����ش�
	ViewPortSetting(Split_X_Count, Split_Y_Count, false);

	return true;
}

MULTIENGINE_DLL void MultiRenderEngine::ShadowRender(int count, std::queue<MeshData*>* meshList, GlobalData* global)
{
	if ((Split_Window[count]).second != nullptr)
	{
		(Split_Window[count]).second->ShadowRender(meshList, global);
	}
}

void MultiRenderEngine::Render(int count, std::queue<MeshData*>* meshList, GlobalData* global)
{
	if ((Split_Window[count]).second != nullptr)
	{
		(Split_Window[count]).second->Render(meshList, global);
	}

}

void MultiRenderEngine::Delete()
{
	Registered_Engine_List.clear();
	Split_Window.clear();
}



Vertexbuffer* MultiRenderEngine::CreateVertexBuffer(ParserData::Mesh* mModel)
{

	if (mModel->m_IsSkinningObject == true)
	{
		Vertexbuffer* vertexbuffer = SkinningVertexBuffer(mModel);
		return vertexbuffer;
	}
	else
	{
		Vertexbuffer* vertexbuffer = BasicVertexBuffer(mModel);
		return vertexbuffer;
	}

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

TextureBuffer* MultiRenderEngine::CreateTextureBuffer(std::string path)
{
	TextureBuffer* buffer = nullptr;

	ID3D11Resource* texResource = nullptr;
	ID3D11ShaderResourceView* newTex = nullptr;

	//�ش� ���ڿ��� dds���ִٸ� (rfind �� �ڿ������� ã�´�)
	if (path.rfind(".dds") != std::string::npos)
	{
		//���ڿ� ��ȯ
		std::wstring _path = std::wstring(path.begin(), path.end());
		const wchar_t* w_path = _path.c_str();

		//����
		DirectX::CreateDDSTextureFromFile(m_Device, w_path, &texResource, &newTex);
	}
	else if (path.rfind(".png") != std::string::npos)
	{
		//���ڿ� ��ȯ
		std::wstring _path = std::wstring(path.begin(), path.end());
		const wchar_t* w_path = _path.c_str();

		//����
		DirectX::CreateWICTextureFromFile(m_Device, w_path, &texResource, &newTex);
	}

	// Texture ���� ������ Texture Buffer ����..
	if (newTex)
	{
		buffer = new TextureBuffer();
		buffer->TextureBufferPointer = newTex;

		texResource->Release();
	}

	return buffer;
}

void MultiRenderEngine::CreateDevice(HWND hwnd, int screenWidth, int screenHeight)
{
	//������ �ޱ�
	m_ScreenHeight = screenHeight;
	m_ScreenWidth = screenWidth;
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
	depthStencilDesc.Width = m_ScreenWidth;
	depthStencilDesc.Height = m_ScreenHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;


	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;


	m_Device->CreateTexture2D(&depthStencilDesc, 0, &mDepthStencilBuffer);
	HR(m_Device->CreateDepthStencilView(mDepthStencilBuffer, 0, &m_DepthStencilView));
	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

}

void MultiRenderEngine::Create_ViewPort(int KeyNumber, int StartX, int StartY, int Width, int Height)
{
	m_ViewPort = new D3D11_VIEWPORT();
	m_ViewPort->TopLeftX = (float)StartX;
	m_ViewPort->TopLeftY = (float)StartY;
	m_ViewPort->Width = static_cast<float>(Width);
	m_ViewPort->Height = static_cast<float>(Height);
	m_ViewPort->MinDepth = 0.0f;
	m_ViewPort->MaxDepth = 1.0f;

	Split_Window.insert({ KeyNumber, {m_ViewPort,nullptr } });
}

void MultiRenderEngine::ViewPortSetting(int m_Horizontal, int m_Vertical, BOOL Create)
{
	//����Ʈ�� �����ϸ鼭  �������� X,Y ���μ��� ���̸� �������ش� 
	WindowCount = m_Horizontal * m_Vertical;
	int Width = m_ScreenWidth / m_Horizontal;
	int Height = m_ScreenHeight / m_Vertical;
	int StartX = 0;
	int StartY = 0;
	int count = 0;

	Split_X_Count = m_Horizontal;
	Split_Y_Count = m_Vertical;

	for (int i = 0; i < m_Vertical; i++)
	{
		for (int j = 0; j < m_Horizontal; j++)
		{
			if (Create)
			{
				//����Ʈ�� �����ؼ� �־��ش�
				Create_ViewPort(count, StartX, StartY, Width, Height);
			}
			else
			{
				//����Ʈ�� Resize�� ������ �����ؼ� �ٽ� �־��ش�
				ReSetting_ViewPort(count, StartX, StartY, Width, Height);
			}

			if (StartX < m_ScreenWidth - Width)
			{
				StartX += Width;
			}
			else
			{
				StartX = 0;
			}
			count++;
		}

		if (StartY < m_ScreenHeight - Height)
		{
			StartY += Height;
		}
		else
		{
			StartY = 0;
		}
	}
}

void MultiRenderEngine::ReSetting_ViewPort(int count, int StartX, int StartY, int Width, int Height)
{
	m_ViewPort = Split_Window[count].first;
	m_ViewPort->TopLeftX = (float)StartX;
	m_ViewPort->TopLeftY = (float)StartY;
	m_ViewPort->Width = static_cast<float>(Width);
	m_ViewPort->Height = static_cast<float>(Height);
	m_ViewPort->MinDepth = 0.0f;
	m_ViewPort->MaxDepth = 1.0f;

	(Split_Window[count]).second->SetViewPort(m_ViewPort, m_ScreenWidth, m_ScreenHeight);
}

Vertexbuffer* MultiRenderEngine::BasicVertexBuffer(ParserData::Mesh* mModel)
{
	///��Ű���̾��� �⺻ ������Ʈ�� ��������
	ID3D11Buffer* mVB = nullptr;
	Vertexbuffer* vertexbuffer = new Vertexbuffer();

	//������ , �븻, uv, ź��Ʈ ���� �о��
	std::vector<MeshVertex> temp;
	int Vcount = (int)mModel->m_VertexList.size();
	temp.resize(Vcount);
	for (int i = 0; i < Vcount; i++)
	{
		temp[i].Pos = mModel->m_VertexList[i]->m_Pos;
		temp[i].Normal = mModel->m_VertexList[i]->m_Normal;
		temp[i].Tex = mModel->m_VertexList[i]->m_UV;
		temp[i].Tangent = mModel->m_VertexList[i]->m_Tanget;
	}


	//���� ����
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(MeshVertex) * Vcount;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &temp[0];
	m_Device->CreateBuffer(&vbd, &vinitData, &mVB);

	vertexbuffer->VertexbufferPointer = mVB;

	/////////////////////////////////////////////////// �߿��� ���־��ּ���
	vertexbuffer->VertexDataSize = sizeof(MeshVertex);
	///////////////////////////////////////////////////

	return vertexbuffer;
}

Vertexbuffer* MultiRenderEngine::SkinningVertexBuffer(ParserData::Mesh* mModel)
{

	///��Ű���� ������Ʈ�� ��������
	ID3D11Buffer* mVB = nullptr;
	Vertexbuffer* vertexbuffer = new Vertexbuffer();

	//������ , �븻, uv, ź��Ÿ ���� �о��
	std::vector<SkinVertex> temp;
	int Vcount = (int)mModel->m_VertexList.size();
	temp.resize(Vcount);

	for (int i = 0; i < Vcount; i++)
	{
		ParserData::Vertex* One = mModel->m_VertexList[i];

		temp[i].Pos = One->m_Pos;
		temp[i].Normal = One->m_Normal;
		temp[i].Tex = One->m_UV;
		temp[i].Tangent = One->m_Tanget;


		int Count = (int)One->m_BoneWeights.size();
		for (int j = 0; j < Count; j++)
		{
			if (j <= 3)
			{
				temp[i].BoneWeight1[j]	= One->m_BoneWeights[j];
				temp[i].BoneIndex1[j]	= One->m_BoneIndices[j];
			}
			else
			{
				temp[i].BoneWeight2[j - 4]	= One->m_BoneWeights[j];
				temp[i].BoneIndex2[j - 4]	= One->m_BoneIndices[j];
			}

		}


	}

	//���� ����
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(SkinVertex) * Vcount;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &temp[0];
	m_Device->CreateBuffer(&vbd, &vinitData, &mVB);

	vertexbuffer->VertexbufferPointer = mVB;

	/////////////////////////////////////////////////// �߿��� ���־��ּ���
	vertexbuffer->VertexDataSize = sizeof(SkinVertex);
	//////////////////////////////////////////////////

	return vertexbuffer;
}




void MultiRenderEngine::BeginRender()
{
	//Ŭ����
	float color[4];

	// Setup the color to clear the buffer to.
	color[0] = 0.17f;
	color[1] = 0.17f;
	color[2] = 0.17f;
	color[3] = 1.0f;
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, color);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

}

void MultiRenderEngine::EndRender()
{
	m_SwapChain->Present(0, 0);
	//���� ������ ����
}

int MultiRenderEngine::GetWindowCount()
{
	return WindowCount;
}


