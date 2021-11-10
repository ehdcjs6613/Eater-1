#pragma once

#include <string>
#include <vector>
#include <functional>

#include "EaterEngineDLL.h"
#include "Component.h"


#define AWAKE				0x00000001
#define START				0x00000010
#define START_UPDATE		0x00000100
#define Transform_UPDATE	0x00001000
#define Physics_UPDATE		0x00010000
#define UPDATE				0x00100000
#define END_UPDATE			0x01000000


/// <summary>
/// �⺻ ���� ������Ʈ
/// </summary>
class MeshData;
class Transform;
class GameObject
{
public:
	EATER_ENGINEDLL GameObject();
	~GameObject();

	EATER_ENGINEDLL void SetActive(bool active);	//��� ���۳�Ʈ ������� ����

	EATER_ENGINEDLL GameObject* GetChild(std::string Name);	//�ڽİ�ü�� ������
	EATER_ENGINEDLL GameObject* GetChild(int Number);		//�ڽİ�ü�� ������
	EATER_ENGINEDLL	Transform* GetTransform();				//�⺻ ���۳�Ʈ�� Transform�� ������

	//������ ���۳�Ʈ�� ������
	Component* GetDeleteComponent(int i);

	//������Ʈ�� ���۳�Ʈ ������ ������
	int GetComponentCount();

	void PushChildList(GameObject* obj);
	
	MeshData* OneMeshData;
	Transform* transform;
public:
	//���۳�Ʈ�� �߰� ��Ų��
	template<typename T>
	T* AddComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t = std::is_base_of<Component, T>::value);

	//���۳�Ʈ�� �����´�
	template<typename T>
	T* GetComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t = std::is_base_of<Component, T>::value);

	//�ڽİ�ü���� ã�����ϴ� ���۳�Ʈ���ִٸ� �׿�����Ʈ�� ���۳�Ʈ�� ������
	template<typename T>
	T* GetChildComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t = std::is_base_of<Component, T>::value);
public:
	std::string Name;			//�̸�
	int			Tag;			//�ױ�
	bool		IsDelete;		//���� ����
protected:
	bool IsActive;				//��� ��������
	unsigned int FunctionMask;	//� �Լ������Ϳ� �־����� ����
private:

	//���۳�Ʈ ����Ʈ
	std::vector<Component*> ComponentList;
	std::vector<GameObject*> ChildList;
	EATER_ENGINEDLL void PushComponentFunction(Component* con, unsigned int type);
};

template<typename T>
inline T* GameObject::AddComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t)
{
	//���Լ��� ������ Component�� ��ӹ��� Ŭ������ ���ü��ִ�
	//�׷��� Component �ȿ� �Լ��� �����

	T* ConponentBox = new T();
	//������ ���۳�Ʈ�� ����Ʈ�� �ִ´�
	ComponentList.push_back(ConponentBox);
	ConponentBox->SetObject(this);
	
	//���߿� ��Ÿ������ ã�Ƽ� �����ü��ֵ��� Ÿ�� ����
	ConponentBox->SetComponentType(typeid(T).hash_code());

	///�������̵� Ȯ�� �������´� �Լ������� ����Ʈ�� �ִ´� 
	//Awake
	if (&Component::Awake != &T::Awake)
	{
		PushComponentFunction(ConponentBox, AWAKE);
	}

	//Start
	if (&Component::Start != &T::Start)
	{
		PushComponentFunction(ConponentBox, START);
	}

	//StartUpdate
	if (&Component::StartUpdate != &T::StartUpdate)
	{
		PushComponentFunction(ConponentBox, START_UPDATE);
	}
	//�̵� ���
	if (&Component::TransformUpdate != &T::TransformUpdate)
	{
		PushComponentFunction(ConponentBox, Transform_UPDATE);
	}
	//���� 
	if (&Component::PhysicsUpdate != &T::PhysicsUpdate)
	{
		PushComponentFunction(ConponentBox, Physics_UPDATE);
	}

	//DefaultUpdate
	if (&Component::Update != &T::Update)
	{
		PushComponentFunction(ConponentBox, UPDATE);
	}

	//EndUpdate
	if (&Component::EndUpdate != &T::EndUpdate)
	{
		PushComponentFunction(ConponentBox, END_UPDATE);
	}

	return ConponentBox;
}

template<typename T>
inline T* GameObject::GetComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t)
{
	//�������� �ڵ带 ���� ����
	//������...���� �Ѱ��� ������Ʈ�� ���� ���۳�Ʈ �ΰ��� �����ִٸ� ��� ã�����ΰ�...

	int count = ComponentList.size();
	for (int i = 0; i < count; i++)
	{
		//���� ���۳�Ʈ�� ã�����ϴ� ���۳�Ʈ�� Ÿ�� ��
		if (ComponentList[i]->GetComponentType() == typeid(T).hash_code())
		{
			//ã�� ���۳�Ʈ�� Ÿ�Ժ�ȯ
			T* temp = dynamic_cast<T*>(ComponentList[i]);
			return temp;
		}
	}


	//���� ã�����ߴٸ� �����ڵ带 �������ָ�ɵ�..
	return nullptr;
}

template<typename T>
inline T* GameObject::GetChildComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t)
{
	return nullptr;
}

