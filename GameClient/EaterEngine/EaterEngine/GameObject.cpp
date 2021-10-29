#include "GameObject.h"


GameObject::GameObject()
{
	IsDelete = true;	//삭제 여부
	Tag	= 0;			//테그
	IsActive = true;	//모든 컨퍼넌트 사용여부
	Name = "GameObject";
}

GameObject::~GameObject()
{

}

void GameObject::SetActive(bool active)
{
	IsActive = active;
}

void GameObject::Delete()
{
	IsDelete = true;


}

bool GameObject::GetDelete()
{
	return IsDelete;
}

GameObject* GameObject::GetChild(std::string Name)
{
	return nullptr;
}

GameObject* GameObject::GetChild(int Number)
{
	return nullptr;
}

Component* GameObject::GetDeleteComponent()
{
	Component* temp =  ComponentList.front();
	ComponentList.pop();
	return temp;
}

int GameObject::GetComponentCount()
{
	return ComponentList.size();
}
