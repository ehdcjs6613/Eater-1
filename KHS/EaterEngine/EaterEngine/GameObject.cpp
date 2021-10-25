#include "GameObject.h"


GameObject::GameObject()
{
	IsDelete = true;	//���� ����
	Tag	= 0;			//�ױ�
	IsActive = true;	//��� ���۳�Ʈ ��뿩��
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

Component* GameObject::GetDeleteComponent(int i)
{
	Component* temp = ComponentList[i];
	return temp;
}

int GameObject::GetComponentCount()
{
	return ComponentList.size();
}
