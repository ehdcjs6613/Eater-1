#pragma once

#include "DxDefine.h"
#include "DllDefine.h"
#include "VirtualMesh.h"
#include "BuildGeometry.h"
#include "Collider.h"

class GameObject;
class VertexPositionColor;
class VertexBuffer;
class IndexBuffer;

class BoxCollider : public Collider
{
private:
	DirectX::XMFLOAT4X4					 mWorldTM;
	DirectX::XMFLOAT4X4					 mView;
	DirectX::XMFLOAT4X4					 mProj;


	ID3D11Buffer* buffer;

	VertexBuffer* m_pVertexBuffer;
	IndexBuffer* m_pIndexBuffer;
	D3D11_BUFFER_DESC vertexBufferDESC;
	D3D11_SUBRESOURCE_DATA vertexBufferDATA;
	UINT indexCount = 0;
	VertexPositionColor* mVertex = nullptr;
	Build						 mBuild;
	VirtualMesh					 mVirtualMesh;

	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_DeviceContext;
public:
	float m_Size[3];

public:
	PhysicsExport BoxCollider();
	PhysicsExport virtual ~BoxCollider();
public:
	//���� �ܰ迡 ������� ����Ǵ� �Լ�
	virtual void Awake() override;
	//���� �Լ�
	virtual void Start() override;
	//ó��
	virtual void StartUpdate() override;
	//�̵� ��� ������Ʈ
	virtual void TransformUpdate() override;
	//���� ������Ʈ
	virtual void PhysicsUpdate() override;
	//�Ϲ� ������Ʈ
	virtual void Update() override;
	//������ ������Ʈ
	virtual void EndUpdate() override;
private:
	//�׷��ִ� �Լ�
	void Draw(const DirectX::XMFLOAT4X4 _View, const DirectX::XMFLOAT4X4 _Proj, const DirectX::XMFLOAT4X4 _WorldTM);
	//����ؼ� �浹üũ�ϴ� OBB(Orient Bounding Box)�Լ�
	//������ ���� ���̵�
	void CalculateOBB();
	//���ĵ� ������������� �浹
	void CalculateAABB();
public:
	void Initialize(ID3D11Device*, ID3D11DeviceContext*, VertexPositionColor* , UINT );
};
