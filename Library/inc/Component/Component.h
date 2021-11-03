#pragma once
/// <summary>
/// ���۳�Ʈ���� �ֻ��� Ŭ����
/// ��Ŭ������ ����ϰ� ���� ���۳�Ʈ����
/// ���߿� ���ӿ�����Ʈ�� ����� AddComponent�� �ҋ� �������̵��� �ߴ��� ���ߴ��� �˻� ��
/// ������Ʈ �Լ� ������ ����Ʈ�� �־���
/// </summary>

class GameObject;
class Component
{
public:
	Component();
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
	void SetConponentType(size_t type);
	//���۳�Ʈ Ÿ���� �޾ƿ´�
	size_t GetConponentType();
	//������Ʈ�� �־��ش�
	void SetObject(GameObject* obj);
protected:
	//�����۳�Ʈ�� ������ �ִ� ���ӿ�����Ʈ
	GameObject* gameobject;
	size_t ComponentType;
};



