#pragma once

#include <string>
#include <vector>
#include "ObjectManager.h"
#include "Component.h"
#include "EngineData.h"
class Component;
#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif


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

class Transform;
class GameObject
{
public:
	GameObject();
	~GameObject();

	EATER_ENGINEDLL void SetActive(bool active);	//��� ���۳�Ʈ ������� ����
	EATER_ENGINEDLL void Delete();					//������Ʈ�� ������
	EATER_ENGINEDLL bool GetDelete();				//������Ʈ �������� üũ


	EATER_ENGINEDLL GameObject* GetChild(std::string Name);	//�ڽİ�ü�� ������
	EATER_ENGINEDLL GameObject* GetChild(int Number);		//�ڽİ�ü�� ������

	//������ ���۳�Ʈ�� ������
	Component* GetDeleteComponent(int i);

	//������Ʈ�� ���۳�Ʈ ������ ������
	int GetComponentCount();
	
	MeshData* OneMeshData;
public:
	//���۳�Ʈ�� �߰� ��Ų��
	template<typename T>
	EATER_ENGINEDLL void AddComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t = std::is_base_of<Component, T>::value);

	//���۳�Ʈ�� �����´�
	template<typename T>
	EATER_ENGINEDLL T* GetComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t = std::is_base_of<Component, T>::value);

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
	//�ڽİ�ü ����Ʈ
	//std::vector<GameObject*> ChildList;

};

template<typename T>
inline void GameObject::AddComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t)
{
	//���Լ��� ������ Component�� ��ӹ��� Ŭ������ ���ü��ִ�
	//�׷��� Component �ȿ� �Լ��� �����

	T* ConponentBox = new T();
	//������ ���۳�Ʈ�� ����Ʈ�� �ִ´�
	ComponentList.push_back(ConponentBox);
	ConponentBox->SetObject(this);
	
	//���߿� ��Ÿ������ ã�Ƽ� �����ü��ֵ��� Ÿ�� ����
	ConponentBox->ComponentType = typeid(T).hash_code();

	///�������̵� Ȯ�� �������´� �Լ������� ����Ʈ�� �ִ´� 
	//Awake
	if (&Component::Awake != &T::Awake)
	{
		ObjectManager::PushAwake(ConponentBox);
		ConponentBox->FUNCTION_MASK |= AWAKE;
	}

	//Start
	if (&Component::Start != &T::Start)
	{
		ObjectManager::PushStart(ConponentBox);
		ConponentBox->FUNCTION_MASK |= START;
	}

	//StartUpdate
	if (&Component::StartUpdate != &T::StartUpdate)
	{
		ObjectManager::PushStartUpdate(ConponentBox);
		ConponentBox->FUNCTION_MASK |= START_UPDATE;
	}
	//�̵� ���
	if (&Component::TransformUpdate != &T::TransformUpdate)
	{
		ObjectManager::PushTransformUpdate(ConponentBox);
		ConponentBox->FUNCTION_MASK |= Transform_UPDATE;
	}
	//���� 
	if (&Component::PhysicsUpdate != &T::PhysicsUpdate)
	{
		ObjectManager::PushPhysicsUpdate(ConponentBox);
		ConponentBox->FUNCTION_MASK |= Physics_UPDATE;
	}

	//DefaultUpdate
	if (&Component::Update != &T::Update)
	{
		ObjectManager::PushUpdate(ConponentBox);
		ConponentBox->FUNCTION_MASK |= UPDATE;
	}

	//EndUpdate
	if (&Component::EndUpdate != &T::EndUpdate)
	{
		ObjectManager::PushEndUpdate(ConponentBox);
		ConponentBox->FUNCTION_MASK |= END_UPDATE;
	}
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
	return nullptr;
}

