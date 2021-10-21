#pragma once

#include <string>
#include <vector>
#include "ObjectManager.h"
#include "Component.h"
class Component;
#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif


#define AWAKE			0x00000001
#define START			0x00000010
#define START_UPDATE	0x00000100
#define UPDATE			0x00001000
#define END_UPDATE		0x00010000



/// <summary>
/// �⺻ ���� ������Ʈ
/// </summary>

class MeshFilter;
class ObjectManager;
class Transfrom;
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
	Component* GetDeleteComponent();


	//������Ʈ�� ���۳�Ʈ ������ ������
	int GetComponentCount();
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
	std::queue<Component*> ComponentList;
	//�ڽİ�ü ����Ʈ
	//std::vector<GameObject*> ChildList;

};

template<typename T>
inline void GameObject::AddComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t)
{
	T* ConponentBox = new T();
	//������ ���۳�Ʈ�� ����Ʈ�� �ִ´�
	ComponentList.push(ConponentBox);
	ConponentBox->SetObject(this);

	///�������̵� Ȯ�� ����
	//Awake
	if (&Component::Awake != &T::Awake)
	{
		ObjectManager::GM()->PushAwake(ConponentBox);
		ConponentBox->FUNCTION_MASK |= AWAKE;
	}

	//Start
	if (&Component::Start != &T::Start)
	{
		ObjectManager::GM()->PushStart(ConponentBox);
		ConponentBox->FUNCTION_MASK |= START;
	}

	//StartUpdate
	if (&Component::StartUpdate != &T::StartUpdate)
	{
		ObjectManager::GM()->PushStartUpdate(ConponentBox);
		ConponentBox->FUNCTION_MASK |= START_UPDATE;
	}

	//DefaultUpdate
	if (&Component::Update != &T::Update)
	{
		ObjectManager::GM()->PushUpdate(ConponentBox);
		ConponentBox->FUNCTION_MASK |= UPDATE;
	}

	//EndUpdate
	if (&Component::EndUpdate != &T::EndUpdate)
	{
		ObjectManager::GM()->PushEndUpdate(ConponentBox);
		ConponentBox->FUNCTION_MASK |= END_UPDATE;
	}
}

template<typename T>
inline T* GameObject::GetComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t)
{
	return NULL;
}

template<typename T>
inline T* GameObject::GetChildComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t)
{
	return nullptr;
}

