#include "GameObject.h"
GameObject::GameObject()
{
	IsDelete = true;	//삭제 여부
	Tag	= 0;			//테그
	IsActive = true;	//모든 컨퍼넌트 사용여부
	Name = "GameObject";
	OneMeshData = new MeshData();
	transform = nullptr;
}

GameObject::~GameObject()
{
	delete OneMeshData;
	OneMeshData = nullptr;
}

void GameObject::SetActive(bool active)
{
	IsActive = active;
}

GameObject* GameObject::GetChild(std::string Name)
{
	return nullptr;
}

GameObject* GameObject::GetChild(int Number)
{
	return nullptr;
}

Component* GameObject::GetDeleteComponent(int i)
{
	Component* temp = ComponentList[i];
	return temp;
}

int GameObject::GetComponentCount()
{
	return ComponentList.size();
}
