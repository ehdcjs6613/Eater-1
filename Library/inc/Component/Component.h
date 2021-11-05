#pragma once
/// <summary>
/// ���۳�Ʈ���� �ֻ��� Ŭ����
/// ��Ŭ������ ����ϰ� ���� ���۳�Ʈ����
/// ���߿� ���ӿ�����Ʈ�� ����� AddComponent�� �ҋ� �������̵��� �ߴ��� ���ߴ��� �˻� ��
/// ������Ʈ �Լ� ������ ����Ʈ�� �־���
/// </summary>

#include <iostream>
#include <string>

//#pragma comment(lib,"../x64/Debug/DirectX2DSupporter.lib")


#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif
#include "EaterEngineDLL.h"

class GameObject;
class Component
{
public:
	EATER_ENGINEDLL Component();
	virtual ~Component();

	//���� �ܰ迡 ������� ����Ǵ� �Լ�
	virtual void Awake() {};
	//���� �Լ�
	virtual void Start() {};
	//ó��
	virtual void StartUpdate() {};
	//�̵� ��� ������Ʈ
	virtual void TransformUpdate() {};
	//���� ������Ʈ
	virtual void PhysicsUpdate() {};
	//�Ϲ� ������Ʈ
	virtual void Update() {};
	//������ ������Ʈ
	virtual void EndUpdate() {};

	
	//���� �����۳�Ʈ�� ��Լ��� �������̵��Ǿ��ִ��� Ȯ���ϱ�����
	unsigned int FUNCTION_MASK = 0x00000000;
	//Ŭ������ Ÿ�� GetComponent���� ���� ���
public:
	//���۳�Ʈ Ÿ���� �־��ش�
	EATER_ENGINEDLL void SetConponentType(size_t type);
	//���۳�Ʈ Ÿ���� �޾ƿ´�
	EATER_ENGINEDLL size_t GetConponentType();
	//������Ʈ�� �־��ش�
	EATER_ENGINEDLL void SetObject(GameObject* obj);
private:
protected:
	//�����۳�Ʈ�� ������ �ִ� ���ӿ�����Ʈ
	GameObject* gameobject;
	size_t ComponentType;
};



