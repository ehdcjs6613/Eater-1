#pragma once

#include "DllDefine.h"
#include "Collider.h"

class GameObject;

class BoxCollider : public Collider
{
private:
	//GameObject* m_pGameObject;

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
	void Draw();
	//����ؼ� �浹üũ�ϴ� OBB(Orient Bounding Box)�Լ�
	//������ ���� ���̵�
	void CalculateOBB();
	//���ĵ� ������������� �浹
	void CalculateAABB();
public:
	void Initialize(ID3D11DeviceContext*);
};
