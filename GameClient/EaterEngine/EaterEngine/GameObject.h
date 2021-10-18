#pragma once

#include <string>
#include <vector>
#include "ObjectManager.h"
class Component;
#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif


/// <summary>
/// 기본 게임 오브젝트
/// </summary>
class ObjectManager;
class GameObject
{
public:
	GameObject();
	~GameObject();

	

	EATER_ENGINEDLL void SetActive(bool active);	//모든 컨퍼넌트 기능중지 여부
	EATER_ENGINEDLL void Delete();					//오브젝트를 삭제함
	EATER_ENGINEDLL bool GetDelete();				//오브젝트 삭제여부 체크


	EATER_ENGINEDLL GameObject* GetChild(std::string Name);	//자식객체를 가져옴
	EATER_ENGINEDLL GameObject* GetChild(int Number);		//자식객체를 가져옴

	//삭제할 컨퍼넌트를 가져옴
	Component* GetDeleteComponent();
	//오브젝트의 컨퍼넌트 갯수를 가져옴
	int GetComponentCount();
public:
	//컨퍼넌트를 추가 시킨다
	template<typename T>
	EATER_ENGINEDLL T* AddComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t = std::is_base_of<Component, T>::value);

	//컨퍼넌트를 가져온다
	template<typename T>
	T* GetComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t = std::is_base_of<Component, T>::value);

	//자식객체에서 찾고자하는 컨퍼넌트가있다면 그오브젝트에 컨퍼넌트를 가져옴
	template<typename T>
	T* GetChildComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t = std::is_base_of<Component, T>::value);
public:
	std::string Name;			//이름
	int			Tag;			//테그
	bool		IsDelete;		//삭제 여부
private:
	bool IsActive;				//기능 중지여부
private:
	//컨퍼넌트 리스트
	std::queue<Component*> ComponentList;
	//자식객체 리스트
	//std::vector<GameObject*> ChildList;

};

template<typename T>
inline T* GameObject::AddComponent(typename std::enable_if<std::is_base_of<Component, T>::value, bool>::type t)
{
	T* ConponentBox = new T();
	//생성한 컨퍼넌트를 리스트에 넣는다
	ComponentList.push(ConponentBox);

	//시작부분의 Start 함수를 넣어준다
	ObjectManager::GM()->PushAwake(ConponentBox);
	ObjectManager::GM()->PushStart(ConponentBox);

	//컨퍼넌트의 옵션에 따라 업데이트 순서에따라 원하는 함수리스트에 넣는다
	switch (ConponentBox->GetUpdateState())
	{
	case 0:
		ObjectManager::GM()->PushDefaultUpdate(ConponentBox);
		break;
	case 1:
		ObjectManager::GM()->PushStartUpdate(ConponentBox);
		break;
	case 2:
		ObjectManager::GM()->PushFinalUpdate(ConponentBox);
		break;
	}



	return ConponentBox;
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
