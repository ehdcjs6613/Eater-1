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

public:
	std::string Name;						//�̸�
	int			Tag;						//�ױ�

	MeshData* OneMeshData;					//�׷��� �������� �Ѱ��� ������
	Transform* transform;					//�⺻������ �������ִ� Transform Ŀ�ʳ�Ʈ
public:
	EATER_ENGINEDLL void SetActive(bool active);			//��� ���۳�Ʈ ������� ����

	EATER_ENGINEDLL GameObject* GetChildBone(std::string Name);	//�ڽİ�ü�� ������
	EATER_ENGINEDLL GameObject* GetChildMesh(std::string Name);	//�ڽİ�ü�� ������
	EATER_ENGINEDLL	Transform* GetTransform();				//�⺻ ���۳�Ʈ�� Transform�� ������

	EATER_ENGINEDLL void ChoiceParent(GameObject* obj);		//���ڽ��� ������ ������Ʈ�� �ڽ����� �ִ´�
	EATER_ENGINEDLL void ChoiceChild(GameObject* obj);		//������ ������Ʈ�� ���� �ڽ����� �ִ´�
public:
	Component* GetDeleteComponent(int i);	//������ ���۳�Ʈ�� ������
	int GetComponentCount();				//������Ʈ�� ���۳�Ʈ ������ ������
	void PushChildList(GameObject* obj);	//������Ʈ�� �ڽ� ����Ʈ�� �־��ش�

	void PushChildMeshObject(GameObject* obj, std::string Name = "Obj"); //���� �ڽ����� �⺻ ���ӿ�����Ʈ�� �ִ´�
	void PushChildBoneObject(GameObject* obj, std::string Name = "Obj"); //���� �ڽ����� �⺻ ���ӿ�����Ʈ�� �ִ´�
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
private:
	bool IsActive;							//��� ��������
	unsigned int FunctionMask;				//� �Լ������Ϳ� �־����� ����
private:
	std::vector<Component*> ComponentList;
	std::vector<GameObject*> ChildMeshList;
	std::vector<GameObject*> ChildBoneList;
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
	ConponentBox->gameobject = this;

	//���߿� ��Ÿ������ ã�Ƽ� �����ü��ֵ��� Ÿ�� ����
	ConponentBox->ComponentType = typeid(T).hash_code();

	///�������̵� Ȯ�� �������´� �Լ������� ����Ʈ�� �ִ´� 
	//Awake
	if (typeid(&Component::Awake).hash_code() != typeid(&T::Awake).hash_code())
	{
		PushComponentFunction(ConponentBox, AWAKE);
	}

	//Start
	if (typeid(&Component::Start).hash_code() != typeid(&T::Start).hash_code())
	{
		PushComponentFunction(ConponentBox, START);
	}

	//StartUpdate
	if (typeid(&Component::StartUpdate).hash_code() != typeid(&T::StartUpdate).hash_code())
	{
		PushComponentFunction(ConponentBox, START_UPDATE);
	}

	//�̵� ���
	if (typeid(&Component::TransformUpdate).hash_code() != typeid(&T::TransformUpdate).hash_code())
	{
		PushComponentFunction(ConponentBox, Transform_UPDATE);
	}

	//���� 
	if (typeid(&Component::PhysicsUpdate).hash_code() != typeid(&T::PhysicsUpdate).hash_code())
	{
		PushComponentFunction(ConponentBox, Physics_UPDATE);
	}

	//DefaultUpdate
	if (typeid(&Component::Update).hash_code() != typeid(&T::Update).hash_code())
	{
		PushComponentFunction(ConponentBox, UPDATE);
	}

	//EndUpdate
	if (typeid(&Component::EndUpdate).hash_code() != typeid(&T::EndUpdate).hash_code())
	{
		PushComponentFunction(ConponentBox, END_UPDATE);
	}

	return ConponentBox;
}

template<typename T>
inline T* GameObject::GetComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t)
{
	//���� ���۳�Ʈ�� 2���������� ã�����Ѵ�
	int count = (int)ComponentList.size();
	for (int i = 0; i < count; i++)
	{
		//���� ���۳�Ʈ�� ã�����ϴ� ���۳�Ʈ�� Ÿ�� ��
		if (ComponentList[i]->ComponentType == typeid(T).hash_code())
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
	//�ڽĿ�����Ʈ�� ���ٰ� ���� ����ã�ԵǴ� ���۳�Ʈ�� �����´�
	std::vector<GameObject*>::iterator it = ChildMeshList.begin();
	for (it; it != ChildMeshList.end(); it++)
	{
		int ComSize = (*it).ComponentList.size();
		for (int i = 0; i < ComSize; i++)
		{
			//���� ���۳�Ʈ�� ã�����ϴ� ���۳�Ʈ�� Ÿ�� ��
			if (ComponentList[i]->ComponentType == typeid(T).hash_code())
			{
				//ã�� ���۳�Ʈ�� Ÿ�Ժ�ȯ
				T* temp = dynamic_cast<T*>(ComponentList[i]);
				return temp;
			}
		}
	}
	return nullptr;
}

