#include "OneCompile.h"
#include "DDSTextureLoader11.h"
#include "DirectXDefine.h"
#include "DirectXDevice.h"
#include "DirectXDeviceContext.h"
#include "DirectXSwapChain.h"
#include "DirectXRasterizerState.h"
#include "DirectXAdapter.h"
#include "DirectXRenderTargeter.h"

#include "SharedData.h"
#include "XRenderer.h"
#include "EngineData.h"
#include "X3Engine.h"
#include "Grahpics2D.h"


// 초기화 부분.
X3Engine::X3Engine() : m_pDevice(nullptr), m_pDeviceContext(nullptr) 
{

	//생성 부분
	m_pDevice = new DirectXDevice();
	m_pDeviceContext = new DirectXDeviceContext();
	m_pRenderer = new XRenderer();
	//m_pRenderer->m_pDirectXSwapChain = new DirectXSwapChain(m_pDevice->m_pDX11Device);
	m_pRasterizerState = new DirectXRasterizerState();
	m_pRasterizerSolid = new DirectXRasterizerState();
	m_pRasterizerWire = new DirectXRasterizerState();
	m_pAdapter = new DirectXAdapter();
	m_pGraphics2D = new Grahpics2D();
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
	// 형상 레벨을 DirectX 11로 설정
	m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;
	m_pRenderer->Render_Initialize(m_pDevice->m_pDX11Device);

	// 스왑 체인과 Device를 같이 생성. (D2D를 지원하기 위해 옵션으로 BGRA 를 셋팅 해 두었다.)
	D3D11CreateDeviceAndSwapChain
	(
		NULL, D3D_DRIVER_TYPE_HARDWARE, 
		NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		&m_FeatureLevel, 1,
		D3D11_SDK_VERSION, 
		&swapChainDesc, 
		&m_pGraphics2D->m_3D_SwapChain,
		&m_pDevice->m_pDX11Device,
		NULL,
		&m_pDeviceContext->m_pDX11DeviceContext
	);

	// Get the pointer to the back buffer.
	//포인터를 뒤쪽 버퍼로 가져갑니다.

	m_pRenderer->m_pRenderTargeter->Create(m_pDevice->m_pDX11Device, m_pGraphics2D->m_3D_SwapChain);

	m_pDevice->CreateDepthBuffer(m_pRenderer->m_pDepthStencil_Buffer);
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
	m_pDevice->CreateResterize(m_pDeviceContext->m_pDX11DeviceContext, m_pRasterizerState->m_pFrameRS);
	m_pDevice->CreateViewPort(m_pDeviceContext->m_pDX11DeviceContext);

	///

	
	// Render State
	CreateRenderState();

	// 어댑터 정보를 얻는다.
	m_pAdapter->GetAdapter();

	m_pAdapter->GetAdapterInfo();

	
	m_pGraphics2D->initialize(m_hWnd, m_pGraphics2D->m_3D_SwapChain);
	if (nullptr == m_pGraphics2D->m_3D_SwapChain)
	{
		std::cout << "ㅅㅂ" << std::endl;
	}
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
	/// 바뀐 화면의 사이즈를 저장해 준뒤에
	m_pDevice->GetWidth();
	m_pDevice->GetHeight();
	/// 화면을 나타내는 예전의 view를 삭제하고 현재것으로 새로 생성한다.
	

	/// 재구성 하는데 필요한 정보들 => 랜더타겟의 뷰, 스탠실 뷰,버퍼
	m_pRenderer->GetRenderTargetView()[0].Release();
	ReleaseCOM(m_pRenderer->m_pDepthStencil_View);
	ReleaseCOM(m_pRenderer->m_pDepthStencil_Buffer);

	HR(m_pRenderer->m_pDirectXSwapChain->m_pSwapChain->ResizeBuffers(1, m_pDevice->GetWidth(), m_pDevice->GetHeight(), DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	ID3D11Texture2D* backBuffer;
	HR(m_pRenderer->m_pDirectXSwapChain->m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));
	HR(m_pDevice->m_pDX11Device->CreateRenderTargetView(backBuffer, 0, &m_pRenderer->m_pRenderTargeter->m_pRenderTarget));
	ReleaseCOM(backBuffer);

	// Create the depth/stencil buffer and view.

	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = m_pDevice->GetWidth();
	depthStencilDesc.Height = m_pDevice->GetHeight();
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	/// 4X MSAA 모드를 사용하지 않음.
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;

	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	/// 스탠실 Desc를 기반으로 하여 스탠실 버퍼와 뷰를 재생성한다.
	HR(m_pDevice->m_pDX11Device->CreateTexture2D
	(
		&depthStencilDesc, 
		0,
		&m_pRenderer->m_pDepthStencil_Buffer)
	);
	if (nullptr == m_pRenderer->m_pDepthStencil_Buffer){	return;	}

	HR(m_pDevice->m_pDX11Device->CreateDepthStencilView
	(
		m_pRenderer->m_pDepthStencil_Buffer, 
		0, &m_pRenderer->m_pDepthStencil_View)
	);


	/// 렌더타겟뷰, 뎁스/스탠실뷰를 파이프라인에 바인딩한다.
	m_pDeviceContext->m_pDX11DeviceContext->OMSetRenderTargets
	(
		1,
		&m_pRenderer->m_pRenderTargeter->m_pRenderTarget,		//장치에 바인딩할 렌더 대상을 나타내는		  렌더타겟
		m_pRenderer->m_pDepthStencil_View		//장치에 바인딩할 깊이 스텐실 보기를 나타내는 스텐실 뷰
	);


	// Set the viewport transform.
	/// 뷰포트 변환을 셋팅한다.
	m_pRenderer->m_D3D11_ViewPort[0].TopLeftX = 0;
	m_pRenderer->m_D3D11_ViewPort[0].TopLeftY = 0;
	m_pRenderer->m_D3D11_ViewPort[0].Width = static_cast<float>(m_pDevice->GetWidth());
	m_pRenderer->m_D3D11_ViewPort[0].Height = static_cast<float>(m_pDevice->GetHeight());
	m_pRenderer->m_D3D11_ViewPort[0].MinDepth = 0.0f;
	m_pRenderer->m_D3D11_ViewPort[0].MaxDepth = 1.0f;

	m_pDeviceContext->m_pDX11DeviceContext->RSSetViewports(1, &m_pRenderer->m_D3D11_ViewPort[0]);

}

void X3Engine::Delete()
{
}

void X3Engine::Render(std::queue<MeshData*>* meshList, GlobalData* global)
{
	//렌더링시작의 순서.
	//나중에 렌더 큐? 같은걸로 해보자,
	m_pRenderer->Render_Begin(m_pDeviceContext->m_pDX11DeviceContext);
	
	m_pRenderer->Render_Update(m_pDeviceContext->m_pDX11DeviceContext);

	m_pRenderer->Render_LateUpdate(m_pDeviceContext->m_pDX11DeviceContext);
	m_pRenderer->Render_2D(m_pGraphics2D,this->m_pAdapter);

	m_pRenderer->Render_End(m_pGraphics2D->m_3D_SwapChain);

	

	

}

void X3Engine::CreateRenderState()
{
	this->m_pRasterizerSolid->Create(this->m_pDevice->GetDevice(), StateRS::eSolid);
	this->m_pRasterizerWire->Create(this->m_pDevice->GetDevice(), StateRS::eWireFrame);
}

void X3Engine::DrawSystemStatus()
{
	// 피쳐레벨
	
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
