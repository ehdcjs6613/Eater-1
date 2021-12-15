
#include "VertexPositionColor.h"
#include "GameObject.h"
#include "Transform.h"
#include "BoxCollider.h"
#include <DirectXMath.h>


BoxCollider::BoxCollider() 
{
	m_Num =(1);

	DirectX::XMMATRIX i =  DirectX::XMMatrixIdentity();
	XMStoreFloat4x4(&this->mWorld, i);
	
	//Hight
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Awake()
{

}

void BoxCollider::Start()
{

}

void BoxCollider::StartUpdate()
{
}

void BoxCollider::TransformUpdate()
{
}

void BoxCollider::PhysicsUpdate()
{
	CalculateOBB();
	CalculateAABB();
}

void BoxCollider::Update()
{
}

void BoxCollider::EndUpdate()
{
}
void BoxCollider::Translasion(DirectX::XMMATRIX* _World)
{
	if (!this)
	{
		return;
	}
	 DirectX::XMStoreFloat4x4(&this->mWorld ,*_World);
	
	
}

void BoxCollider::Draw(const DirectX::XMFLOAT4X4 _View, const DirectX::XMFLOAT4X4 _Proj)
{
	

	this->gameobject;
	//요기수정
	mView = (_View);
	mProj = (_Proj);

	// 입력 배치 객체 셋팅
	md3dImmediateContext->IASetInputLayout(m_Gemetry.m_pInputLayout);
	md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	//D3D11_PRIMITIVE_TOPOLOGY_LINELIST

// 인덱스버퍼와 버텍스버퍼 셋팅
	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;
	md3dImmediateContext->IASetVertexBuffers(0, 1, &m_Gemetry.m_pVertexBuffer, &stride, &offset);
	md3dImmediateContext->IASetIndexBuffer(m_Gemetry.m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	/// WVP TM등을 셋팅

	if (GetAsyncKeyState(VK_UP) & 8001)
	{
		Center[0] += 0.1f;
	}
	if (GetAsyncKeyState(VK_DOWN) & 8001)
	{
		Center[1] += 0.1f;
	}
	if (GetAsyncKeyState(VK_LEFT) & 8001)
	{
		Center[2] += 0.1f;
	}

	if (GetAsyncKeyState('1') & 8001)
	{
		Size[0] -= 0.1f;
	}
	if (GetAsyncKeyState('2') & 8001)
	{
		Size[1] -= 0.1f;
	}
	if (GetAsyncKeyState('3') & 8001)
	{
		Size[2] -= 0.1f;
	}



	DirectX::XMMATRIX view = DirectX::XMLoadFloat4x4(&mView);
	DirectX::XMMATRIX proj = DirectX::XMLoadFloat4x4(&mProj);
	DirectX::XMMATRIX world = DirectX::XMLoadFloat4x4(&mWorld);

	Center[0] = 0;
	Center[1] = 1;
	Center[2] = 0;

	world =
	{
		Size[0]		,0		,0		,0,
		0,		Size[1]		,0		,0,
		0,			 0,		Size[2]	,0,
		Center[0],Center[1],Center[2],1,
	};

	DirectX::XMMATRIX worldViewProj = world * view * proj;
	m_Gemetry.m_pFxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));


	//mWorld =
	//{
	//	1,0,0,0,
	//	0,1,0,0,
	//	0,0,1,0,
	//	0,0,0,1,
	//};

	// 렌더스테이트
	//md3dImmediateContext->RSSetState(m_pRenderstate);

	// 테크닉은...
	D3DX11_TECHNIQUE_DESC techDesc;
	m_Gemetry.m_pTech->GetDesc(&techDesc);

	// 렌더패스는...
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		m_Gemetry.m_pTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);

		// 36개의 인덱스로 축을 그린다.
		md3dImmediateContext->DrawIndexed(36, 0, 0);
	}

}

void BoxCollider::Rnder()
{
	

	
}



void BoxCollider::CalculateOBB()
{

}

void BoxCollider::CalculateAABB()
{
	
}

void BoxCollider::Initialize()
{
	m_Gemetry.CreateLineMesh(md3dDevice, GeometryGenerator::MeshType::Box);
	//m_Gemetry.CreateBulildFX(md3dDevice);
	//m_Gemetry.CreateBulildInputLayout(md3dDevice);
}

void BoxCollider::SetSize(float _x, float _y, float _z)
{
	Size[0] = _x;
	Size[1] = _y;
	Size[2] = _z;
}

void BoxCollider::SetCenter(float _x, float _y, float _z)
{
	Center[0] = _x;
	Center[1] = _y;
	Center[2] = _z;
}

void BoxCollider::Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext)
{
	md3dDevice = _pDevice;
	md3dImmediateContext = _pDeviceContext;

	Initialize();
}
