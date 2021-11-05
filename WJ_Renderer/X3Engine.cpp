#include "OneCompile.h"
#include "XVertex.h"

#include "DirectXDefine.h"
#include "DirectXDevice.h"
#include "DirectXDeviceContext.h"
#include "DirectXSwapChain.h"
#include "DirectXRasterizerState.h"
#include "DirectXAdapter.h"
#include "DirectXRenderTargeter.h"

#include "Grahpics2D.h"
#include "GraphicsEngine.h"
#include "XRenderer.h"
#include "X3Engine.h"

//����Ʈ������ ��Ŭ����
#include <wrl/client.h>

// �ʱ�ȭ �κ�.
X3Engine::X3Engine() : m_pDevice(nullptr), m_pDeviceContext(nullptr) 
{

	//���� �κ�
	m_pDevice = new DirectXDevice();
	m_pDeviceContext = new DirectXDeviceContext();
	m_pRenderer = new XRenderer();
	//m_pRenderer->m_pDirectXSwapChain = new DirectXSwapChain(m_pDevice->m_pDX11Device);
	m_pRasterizerState = new DirectXRasterizerState();
	m_pRasterizerSolid = new DirectXRasterizerState();
	m_pRasterizerWire = new DirectXRasterizerState();
	m_pAdapter = new DirectXAdapter();
	m_p2DSupport = new Grahpics2D();

	
}

X3Engine::~X3Engine()
{

}

void X3Engine::Initialize(HWND _hWnd, int _iWidth, int _iHeight)
{
	m_hWnd		= _hWnd;
	m_pDevice->CreateSize(_iWidth, _iHeight);
	
	ID3D11Texture2D* backBufferPtr = m_pDevice->CreateInitFactory(m_videoCardMemory);
	DXGI_SWAP_CHAIN_DESC swapChainDesc (m_pDevice->CreateInitSwapChain(m_hWnd));

	// Set the feature level to DirectX 11.
	// ���� ������ DirectX 11�� ����
	m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;
	m_pRenderer->Render_Initialize(m_pDevice->m_pDX11Device);

	// ���� ü�ΰ� Device�� ���� ����. (D2D�� �����ϱ� ���� �ɼ����� BGRA �� ���� �� �ξ���.)
	D3D11CreateDeviceAndSwapChain
	(
		NULL, D3D_DRIVER_TYPE_HARDWARE, 
		NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		&m_FeatureLevel, 1,
		D3D11_SDK_VERSION, 
		&swapChainDesc, 
		&m_pRenderer->m_pDirectXSwapChain->m_pSwapChain,
		&m_pDevice->m_pDX11Device,
		NULL,
		&m_pDeviceContext->m_pDX11DeviceContext
	);

	// Get the pointer to the back buffer.
	//�����͸� ���� ���۷� �������ϴ�.

	m_pRenderer->m_pRenderTargeter->Create
	(
		m_pDevice->m_pDX11Device, 
		m_pRenderer->m_pDirectXSwapChain->m_pSwapChain
	);

	m_pDevice->CreateDepthBuffer
	(
		m_pRenderer->m_pDepthStencil_Buffer
	);
	m_pDevice->CreateDepthStencilState
	(
		m_pDeviceContext->m_pDX11DeviceContext, 
		m_pRenderer->m_pDepthStencil_State
	);
	m_pDevice->CreateDepthStencilView
	(
		m_pDeviceContext->m_pDX11DeviceContext,
		m_pRenderer->m_pDepthStencil_View,
		m_pRenderer->m_pDepthStencil_Buffer,
		m_pRenderer->m_pRenderTargeter->m_pRenderTarget
	);
	m_pDevice->CreateResterize
	(
		m_pDeviceContext->m_pDX11DeviceContext,
		m_pRasterizerState->m_pFrameRS
	);
	m_pDevice->CreateViewPort
	(
		m_pDeviceContext->m_pDX11DeviceContext
	);

	///

	
	// Render State
	CreateRenderState();

	// ����� ������ ��´�.
	m_pAdapter->GetAdapter();

	m_pAdapter->GetAdapterInfo();

	
	m_p2DSupport->initialize(m_hWnd, m_pRenderer->m_pDirectXSwapChain->m_pSwapChain);

	m_p2DSupport->LoadBitMap(L"../Image/apple_1.png", L"../Image/apple_1.png");
	m_p2DSupport->LoadBitMap(L"../Image/atk_1.png", L"../Image/atk_1.png");

	if (nullptr == m_pRenderer->m_pDirectXSwapChain->m_pSwapChain)
	{
		
	}
	InitializeShaders();

	TestScene();

	//OnReSize(this->m_iWidth, m_iHeight);
}

Indexbuffer* X3Engine::CreateIndexBuffer(ParserData::Model* mModel)
{
	return nullptr;
}

Vertexbuffer* X3Engine::CreateVertexBuffer(ParserData::Model* mModel)
{
	return nullptr;
}

TextureBuffer* X3Engine::CreateTextureBuffer(std::string path)
{
	return nullptr;
}



void X3Engine::OnReSize(int Change_Width, int Change_Height)
{
	/// �ٲ� ȭ���� ����� ������ �صڿ�
	m_pDevice->GetWidth();
	m_pDevice->GetHeight();
	/// ȭ���� ��Ÿ���� ������ view�� �����ϰ� ��������� ���� �����Ѵ�.
	

	/// �籸�� �ϴµ� �ʿ��� ������ => ����Ÿ���� ��, ���Ľ� ��,����


	// Create the depth/stencil buffer and view.


	/// 4X MSAA ��带 ������� ����.
	

	/// ���Ľ� Desc�� ������� �Ͽ� ���Ľ� ���ۿ� �並 ������Ѵ�.


	/// ����Ÿ�ٺ�, ����/���ĽǺ並 ���������ο� ���ε��Ѵ�.



	// Set the viewport transform.
	/// ����Ʈ ��ȯ�� �����Ѵ�.


}

void X3Engine::Delete()
{
}

void X3Engine::Render(std::queue<MeshData*>* meshList, GlobalData* global)
{
	//������������ ����.
	//���߿� ���� ť? �����ɷ� �غ���,
	m_pRenderer->Render_Begin(m_pDeviceContext->m_pDX11DeviceContext);
	

	

	m_pRenderer->Render_Update(this->m_pDevice->m_pDX11Device, 
		m_pDeviceContext->m_pDX11DeviceContext,m_XVertexShader.GetShader(),
		m_XPexelShader.GetShader(),m_XVertexShader.GetInputLayout(),m_pVertexBuffer);

	m_pRenderer->Render_LateUpdate(m_pDeviceContext->m_pDX11DeviceContext);

	m_pRenderer->Render_2D(m_p2DSupport, this->m_pAdapter);

	m_pRenderer->Render_End(m_p2DSupport,m_pRenderer->m_pDirectXSwapChain->m_pSwapChain);
	

}

void X3Engine::CreateRenderState()
{
	this->m_pRasterizerSolid->Create(this->m_pDevice->GetDevice(), StateRS::eSolid);
	this->m_pRasterizerWire->Create(this->m_pDevice->GetDevice(), StateRS::eWireFrame);
}

void X3Engine::DrawSystemStatus()
{
	// ���ķ���
	
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

}

void X3Engine::InitializeShaders()
{
	std::wstring shaderFoler;


#pragma region DetermineShaderPath
#ifdef _DEBUG //Debug
	#ifdef _WIN64 //x64
		shaderFoler = L"../x64/Debug/";
	#else		  //x86
		shaderFoler = L"../Debug/";
	#endif // _WIN64
#else	//Release
	#ifdef _WIN64 //x64
		shaderFoler = L"../x64/Release/";
	#else
		shaderFoler = L"../Release/";
#endif // _WIN64 //x64



#endif // _DEBUG

#pragma endregion



	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",0,DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,0,0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA } ,
	};
	UINT numElements = ARRAYSIZE(layout, numElements);

	if (false == m_XVertexShader.Initialize(m_pDevice->m_pDX11Device, shaderFoler + L"vertexShaders.cso",layout,numElements ))
	{
		return;
	}
	if (false == m_XPexelShader.Initialize(m_pDevice->m_pDX11Device, shaderFoler + L"vertexShaders.cso", layout, numElements))
	{
		return;
	}


}

bool X3Engine::TestScene()
{
	//XVertex v[] =
	//{
	//	XVertex(0.0f,0.0f),
	//};

	XVertex v[] =
	{
		XVertex(0.0f, -0.1f), //Center Point
		XVertex(-0.1f, 0.0f), //Left Point
		XVertex(0.1f, 0.0f), //Right Point
	};

	D3D11_BUFFER_DESC vertexBufferDESC;
	ZeroMemory(&vertexBufferDESC, sizeof(D3D11_BUFFER_DESC));

	vertexBufferDESC.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDESC.ByteWidth = sizeof(XVertex) * ARRAYSIZE(v);
	vertexBufferDESC.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDESC.CPUAccessFlags = 0;
	vertexBufferDESC.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
	vertexBufferData.pSysMem = v;

	HRESULT hr = m_pDevice->m_pDX11Device->CreateBuffer(&vertexBufferDESC, &vertexBufferData, &m_pVertexBuffer);

	return false;
}
