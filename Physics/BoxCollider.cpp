
#include "BuildGeometry.h"

#include "VertexPositionColor.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider() : m_Size{1,1,1}
{
	
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
	//DirectX::XMStoreFloat4x4(&mWorldTM, DirectX::XMMatrixIdentity());
	//DirectX::XMStoreFloat4x4(&mView, DirectX::XMMatrixIdentity());
	//DirectX::XMStoreFloat4x4(&mProj, DirectX::XMMatrixIdentity());


}

void BoxCollider::EndUpdate()
{
}

void BoxCollider::Draw(const DirectX::XMFLOAT4X4 _View, const DirectX::XMFLOAT4X4 _Proj, const DirectX::XMFLOAT4X4 _WorldTM)
{
	// �Է� ��ġ ��ü ����

	m_DeviceContext->IASetInputLayout(mBuild.mInputLayout);
	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	
	// ���ؽ����ۿ� �ε������� ����
	UINT stride = sizeof(VertexPositionColor);
	UINT offset = 0;
	m_DeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer->buffer, &stride, &offset);
	m_DeviceContext->IASetIndexBuffer(m_pVertexBuffer->buffer, DXGI_FORMAT_R32_UINT, 0);


	/// WVP TM���� ����
	// Set constants
	DirectX::XMMATRIX view = DirectX::XMLoadFloat4x4(&_View);
	DirectX::XMMATRIX proj = DirectX::XMLoadFloat4x4(&_Proj);
	DirectX::XMMATRIX world = DirectX::XMLoadFloat4x4(&_WorldTM);
	DirectX::XMMATRIX worldViewProj = world * view * proj;


	mBuild.mfxWorldViewProj->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

	// ��ũ����...
	D3DX11_TECHNIQUE_DESC techDesc;
	mBuild.mTech->GetDesc(&techDesc);

	// �����н���...
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		mBuild.mTech->GetPassByIndex(p)->Apply(0, m_DeviceContext);
		m_DeviceContext->DrawIndexed(36, 0, 0);
	}
	
}

void BoxCollider::CalculateOBB()
{

}

void BoxCollider::CalculateAABB()
{

}

void BoxCollider::Initialize(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext , VertexPositionColor* _pData, UINT indexCount)
{
	m_DeviceContext =  _pDeviceContext;
	m_Device = _pDevice;

	
	VertexPositionColor* cube = (VertexPositionColor*)mVirtualMesh.CreateVertex(VirtualMesh::MeshType::eCube);

	m_pVertexBuffer->Initialize(cube, mVirtualMesh.vertexCount, m_Device);

	/// �ε��� ���۸� �����Ѵ�. (�׸�������)
	UINT* indices = mVirtualMesh.CreateIndex(VirtualMesh::MeshType::eCube);

	m_pIndexBuffer->Initialize(indices, mVirtualMesh.indicesCount, m_Device);


	mBuild.BuildFX("../Resources/Shader/LWJ/color.cso", m_Device);
	mBuild.BuildVertexLayOut(m_Device);

}
