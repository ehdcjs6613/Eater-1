#pragma once
#include "EaterEngineDLL.h"
#include "Component.h"
class Collider : public Component
{
public:
	EATER_ENGINEDLL Collider();
	EATER_ENGINEDLL ~Collider();

	//�������鼭 �浹�ϸ鼭 üũ�Ұ�����
	EATER_ENGINEDLL void SetTrigger(bool trigger);
	//���� ����
	EATER_ENGINEDLL void SetMaterial();
	//�߽��� ����
	EATER_ENGINEDLL void SetCenter(float x, float y, float z);
	//ũ�� ����
	EATER_ENGINEDLL void SetSize(float x, float y, float z);
protected:
	XMFLOAT3 Center;
	XMFLOAT3 Size;
	
	bool isTrigger;

	//���׸��� ����
private:
};

