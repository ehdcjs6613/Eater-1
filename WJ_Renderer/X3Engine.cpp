//#include <wrl/client.h>

#include <afxdlgs.h>

#include "OneCompile.h"
#include "EngineData.h"
#include "Effects.h"
#include "InputLayout.h"
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
//#include "../DirectX2DSupporter/Grahpics2D.h"
#include "ParserData.h"
#include "ResourcesData.h"
#include "CBox.h"
#include "../Physics/Collider.h"
#include "../Physics/BoxCollider.h"
#include "../Physics/SphereCollider.h"
#include "../EditorLib/LibDefine.h"
//#include "../EditorLib/DockableView.h"
#include "../EditorLib/EDDockableBase.h"
#include "../EditorLib/ColliderExporter.h"
#include "../Editor/MainFrm.h"
#include "../Editor/Editor.h"

#include "X3Engine.h"


//����Ʈ������ ��Ŭ����

/*
	
*/
// �ʱ�ȭ �κ�.
X3Engine::X3Engine() : 
	m_pDevice(nullptr), 
	m_pDeviceContext(nullptr) , 
	m_ArrColor{ 0.5f, 0.5f, 0.35f, 1.0f },
	//m_XVertexShader{},
	//m_XPexelShader{},
	//m_pVertexBuffer(nullptr),
	m_CBox(nullptr)
{

	//���� �κ�
	m_pDevice = new DirectXDevice();
	m_pDeviceContext = new DirectXDeviceContext();
	m_pSamplerState = new DirectXSamplerState();
	
	m_pRasterizerState = new DirectXRasterizerState();
	m_pRasterizerSolid = new DirectXRasterizerState();
	m_pRasterizerWire = new DirectXRasterizerState();
	m_pAdapter = new DirectXAdapter();
	m_pRenderTargeter = new DirectXRenderTargeter();
	m_CBox = new CBox();
	m_BoxCollider0 = new BoxCollider();
	m_BoxCollider1 = new BoxCollider();
	m_BoxCollider2 = new BoxCollider();
	//m_SphereCollider = new SphereCollider();
	m_ColliderExporter = new ColliderExporter();

	this->m_pDirectXSwapChain = new DirectXSwapChain(m_pDevice->GetDevice());
	
	
	DirectX::XMFLOAT4X4 tWorld0;
	
	tWorld0 =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		-10,0,0,1,
	};
	DirectX::XMMATRIX r = DirectX::XMLoadFloat4x4(&tWorld0);
	//DirectX::XMStoreFloat4x4(&tWorld0, r);
	m_BoxCollider0->Translastion(r);
	//--------------------------------------------
	DirectX::XMFLOAT4X4 tWorld1;
	tWorld1 =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		-5,0,0,1,
	};
	DirectX::XMMATRIX r2 = DirectX::XMLoadFloat4x4(&tWorld1);
	//DirectX::XMStoreFloat4x4(&tWorld1, r2);
	m_BoxCollider1->Translastion(r2);

	DirectX::XMFLOAT4X4 tWorld2;
	tWorld2 =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		5,0,0,1,
	};
	DirectX::XMMATRIX r3 = DirectX::XMLoadFloat4x4(&tWorld2);
	//DirectX::XMStoreFloat4x4(&tWorld1, r2);
	m_BoxCollider1->Translastion(r3);

	m_BoxColliders.push_back(m_BoxCollider0);
	m_BoxColliders.push_back(m_BoxCollider1);
	m_BoxColliders.push_back(m_BoxCollider2);

}

X3Engine::~X3Engine()
{

}

void X3Engine::Initialize(HWND _hWnd, int _iWidth, int _iHeight)
{

	///������ ������ �ʴ´�.
#pragma region ������ ������ �ʴ´�
	m_hWnd = _hWnd;
	m_pDevice->CreateSize(_iWidth, _iHeight);
		//����۸� ��ȯ�Ͽ� ���丮�� �ʱ�ȭ�մϴ�.
	ID3D11Texture2D* backBufferPtr = m_pDevice->CreateInitFactory(m_videoCardMemory);
	//����ü���� �ʱ�ȭ ���ݴϴ�.
	DXGI_SWAP_CHAIN_DESC swapChainDesc(m_pDevice->CreateInitSwapChain(m_hWnd));

	// Set the feature level to DirectX 11.
	// ���� ������ DirectX 11�� ����
	// ����ü���� ����� �ݴϴ�.
	m_pDirectXSwapChain->MakeASwapChain(m_pDevice->GetDevice(), m_pDeviceContext->GetDeviceContext(), swapChainDesc);

	///���� = (����)

	//���� Ÿ���� ������ݴϴ�.
	m_pRenderTargeter->Create(m_pDevice->GetDevice(), m_pDirectXSwapChain->GetSwapChain());
	//����̽��� �������۸� ������ݴϴ�.
	m_pDevice->CreateDepthBuffer(m_pDepthStencil_Buffer);
	m_pDevice->CreateDepthStencilState(m_pDeviceContext->GetDeviceContext(), m_pDepthStencil_State);
	//�������ٽ� �並 ���� ���ǵ��� �־��ݴϴ�.
	m_pDevice->CreateDepthStencilView
	(
		m_pDeviceContext->GetDeviceContext(),
		m_pDepthStencil_View,
		m_pDepthStencil_Buffer,
		m_pRenderTargeter->m_pRenderTarget
	);
	//�����Ͷ������� ������ݴϴ�.
	m_pDevice->CreateResterize(m_pDeviceContext->GetDeviceContext(), m_pRasterizerState->GetFrameRS());
	//����Ʈ�� ������ݴϴ�.

	(m_ViewPort) = m_pDevice->CreateViewPort(m_pDeviceContext->GetDeviceContext());
	//���÷� ������Ʈ�� ������ݴϴ�.
	m_pSamplerState->CreateDXSamplerState(m_pDevice->GetDevice());

	///


	// Render State
	CreateRenderState();

	// ����� ������ ��´�.
	m_pAdapter->GetAdapter();

	m_pAdapter->GetAdapterInfo();



	if (nullptr == m_pDirectXSwapChain->GetSwapChain())
	{

	}
	
	InitializeShaders();
#pragma endregion �����Ⱦ�.

}

Indexbuffer* X3Engine::CreateIndexBuffer(ParserData::Mesh* mModel)
{
	ID3D11Buffer* mIB = nullptr;
	Indexbuffer* indexbuffer = new Indexbuffer();

	//���� ���
	size_t ModelCount = (int)mModel->m_IndexList.size();
	size_t Icount = (int)mModel->m_IndexList.size();

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
	ibd.ByteWidth = sizeof(UINT) * (UINT)index.size();
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
	size_t Vcount = mModel->m_VertexList.size();

	std::vector<XVertexDef> temp;
	temp.resize(Vcount);
	for (int i = 0; i < Vcount; i++)
	{
		temp[i].Pos = mModel->m_VertexList[i]->m_Pos;
		temp[i].Nomal = mModel->m_VertexList[i]->m_Normal;
		temp[i].Tex =  mModel->m_VertexList[i]->m_UV;
		temp[i].Tangent = mModel->m_VertexList[i]->m_Tanget;
	}



	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(XVertexDef) * (UINT)Vcount;
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
}

void X3Engine::Delete()
{
}

void X3Engine::Render(std::queue<MeshData*>* meshList, GlobalData* global)
{
	CMainFrame* frm = (CMainFrame*)AfxGetMainWnd();
	DockableBase* dockB = frm->GetDockableBase();
	if (nullptr != frm->GetDockableBase())
	{
		frm->GetDockableBase()->Update();
	}
	//
	//if (frm->GetDockableBase() != nullptr)
	//{
	//	frm->GetDockableBase()->Update();
	//}

	static int num = -1;
	//0x09 HT: HORIZONTAB
	static int size = m_BoxColliders.size();
	if (GetAsyncKeyState(VK_RIGHT) & 8001)
	{
		
		if (num < size-1)
		{
			if (num  < 0)
			{
				num++;
				m_BoxColliders[num]->OnPick();
				m_BoxColliders[num]->Initialize();
			}
			else
			{
				m_BoxColliders[num]->OffPick();
				m_BoxColliders[num]->Initialize();
				num++;
			}
			
		
		}
		else if (num >= size)
		{
			return;
		}
		m_BoxColliders[num]->OnPick();
		m_BoxColliders[num]->Initialize();


	}
	else if (GetAsyncKeyState(VK_LEFT) & 8001)
	{
		
		if (num > 0)
		{
			m_BoxColliders[num]->OffPick();
			m_BoxColliders[num]->Initialize();
			--num;
		}
		else
		{
			return;
		}
		m_BoxColliders[num]->OnPick();
		m_BoxColliders[num]->Initialize();

	}

	
	if (nullptr != frm->GetDockableBase() && num!= -1)
	{
		

		m_BoxColliders[num]->GetWorld();
		tWorld0 =
		{
			frm->GetDockableBase()->xs, 0 , 0, 0,
			0, frm->GetDockableBase()->ys , 0, 0,
			0, 0 , frm->GetDockableBase()->zs, 0,
			frm->GetDockableBase()->xf, frm->GetDockableBase()->yf , frm->GetDockableBase()->zf, 1,
		};
		DirectX::XMMATRIX r = DirectX::XMLoadFloat4x4(&tWorld0);
		m_BoxColliders[num]->Translastion(r);
	}

	if (GetAsyncKeyState(VK_RETURN) & 8001)
	{
		//
		m_ColliderExporter->Start();

		int size = m_BoxColliders.size();
		for (auto k : m_BoxColliders)
		{
			
			m_ColliderExporter->PushInfo((k));
			m_ColliderExporter->Export((const wchar_t*)L"BoxCollider");
		}
		m_ColliderExporter->End();

	}
	
	//������������ ����.
	//���߿� ���� ť? �����ɷ� �غ���,
	m_pDeviceContext->GetDeviceContext()->RSSetViewports(1, &this->m_ViewPort);

	mView = DirectX::SimpleMath::Matrix(*global->mViewMX);
	mProj = DirectX::SimpleMath::Matrix(*global->mProj);

	//m_pViewGrid->Update(&mView, &mProj);

	m_CBox->Update(mView, mProj);
	m_CBox->Render(meshList);

	//m_BoxCollider->Update();
	////const DirectX::XMFLOAT4X4 _WorldTM = {  };

	//DirectX::XMMATRIX r = XMMatrixIdentity();
	//DirectX::XMFLOAT4X4 tWorld0;
	//DirectX::XMStoreFloat4x4(&tWorld0, r);

	for (auto k : m_BoxColliders)
	{
		//auto dc = (*k);
		(k)->Draw(mView, mProj);
		(k)->Rnder();
	}

	



	//
	////m_SphereCollider->Translasion(&r);
	//m_SphereCollider->Draw(mView, mProj);
	//m_SphereCollider->Rnder();

	//m_BoxCol->Update(mView, mProj);
	//m_BoxCol->Render(meshList);
	

	///2D������ ó��
	



}

void X3Engine::SetViewPort(void* VPT, int Change_Width, int Change_Height)
{
	(this->m_ViewPort) = *(D3D11_VIEWPORT*)VPT;
}

void X3Engine::SetDevice(void* Devie, void* DevieContext)
{
	m_pDevice->SetDevice(reinterpret_cast<ID3D11Device*>(Devie));
	m_pDeviceContext->SetDeviceContext(reinterpret_cast<ID3D11DeviceContext*>(DevieContext));

	//����������Ʈ�� �����Ѵ�.
	this->CreateRenderState();
	
	Effects::InitAll(m_pDevice->GetDevice());
	InputLayouts::InitAll(m_pDevice->GetDevice());

	m_CBox->Initialize(m_pDevice->GetDevice(), m_pDeviceContext->GetDeviceContext());
	m_BoxCollider0->Initialize(m_pDevice->GetDevice(), m_pDeviceContext->GetDeviceContext());
	m_BoxCollider1->Initialize(m_pDevice->GetDevice(), m_pDeviceContext->GetDeviceContext());
	m_BoxCollider2->Initialize(m_pDevice->GetDevice(), m_pDeviceContext->GetDeviceContext());
	//m_SphereCollider->Initialize(m_pDevice->GetDevice(), m_pDeviceContext->GetDeviceContext());

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

	//���� �� �ڵ�(hlsl ���̴� �ʱ�ȭ �Լ�)�� ������� �ʴ´�.
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

	
	//UINT numElements = ARRAYSIZE(layout, numElements);
	UINT numElements = ARRAYSIZE(layout);

	//if (0 != m_XVertexShader.Initialize(m_pDevice->GetDevice(), shaderFoler + L"vertexShaders.cso", layout, numElements))
	//{
	//	return;
	//}
	//if (0 != m_XPexelShader.Initialize(m_pDevice->GetDevice(), shaderFoler + L"pixelShaders.cso", layout, numElements))
	//{
	//	return;
	//}
}


HRESULT X3Engine::BeginRender()
{
	HRESULT hr = S_OK;

	
	return hr;
}

HRESULT X3Engine::LoopRender()
{
	HRESULT hr = S_OK;

	return hr;
}

HRESULT X3Engine::EndRender()
{
	HRESULT hr = S_OK;
	//m_pGrahpics2D->Draw_AllText();
	//m_pGrahpics2D->Draw_AllImage();
	//m_pGrahpics2D->Draw_AllSprite();

	return hr;
}


