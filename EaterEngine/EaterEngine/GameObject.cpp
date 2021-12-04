#include "GameObject.h"
#include "EngineData.h"
#include "DebugManager.h"
#include "ObjectManager.h"
#include "Transform.h"
#include "MeshFilter.h"

GameObject::GameObject()
{
	Tag	= 0;			//�ױ�
	IsActive = true;	//��� ���۳�Ʈ ��뿩��
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
	std::vector<Component*>::iterator it = ComponentList.begin();
	for (it; it != ComponentList.end(); it++)
	{
		(*it)->Enabled = active;
	}
}

GameObject* GameObject::GetChildBone(std::string FindName)
{
	GameObject* temp = nullptr;
	if (Name == FindName)
	{
		temp = this;
		return temp;
	}


	std::vector<GameObject*>::iterator it = ChildBoneList.begin();
	for (it; it != ChildBoneList.end(); it++)
	{
		temp = (*it)->GetChildBone(FindName);
		if (temp != nullptr)
		{
			break;
		}
	}

	return temp;
}

GameObject* GameObject::GetChildMesh(std::string FindName)
{
	if (Name == FindName)
	{
		return this;
	}

	std::vector<GameObject*>::iterator it = ChildMeshList.begin();
	for (it; it != ChildMeshList.end(); it++)
	{
		 (*it)->GetChildMesh(FindName);
	}
}

Transform* GameObject::GetTransform()
{
	if (transform != nullptr)
	{
		return  transform;
	}
	else
	{
		return nullptr;
	}
}

Component* GameObject::GetDeleteComponent(int i)
{
	//���� �ε����� �´� ���۳�Ʈ�� ���������ش�
	Component* temp = ComponentList[i];
	return temp;
}

int GameObject::GetComponentCount()
{
	//���۳�Ʈ ����Ʈ�� ����� ��ȯ
	return (int)ComponentList.size();
}

void GameObject::PushChildList(GameObject* obj)
{
	//�ڽ� ������Ʈ�� �ִ´�
	ChildMeshList.push_back(obj);
}

void GameObject::ChoiceParent(GameObject* obj)
{
	//���ڽ��� ������ ������Ʈ�� �ڽ����� �ִ´�
	transform->SetParnet(obj->transform);
	obj->transform->SetChild(transform);
}

void GameObject::ChoiceChild(GameObject* obj)
{
	//���ڽ��� ������ ������Ʈ�� �ڽ����� �ִ´�
	transform->SetChild(obj->transform);
	obj->transform->SetParnet(transform);
}

void GameObject::PushChildMeshObject(GameObject* obj, std::string Name)
{
	ChildMeshList.push_back(obj);
}

void GameObject::PushChildBoneObject(GameObject* obj, std::string Name)
{
	ChildBoneList.push_back(obj);
}

void GameObject::PushComponentFunction(Component* con, unsigned int type)
{
	std::string ComponentFunction = typeid(*con).name();
	switch (type)
	{
	case AWAKE:
		DebugManager::Print(DebugManager::MSG_TYPE::MSG_PUSH, ComponentFunction, "1.Awake",false);
		ObjectManager::PushAwake(con,con->Awake_Order);
		con->FUNCTION_MASK |= AWAKE;
		break;
	case START:
		DebugManager::Print(DebugManager::MSG_TYPE::MSG_PUSH, ComponentFunction, "2.Start", false);
		ObjectManager::PushStart(con, con->Start_Order);
		con->FUNCTION_MASK |= START;
		break;
	case START_UPDATE:
		DebugManager::Print(DebugManager::MSG_TYPE::MSG_PUSH, ComponentFunction, "3.StartUpdate", false);
		ObjectManager::PushStartUpdate(con, con->StartUpdate_Order);
		con->FUNCTION_MASK |= START_UPDATE;
		break;
	case Transform_UPDATE:
		DebugManager::Print(DebugManager::MSG_TYPE::MSG_PUSH, ComponentFunction,"4.TransformUpdate", false);
		ObjectManager::PushTransformUpdate(con, con->TransformUpdate_Order);
		con->FUNCTION_MASK |= Transform_UPDATE;
		break;
	case Physics_UPDATE:
		DebugManager::Print(DebugManager::MSG_TYPE::MSG_PUSH, ComponentFunction, "5.PhysicsUpdate", false);
		ObjectManager::PushPhysicsUpdate(con, con->PhysicsUpdate_Order);
		con->FUNCTION_MASK |= Physics_UPDATE;
		break;
	case UPDATE:
		DebugManager::Print(DebugManager::MSG_TYPE::MSG_PUSH, ComponentFunction, "6,Update", false);
		ObjectManager::PushUpdate(con, con->DefaultUpdate_Order);
		con->FUNCTION_MASK |= UPDATE;
		break;
	case END_UPDATE:
		DebugManager::Print(DebugManager::MSG_TYPE::MSG_PUSH, ComponentFunction, "7.EndUpdate", false);
		ObjectManager::PushEndUpdate(con, con->EndUpdate_Order);
		con->FUNCTION_MASK |= END_UPDATE;
		break;
	}
}
