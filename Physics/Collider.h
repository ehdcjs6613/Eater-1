#pragma once


#include "Component.h"

class Collider : public Component
{
public:
	Collider();
	virtual ~Collider();
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
};

