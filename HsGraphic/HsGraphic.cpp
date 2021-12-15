#include "GraphicDebugManager.h"
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
	mScreenViewport		= nullptr;
	mSwapChain			= nullptr;

	//������ ������
	WinSizeX = 0;
	WinSizeY = 0;

	mWireframe	= nullptr;
	mSolid		= nullptr;

	mShaderManager	= nullptr;
	mRenderManager	= nullptr;
	mDebugManager	= nullptr;
}

HsGraphic::~HsGraphic()
{
	
}

void HsGraphic::Initialize(HWND _hWnd, int screenWidth, int screenHeight)
{
	WinSizeX	= screenWidth;
	WinSizeY	= screenHeight;
	hwnd		= _hWnd;

	//����̽� ����
	CreateDevice();
	//����Ʈ ����
	Create_ViewPort();
	//����ü�ο��� ����Ÿ���� ����
	Create_SwapChain_RenderTarget();


	//����̽��� ���ؽ�Ʈ�� ���� ���ÿ� ���� �Ŵ��� �ʱ�ȭ
	mShaderManager = new ShaderManager();
	mShaderManager->Initialize(Device, DeviceContext);

	//����� �Ŵ��� �ʱ�ȭ
	mDebugManager = new GraphicDebugManager();
	mDebugManager->Initialize(Device, DeviceContext);

	//������ �Ŵ��� �ʱ�ȭ
	mRenderManager = new RenderingManager();
	mRenderManager->Initialize(Device, DeviceContext, mShaderManager, mDebugManager);
}

Indexbuffer* HsGraphic::CreateIndexBuffer(ParserData::Mesh* mModel)
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

	Device->CreateBuffer(&ibd, &iinitData, &mIB);

	indexbuffer->IndexBufferPointer = mIB;
	indexbuffer->Count = IndexCount * 3;

	return indexbuffer;
}

Vertexbuffer* HsGraphic::CreateVertexBuffer(ParserData::Mesh* mModel)
{
	//���� 	
	Vertexbuffer* vertexbuffer;
	switch (mModel->m_MeshType)
	{
	case MESH_TYPE::SKIN_MESH:
		vertexbuffer = CreateSkinngingVertexBuffer(mModel);
		break;
	default:
		vertexbuffer = CreateBasicVertexBuffer(mModel);
		break;
	}

	return vertexbuffer;
}

Vertexbuffer* HsGraphic::CreateTerrainVertexBuffer(ParserData::Mesh* mModel, std::string maskName)
{
	return nullptr;
}

ID3D11RenderTargetView* HsGraphic::GetEngineRTV()
{
	return mRenderTargetView;
}

ID3D11DepthStencilView* HsGraphic::GetEngineDSV()
{
	return mDepthStencilView;
}

void HsGraphic::CreateDevice()
{
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
	swapChainDesc.BufferDesc.Width = WinSizeX;
	swapChainDesc.BufferDesc.Height = WinSizeY;

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
	(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featurelevel, 1,
		D3D11_SDK_VERSION, &swapChainDesc, &mSwapChain, &Device, NULL, &DeviceContext));
}

void HsGraphic::BeginRender()
{
	XMVECTORF32 DeepDarkGray = { 0.15f, 0.15f, 0.15f, 1.0f };
	DeviceContext->ClearRenderTargetView(mRenderTargetView, DeepDarkGray);
	DeviceContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
}

void HsGraphic::EndRender()
{
	//���� ������ ����
	mSwapChain->Present(0, 0);
}

Vertexbuffer* HsGraphic::CreateBasicVertexBuffer(ParserData::Mesh* mModel)
{
	///��Ű���̾��� �⺻ ������Ʈ�� ��������
	ID3D11Buffer* mVB = nullptr;
	Vertexbuffer* vertexbuffer = new Vertexbuffer();

	//������ , �븻, uv, ź��Ÿ ���� �о��
	std::vector<Deferred32> temp;
	int Vcount = (int)mModel->m_VertexList.size();
	temp.resize(Vcount);
	for (int i = 0; i < Vcount; i++)
	{
		temp[i].Pos = mModel->m_VertexList[i]->m_Pos;
		temp[i].Nomal = mModel->m_VertexList[i]->m_Normal;
		temp[i].Tex = mModel->m_VertexList[i]->m_UV;
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
	Device->CreateBuffer(&vbd, &vinitData, &mVB);

	vertexbuffer->VertexbufferPointer = mVB;
	vertexbuffer->Count = Vcount;

	/////////////////////////////////////////////////// �߿��� ���־��ּ���
	vertexbuffer->VertexDataSize = sizeof(Deferred32);
	//////////////////////////////////////////////////
	

	return vertexbuffer;
}

Vertexbuffer* HsGraphic::CreateSkinngingVertexBuffer(ParserData::Mesh* mModel)
{
	///��Ű���� ������Ʈ�� ��������
	ID3D11Buffer* mVB = nullptr;
	Vertexbuffer* vertexbuffer = new Vertexbuffer();

	//������ , �븻, uv, ź��Ÿ ���� �о��
	std::vector<Skinning32> temp;
	int Vcount = (int)mModel->m_VertexList.size();
	temp.resize(Vcount);


	for (int i = 0; i < Vcount; i++)
	{
		ParserData::Vertex* One = mModel->m_VertexList[i];

		temp[i].Pos = One->m_Pos;
		temp[i].Nomal = One->m_Normal;
		temp[i].Tex = One->m_UV;
		temp[i].Tangent = One->m_Tanget;


		int Count = (int)One->m_BoneWeights.size();
		for (int j = 0; j < Count; j++)
		{
			if (j <= 3)
			{
				temp[i].BoneWeights01[j] = One->m_BoneWeights[j];
				temp[i].BoneIndex01[j] = One->m_BoneIndices[j];
			}
			else
			{
				temp[i].BoneWeights02[j - 4] = One->m_BoneWeights[j];
				temp[i].BoneIndex02[j - 4] = One->m_BoneIndices[j];
			}
		}

	}


	//���� ����
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Skinning32) * Vcount;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &temp[0];
	Device->CreateBuffer(&vbd, &vinitData, &mVB);

	vertexbuffer->VertexbufferPointer = mVB;
	vertexbuffer->Count = Vcount;

	/////////////////////////////////////////////////// �߿��� ���־��ּ���
	vertexbuffer->VertexDataSize = sizeof(Skinning32);
	//////////////////////////////////////////////////

	return vertexbuffer;
}


TextureBuffer* HsGraphic::CreateTextureBuffer(std::string path)
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
		DirectX::CreateDDSTextureFromFile(Device, w_path, &texResource, &newTex);
	}
	else if (path.rfind(".png") != std::string::npos)
	{
		//���ڿ� ��ȯ
		std::wstring _path = std::wstring(path.begin(), path.end());
		const wchar_t* w_path = _path.c_str();

		//����
		DirectX::CreateWICTextureFromFile(Device, w_path, &texResource, &newTex);
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

void HsGraphic::OnReSize(int Change_Width, int Change_Height)
{
	WinSizeX = Change_Width;
	WinSizeY = Change_Height;

	assert(DeviceContext);
	assert(Device);
	assert(mSwapChain);

	//����Ÿ�� ����
	if (mRenderTargetView != nullptr)
	{
		mRenderTargetView->Release();
		mRenderTargetView = nullptr;
	}

	//�������ٽ� ����
	if (mDepthStencilView != nullptr)
	{
		mDepthStencilView->Release();
		mDepthStencilView = nullptr;
	}


	//����ü�� �缳��
	mSwapChain->ResizeBuffers(1, WinSizeX, WinSizeY, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

	//�������ٽ� ����Ÿ�� �����
	//CreateRenderTarget();

	//�缳��
	DeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
	DeviceContext->RSSetViewports(1, mScreenViewport);
}

void HsGraphic::Render(std::queue<MeshData*>* meshList, GlobalData* global)
{
	//��Ƽ ������ �������� �޾ƿ� DSV, RTV, VPT�� �׸��غ�
	BeginRender();

	DeviceContext->RSSetViewports(1, mScreenViewport);

	while (meshList->size() != 0)
	{
		//���� �������� ������Ʈ�� �����´�
		MeshData* Mesh = meshList->front();
		
		switch (Mesh->ObjType)
		{
			case OBJECT_TYPE::CAMERA: //ī�޶� ������Ʈ
			{
				mRenderManager->CameraUpdate(global);
				#ifdef _DEBUG
				mRenderManager->DebugUpdate();
				#endif
				break;
			}

			case OBJECT_TYPE::SKINNING: //��Ű�� �Ž�
			{
				mRenderManager->SkinningUpdate(Mesh);
				mRenderManager->Rendering(Mesh,RenderingManager::ShaderType::SKINNING);
				break;
			}

			case OBJECT_TYPE::BASE: //�⺻ �Ž�
			{
				mRenderManager->MeshUpdate(Mesh);
				mRenderManager->Rendering(Mesh, RenderingManager::ShaderType::BASIC);
				break;
			}

			case OBJECT_TYPE::BONE: //�⺻ �Ž�
			{
				mRenderManager->BoneUpdate(Mesh);
				break;
			}
		}


		//����Ѱ��� ���ش�
		meshList->pop();
	}
	
	EndRender();
}

void HsGraphic::Delete()
{
	mWireframe->Release();
	mSolid->Release();
}

void HsGraphic::SetViewPort(void* VPT, int Change_Width, int Change_Height)
{
	//����Ÿ�ٰ� �������ٽ� ����Ʈ�� �޾ƿ´�
	mScreenViewport		= reinterpret_cast<D3D11_VIEWPORT*>(VPT);

	WinSizeX = Change_Width;
	WinSizeY = Change_Height;
}
	
void HsGraphic::SetDevice(void* mDevie, void* mDevieContext)
{
	//����̽��� ���ؽ�Ʈ�� �޾ƿ´� 
	Device			= reinterpret_cast<ID3D11Device*>(mDevie);
	DeviceContext	= reinterpret_cast<ID3D11DeviceContext*>(mDevieContext);


	//����̽��� ���ؽ�Ʈ�� ���� ���ÿ� ���� �Ŵ��� �ʱ�ȭ
	mShaderManager = new ShaderManager();
	mShaderManager->Initialize(Device, DeviceContext);

	//����� �Ŵ��� �ʱ�ȭ
	mDebugManager = new GraphicDebugManager();
	mDebugManager->Initialize(Device, DeviceContext);

	//������ �Ŵ��� �ʱ�ȭ
	mRenderManager = new RenderingManager();
	mRenderManager->Initialize(Device, DeviceContext, mShaderManager, mDebugManager);
}
void HsGraphic::Create_SwapChain_RenderTarget()
{
	ID3D11Texture2D* backBuffer;
	mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer));
	Device->CreateRenderTargetView(backBuffer, 0, &mRenderTargetView);
	backBuffer->Release();

	ID3D11Texture2D* mDepthStencilBuffer = nullptr;
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = WinSizeX;
	depthStencilDesc.Height = WinSizeY;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;

	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	Device->CreateTexture2D(&depthStencilDesc, 0, &mDepthStencilBuffer);
	Device->CreateDepthStencilView(mDepthStencilBuffer, 0, &mDepthStencilView);
	DeviceContext->OMSetRenderTargets(1, &mRenderTargetView, mDepthStencilView);
}
void HsGraphic::Create_ViewPort()
{
	mScreenViewport = new D3D11_VIEWPORT();
	mScreenViewport->TopLeftX = (float)0;
	mScreenViewport->TopLeftY = (float)0;
	mScreenViewport->Width = static_cast<float>(WinSizeX);
	mScreenViewport->Height = static_cast<float>(WinSizeY);
	mScreenViewport->MinDepth = 0.0f;
	mScreenViewport->MaxDepth = 1.0f;
}
