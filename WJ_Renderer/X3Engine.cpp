#include <wrl/client.h>

#include "OneCompile.h"
#include "d3dx11effect.h"
#include "WICTextureLoader.h"
#include "XVertex.h"
#include "DirectXDefine.h"
#include "DirectXDevice.h"
#include "DirectXDeviceContext.h"
#include "DirectXSwapChain.h"
#include "DirectXRasterizerState.h"
#include "DirectXAdapter.h"
#include "DirectXRenderTargeter.h"
#include "DirectXSamplerState.h"
#include "XRenderer.h"
#include "ParserData.h"
//#include "Grahpics2D.h"
#include "ResourcesData.h"
#include "ViewGrid.h"
#include "X3Engine.h"
//����Ʈ������ ��Ŭ����

// �ʱ�ȭ �κ�.
X3Engine::X3Engine() : m_pDevice(nullptr), m_pDeviceContext(nullptr) , m_ArrColor{ 0.5f, 0.5f, 0.35f, 1.0f }
{

	//���� �κ�
	m_pDevice = new DirectXDevice();
	m_pDeviceContext = new DirectXDeviceContext();
	
	//m_pRenderer->m_pDirectXSwapChain = new DirectXSwapChain(m_pDevice->m_pDX11Device);
	m_pRasterizerState = new DirectXRasterizerState();
	m_pRasterizerSolid = new DirectXRasterizerState();
	m_pRasterizerWire = new DirectXRasterizerState();
	m_pAdapter = new DirectXAdapter();
	m_pRenderTargeter = new DirectXRenderTargeter();
	this->m_pDirectXSwapChain = new DirectXSwapChain(m_pDevice->GetDevice());
	//m_p2DSupport = new Grahpics2D();


}

X3Engine::~X3Engine()
{

}

void X3Engine::Initialize(HWND _hWnd, int _iWidth, int _iHeight)
{
	m_hWnd = _hWnd;
	m_pDevice->CreateSize(_iWidth, _iHeight);

	//����۸� ��ȯ�Ͽ� ���丮�� �ʱ�ȭ�մϴ�.
	ID3D11Texture2D* backBufferPtr = m_pDevice->CreateInitFactory(m_videoCardMemory);
	//����ü���� �ʱ�ȭ ���ݴϴ�.
	DXGI_SWAP_CHAIN_DESC swapChainDesc(m_pDevice->CreateInitSwapChain(m_hWnd));

	// Set the feature level to DirectX 11.
	// ���� ������ DirectX 11�� ����
	// ����ü���� ����� �ݴϴ�.
	m_pDirectXSwapChain->MakeASwapChain(m_pDevice->GetDevice(),m_pDeviceContext->GetDeviceContext(),swapChainDesc);

	///���� = (����)

	//���� Ÿ���� ������ݴϴ�.
	m_pRenderTargeter->Create(m_pDevice->GetDevice(),m_pDirectXSwapChain->GetSwapChain());
	//����̽��� �������۸� ������ݴϴ�.
	m_pDevice->CreateDepthBuffer(m_pDepthStencil_Buffer);
	m_pDevice->CreateDepthStencilState(m_pDeviceContext->GetDeviceContext(),m_pDepthStencil_State);
	//�������ٽ� �並 ���� ���ǵ��� �־��ݴϴ�.
	m_pDevice->CreateDepthStencilView
	(
		m_pDeviceContext->GetDeviceContext(),
		m_pDepthStencil_View,
		m_pDepthStencil_Buffer,
		m_pRenderTargeter->m_pRenderTarget
	);
	//�����Ͷ������� ������ݴϴ�.
	m_pDevice->CreateResterize(	m_pDeviceContext->GetDeviceContext(),m_pRasterizerState->GetFrameRS());
	//����Ʈ�� ������ݴϴ�.
	m_pDevice->CreateViewPort(m_pDeviceContext->GetDeviceContext());
	//���÷� ������Ʈ�� ������ݴϴ�.
	m_pSamplerState->CreateDXSamplerState(m_pDevice->GetDevice());

	///


	// Render State
	CreateRenderState();

	// ����� ������ ��´�.
	m_pAdapter->GetAdapter();

	m_pAdapter->GetAdapterInfo();


	//m_p2DSupport->initialize(m_hWnd, m_pRenderer->m_pDirectXSwapChain->m_pSwapChain);
	//m_p2DSupport->LoadBitMap(L"../Image/apple_1.png", L"../Image/apple_1.png");
	//m_p2DSupport->LoadBitMap(L"../Image/atk_1.png", L"../Image/atk_1.png");

	if (nullptr == m_pDirectXSwapChain->GetSwapChain())
	{

	}
	InitializeShaders();
	ViewGrid* m_pViewGrid = new ViewGrid();
	m_pViewGrid->Initialize(m_pDevice->GetDevice(), m_pDeviceContext->GetDeviceContext(), m_pRasterizerWire->GetFrameRS());
	

	//OnReSize(this->m_iWidth, m_iHeight);
}

Indexbuffer* X3Engine::CreateIndexBuffer(ParserData::Mesh* mModel)
{
	ID3D11Buffer* mIB = nullptr;
	Indexbuffer* indexbuffer = new Indexbuffer();

	//���� ���
	int ModelCount = (int)mModel->m_IndexList.size();
	int Icount = (int)mModel->m_IndexList.size();

	std::vector<UINT> index;
	index.resize(Icount * 3);

	int j = 0;
	for (int i = 0; i < Icount; i++)
	{
		index[j] = mModel->m_IndexList[i]->m_Index[0];
		j++;
		index[j] = mModel->m_IndexList[i]->m_Index[1];
		j++;
		index[j] = mModel->m_IndexList[i]->m_Index[2];
		j++;
	}


	//�ε��� ���۸� �����Ѵ�
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * index.size();
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &index[0];
	m_pDevice->GetDevice()->CreateBuffer(&ibd, &iinitData, &mIB);

	//�ε������۸� �������ֵ��� ����
	indexbuffer->IndexBufferPointer = mIB;
	//indexbuffer->size = sizeof(ID3D11Buffer);

	return indexbuffer;
}

Vertexbuffer* X3Engine::CreateVertexBuffer(ParserData::Mesh* mModel)
{
	ID3D11Buffer* mVB = nullptr;
	Vertexbuffer* vertexbuffer = new Vertexbuffer();



	//���� ���
	int Vcount = mModel->m_VertexList.size();
	mModel->m_VertexList;


	std::vector<XVertexDef> temp;
	temp.resize(Vcount);
	for (int i = 0; i < Vcount; i++)
	{
		temp[i].Pos = mModel->m_VertexList[i]->m_Pos;
		temp[i].Nomal = mModel->m_VertexList[i]->m_Normal;
		temp[i].Tex = { mModel->m_VertexList[i]->m_U ,mModel->m_VertexList[i]->m_V };
		temp[i].Tangent = mModel->m_VertexList[i]->m_Tanget;
	}



	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(XVertexDef) * Vcount;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &temp[0];
	m_pDevice->GetDevice()->CreateBuffer(&vbd, &vinitData, &mVB);


	vertexbuffer->VertexbufferPointer = mVB;
	//vertexbuffer->size = sizeof(ID3D11Buffer);

	return vertexbuffer;
}

TextureBuffer* X3Engine::CreateTextureBuffer(std::string path)
{
	// string to wstring
	std::wstring W_Path;
	W_Path.assign(path.begin(), path.end());

	TextureBuffer* _TextureBuffer = new TextureBuffer();

	// �ؽ��� ������ ���� �ӽ� ��ü
	ID3D11Resource* Texture_Resource = nullptr;
	// �ؽ��� SRV
	ID3D11ShaderResourceView* DX11_SRV = nullptr;
	// �ؽ��� ���� ����.
	DirectX::CreateWICTextureFromFile(m_pDevice->GetDevice(), W_Path.c_str(), &Texture_Resource, &DX11_SRV);
	ReleaseCOM(Texture_Resource);

	_TextureBuffer->TextureBufferPointer = _TextureBuffer;

	return _TextureBuffer;
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
	
	BeginRender();
	LoopRender();
	EndRender();

	///2D������ ó��
	//m_pRenderer->Render_2D(m_p2DSupport, this->m_pAdapter);
	//m_pRenderer->Render_End(m_p2DSupport,m_pRenderer->m_pDirectXSwapChain->m_pSwapChain);


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

	/// ============================ ���̴��� �ʱ�ȭ �κ� ===================================== //
	/*
	// Color Shader

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0,DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,0,0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,0 } ,
		{ "COLOR",		0,DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,0 } ,
	};
	*/
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0,DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT,0,0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,0 } ,
		{ "TEXCOORD",	0,DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA,0 } ,
	};


	UINT numElements = ARRAYSIZE(layout, numElements);

	if (0 != m_XVertexShader.Initialize(m_pDevice->GetDevice(), shaderFoler + L"vertexShaders.cso", layout, numElements))
	{
		return;
	}
	if (0 != m_XPexelShader.Initialize(m_pDevice->GetDevice(), shaderFoler + L"pixelShaders.cso", layout, numElements))
	{
		return;
	}
}


HRESULT X3Engine::BeginRender()
{
	HRESULT hr = S_OK;

	//����Ÿ�� (�����)�� �ʱ�ȭ�Ѵ�.
	m_pDeviceContext->GetDeviceContext()->ClearRenderTargetView(m_pRenderTargeter->m_pRenderTarget, this->m_ArrColor);

	//����, ���ٽ� ���ʱ�ȭ
	m_pDeviceContext->GetDeviceContext()->ClearDepthStencilView
	(
		this->m_pDepthStencil_View,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0
	);
	m_pDeviceContext->GetDeviceContext()->OMSetRenderTargets(1, &m_pRenderTargeter->m_pRenderTarget, m_pDepthStencil_View);


	//m_pDeviceContext->GetDeviceContext()->RSSetState(m_pRasterizerState->GetFrameRS());
	m_pDeviceContext->GetDeviceContext()->RSSetState(m_pRasterizerState->GetFrameRS());
	m_pDeviceContext->GetDeviceContext()->OMSetDepthStencilState(m_pDepthStencil_State, 0);
	m_pDeviceContext->GetDeviceContext()->PSSetSamplers(0, 1, &m_pSamplerState->m_pSamplerState);

	return hr;
}

HRESULT X3Engine::LoopRender()
{
	HRESULT hr = S_OK;

	/// ��å ���� - ������ǥ�踦 īƼ���� ��ǥ��� �ٲ۴�.
	DirectX::XMMATRIX I = DirectX::XMMatrixIdentity();
	DirectX::XMStoreFloat4x4(&mWorld, I);
	DirectX::XMStoreFloat4x4(&mView, I);
	DirectX::XMStoreFloat4x4(&mProj, I);

	/// WVP TM���� ����
	// Set constants
	DirectX::XMMATRIX world = DirectX::XMLoadFloat4x4(&mWorld);
	DirectX::XMMATRIX view = DirectX::XMLoadFloat4x4(&mView);
	DirectX::XMMATRIX proj = DirectX::XMLoadFloat4x4(&mProj);

	m_pViewGrid->Update(world, view, proj);

	/// ī�޶� ����� ��
	//m_pCamera->UpdateViewMatrix();
	//view = m_pCamera->View();
	//proj = m_pCamera->Proj();

	// ��� ���� ������ ���ؼ� ������������� ����� �������ش�. (��ü�� ĳ�ø� �ٲٴ� ���̸� GPU�� ������۰� �ٷ� ���ŵǴ� ���� �ƴϴ�.)
	DirectX::XMMATRIX worldViewProj = world * view * proj;
	mfxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

	///----------------------------------------------------------------------------------------------------
	/// ������Ʈ���� �׸���. (Draw Primitive)

	//-----
	// ��å ���� (�簢��)

	// �Է� ��ġ ��ü ����
	m_pDeviceContext->GetDeviceContext()->IASetInputLayout(mInputLayout);
	m_pDeviceContext->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pDeviceContext->GetDeviceContext()->OMSetDepthStencilState(NormalDSS, 0);

	m_pViewGrid->Render();

	return hr;
}

HRESULT X3Engine::EndRender()
{
	HRESULT hr = S_OK;
	return hr;
}


