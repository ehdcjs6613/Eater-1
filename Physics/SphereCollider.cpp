#include "SphereCollider.h"

SphereCollider::SphereCollider()
{
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::Awake()
{
}

void SphereCollider::Start()
{
}

void SphereCollider::StartUpdate()
{
}

void SphereCollider::TransformUpdate()
{
}

void SphereCollider::PhysicsUpdate()
{
}

void SphereCollider::Update()
{
}

void SphereCollider::EndUpdate()
{
}

void SphereCollider::CalculateOBB()
{
}

void SphereCollider::CalculateAABB()
{
}

 void SphereCollider::Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext)
{
	 md3dDevice = _pDevice;
	 md3dImmediateContext = _pDeviceContext;

	 Initialize();
}

 void SphereCollider::Draw(const DirectX::XMFLOAT4X4 _View, const DirectX::XMFLOAT4X4 _Proj)
{
	 this->gameobject;
	 //요기수정
	 mView = DirectX::XMLoadFloat4x4(&_View);
	 mProj = DirectX::XMLoadFloat4x4(&_Proj);

	 // 입력 배치 객체 셋팅
	 md3dImmediateContext->IASetInputLayout(m_Gemetry.m_pInputLayout);
	 md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	 //D3D11_PRIMITIVE_TOPOLOGY_LINELIST

 // 인덱스버퍼와 버텍스버퍼 셋팅
	 UINT stride = sizeof(VertexPositionColor);
	 UINT offset = 0;
	 md3dImmediateContext->IASetVertexBuffers(0, 1, &m_Gemetry.m_pVertexBuffer, &stride, &offset);
	 md3dImmediateContext->IASetIndexBuffer(m_Gemetry.m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	
	 float v[16] =
	 {
		 1, 0, 0, 0,
		 0, 1, 0, 0,
		 0, 0, 1, 0,
		 1, 1, 1, 1,
		 //this->gameobject->GetTransform()->Position.x, this->gameobject->GetTransform()->Position.y, this->gameobject->GetTransform()->Position.z, 1,

	 };



	 mWorld =
	 {
		 DirectX::XMMATRIX(v),
	 };


	 DirectX::XMMATRIX worldViewProj = this->mWorld * mView * mProj;
	 m_Gemetry.m_pFxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));


	

	 // 테크닉은...
	 D3DX11_TECHNIQUE_DESC techDesc;
	 m_Gemetry.m_pTech->GetDesc(&techDesc);

	 // 렌더패스는...
	 for (UINT p = 0; p < techDesc.Passes; ++p)
	 {
		 m_Gemetry.m_pTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);

		 // 36개의 인덱스로 축을 그린다.
		 md3dImmediateContext->DrawIndexed(48, 0, 0);
	 }
}

 void SphereCollider::Rnder()
{
	 this->gameobject;
	 //요기수정

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


	 DirectX::XMMATRIX worldViewProj = this->mWorld * mView * mProj;
	 m_Gemetry.m_pFxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));



	 // 테크닉은...
	 D3DX11_TECHNIQUE_DESC techDesc;
	 m_Gemetry.m_pTech->GetDesc(&techDesc);

	 // 렌더패스는...
	 for (UINT p = 0; p < techDesc.Passes; ++p)
	 {
		 m_Gemetry.m_pTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);

		 // 36개의 인덱스로 축을 그린다.
		 md3dImmediateContext->DrawIndexed(48, 0, 0);
	 }
}

 void SphereCollider::Translasion(DirectX::XMMATRIX* _World)
{
  
}

void SphereCollider::Initialize()
{
	m_Gemetry.CreateLineMesh(md3dDevice, GeometryGenerator::MeshType::Sphere);
	m_Gemetry.CreateBulildFX(md3dDevice);
	m_Gemetry.CreateBulildInputLayout(md3dDevice);
}
