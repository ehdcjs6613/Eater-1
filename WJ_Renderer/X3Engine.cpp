//#include <wrl/client.h>
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
#include "../DirectX2DSupporter/Grahpics2D.h"
#include "ParserData.h"
#include "ResourcesData.h"
#include "CBox.h"
#include "X3Engine.h"
//����Ʈ������ ��Ŭ����

/*
	
*/
// �ʱ�ȭ �κ�.
X3Engine::X3Engine() : 
	m_pDevice(nullptr), 
	m_pDeviceContext(nullptr) , 
	m_ArrColor{ 0.5f, 0.5f, 0.35f, 1.0f },
	m_XVertexShader{},
	m_XPexelShader{},
	m_pVertexBuffer(nullptr),
	m_CBox(nullptr)
	//mWorld{},
	//mView{},
	//mProj{},
	//m_FX(nullptr),
	//mTech(nullptr),
	//mfxWorldViewProj(nullptr),
	//mInputLayout(nullptr),
	//NormalDSS(nullptr)
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

	this->m_pDirectXSwapChain = new DirectXSwapChain(m_pDevice->GetDevice());

	
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
	m_pDeviceContext->GetDeviceContext()->RSSetViewports(1, &this->m_ViewPort);

	mView = DirectX::SimpleMath::Matrix(*global->mViewMX);
	mProj = DirectX::SimpleMath::Matrix(*global->mProj);

	//m_pViewGrid->Update(&mView, &mProj);

	m_CBox->Update(mView, mProj);
	m_CBox->Render(meshList);


	//while (!meshList->empty())
	//{
	//	// �޽� �����͸� �ϳ� ������.
	//	MeshData* _Mesh_Data = meshList->front();
	//
	//	/// ������Ʈ���� �׸���. (Draw Primitive)
	//	if (_Mesh_Data->ObjType != OBJECT_TYPE::BASE)
	//	{
	//		meshList->pop();
	//		continue;
	//	}
	//
	//	// �ش� �޽��� VB,IB �� �޾ƿ�.
	//	Render_VB = reinterpret_cast<ID3D11Buffer*>(_Mesh_Data->VB->VertexbufferPointer);
	//	Render_IB = reinterpret_cast<ID3D11Buffer*>(_Mesh_Data->IB->IndexBufferPointer);
	//
	//	// �Ž� �ؽ��� �������� ĳ�����ؼ� �װ� �ؿ� ����Ʈ�� ������ ���ð���
	//	//_Mesh_Data->Diffuse->TextureBufferPointer;
	//	
	//	// �Է� ��ġ ��ü ����
	//	m_pDeviceContext->GetDeviceContext()->IASetInputLayout(InputLayouts::PosNormalTexBiNormalTangent);
	//	m_pDeviceContext->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//
	//	// ���ؽ����ۿ� �ε������� ����
	//	Vertex_Buffer_Stride = _Mesh_Data->VB->VertexDataSize;
	//	Vertex_Buffer_Offset = 0;
	//
	//	/// WVP TM���� ����
	//	mWorld = _Mesh_Data->mWorld;//_Mesh_Data->mWorld;
	//	//mWorld = DirectX::SimpleMath::Matrix();
	//	Mul_WVP = mWorld * mView * mProj;
	//
	//	// ������ �����
	//	World_Inverse = mWorld.Invert();
	//
	//	// Set per frame constants.
	//	DirectionalLight _temp_Dir;
	//	DirectX::SimpleMath::Vector4 _Ambient = DirectX::SimpleMath::Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	//	DirectX::SimpleMath::Vector4 _Diffuse = DirectX::SimpleMath::Vector4(0.5f, 0.5f, 0.5f, 1.0f);
	//	DirectX::SimpleMath::Vector4 _Specular = DirectX::SimpleMath::Vector4(0.5f, 0.5f, 0.5f, 1.0f);
	//	DirectX::SimpleMath::Vector3 _Direction = DirectX::SimpleMath::Vector3(-0.57735f, -0.57735f, 0.57735f);
	//	_temp_Dir.Ambient = _Ambient;
	//	_temp_Dir.Diffuse = _Diffuse;
	//	_temp_Dir.Specular = _Specular;
	//	_temp_Dir.Direction = _Direction;
	//
	//	Material _Temp_Mat;
	//	DirectX::SimpleMath::Vector4 _Ambient1 = DirectX::SimpleMath::Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	//	DirectX::SimpleMath::Vector4 _Diffuse1 = DirectX::SimpleMath::Vector4(0.5f, 0.5f, 0.5f, 1.0f);
	//	DirectX::SimpleMath::Vector4 _Specular1 = DirectX::SimpleMath::Vector4(0.5f, 0.5f, 0.5f, 1.0f);
	//	DirectX::SimpleMath::Vector4 _Reflect1 = DirectX::SimpleMath::Vector4(0.5f, 0.5f, 0.5f, 1.0f);
	//	_Temp_Mat.Ambient = _Ambient1;
	//	_Temp_Mat.Diffuse = _Diffuse1;
	//	_Temp_Mat.Specular = _Specular1;
	//	_Temp_Mat.Reflect = _Reflect1;
	//
	//
	//	Effects::BasicTextureFX->SetDirLights(&_temp_Dir);
	//
	//	// ���� Eye ������.
	//	DirectX::SimpleMath::Vector3 _Camera_Vec(mView._41, mView._42, mView._43);
	//	Effects::BasicTextureFX->SetEyePosW(_Camera_Vec);
	//
	//	ID3DX11EffectTechnique* mTech = nullptr;
	//
	//	/// �ؽ��� ���
	//	//mTech = Effects::BasicFX->Light1Tech;
	//	/// �ؽ��� �̻��
	//	mTech = Effects::BasicTextureFX->Light1TexTech;
	//
	//	D3DX11_TECHNIQUE_DESC techDesc;
	//	mTech->GetDesc(&techDesc);
	//
	//	for (UINT p = 0; p < techDesc.Passes; ++p)
	//	{
	//		
	//		m_pDeviceContext->GetDeviceContext()->IASetVertexBuffers(0, 1, &Render_VB, &Vertex_Buffer_Stride, &Vertex_Buffer_Offset);
	//		m_pDeviceContext->GetDeviceContext()->IASetIndexBuffer(Render_IB, DXGI_FORMAT_R32_UINT, 0);
	//
	//		World_Inverse_Transpose = MathHelper::InverseTranspose(mWorld);
	//		Effects::BasicTextureFX->SetWorld(mWorld);
	//		Effects::BasicTextureFX->SetWorldInvTranspose(World_Inverse_Transpose);
	//		Effects::BasicTextureFX->SetWorldViewProj(Mul_WVP);
	//		Effects::BasicTextureFX->SetMaterial(_Temp_Mat);
	//		Effects::BasicTextureFX->SetTexTransform(DirectX::SimpleMath::Matrix::Identity);
	//		Effects::BasicTextureFX->SetDiffuseMap((ID3D11ShaderResourceView*)(_Mesh_Data->Diffuse->TextureBufferPointer));
	//
	//		mTech->GetPassByIndex(p)->Apply(0, m_pDeviceContext->GetDeviceContext());
	//		m_pDeviceContext->GetDeviceContext()->DrawIndexed(_Mesh_Data->IB->Count, 0, 0);
	//	}
	//	meshList->pop();
	//
	//}

	//m_pViewGrid->Render();

	//BeginRender();
	//LoopRender();
	//EndRender();

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


