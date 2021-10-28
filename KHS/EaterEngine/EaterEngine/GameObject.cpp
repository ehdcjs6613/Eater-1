#include "GameObject.h"
GameObject::GameObject()
{
	IsDelete = true;	//���� ����
	Tag	= 0;			//�ױ�
	IsActive = true;	//��� ���۳�Ʈ ��뿩��
	Name = "GameObject";
	OneMeshData = new MeshData();
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
