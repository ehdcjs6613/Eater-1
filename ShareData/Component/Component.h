#pragma once
/// <summary>
/// ���۳�Ʈ���� �ֻ��� Ŭ����
/// ��Ŭ������ ����ϰ� ���� ���۳�Ʈ����
/// ���߿� ���ӿ�����Ʈ�� ����� AddComponent�� �ҋ� �������̵��� �ߴ��� ���ߴ��� �˻� ��
/// ������Ʈ �Լ� ������ ����Ʈ�� �־���
/// </summary>

#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

class GameObject;
class Component
{
public:
	EATER_ENGINEDLL Component();
	EATER_ENGINEDLL virtual ~Component();

	//���� �ܰ迡 ������� ����Ǵ� �Լ�
	virtual void Awake() {};
	//���� �Լ�
	virtual void Start() {};
	//ó��
	virtual void StartUpdate() {};
	//��� ������Ʈ
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
	size_t ComponentType;
public:
	EATER_ENGINEDLL void SetObject(GameObject* obj);
private:

protected:
	//�����۳�Ʈ�� ������ �ִ� ���ӿ�����Ʈ
	GameObject* gameobject;
};



