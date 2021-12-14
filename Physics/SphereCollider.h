#pragma once

#include "DllDefine.h"
#include "DxDefine.h"
#include "Collider.h"
#include <queue>
#include "VertexPositionColor.h"
#include "GeometryGenerator.h"

class SphereCollider : public Collider
{
private:
	GeometryGenerator m_Gemetry;

	DirectX::XMMATRIX mWorld;	// ���� ��ȯ ��� (����->����)
	DirectX::XMMATRIX mView;	// �þ� ��ȯ ��� (ī�޶� ��)
	DirectX::XMMATRIX mProj;	// ���� ��ȯ ��� (����/����)

public:
	PhysicsExport SphereCollider();
	PhysicsExport virtual ~SphereCollider();
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
	//����ؼ� �浹üũ�ϴ� OBB(Orient Bounding Box)�Լ�
	//������ ���� ���̵�
	void CalculateOBB();
	//���ĵ� ������������� �浹
	void CalculateAABB();
public:
	//��ü����Լ�
	PhysicsExport void Initialize(ID3D11Device*, ID3D11DeviceContext*);
	PhysicsExport void Draw(const DirectX::XMFLOAT4X4 _View, const DirectX::XMFLOAT4X4 _Proj);
	PhysicsExport void Rnder();


	PhysicsExport void Translasion(DirectX::XMMATRIX* _World);


public:
	//��� �Լ�
	virtual void Initialize() override;

};

