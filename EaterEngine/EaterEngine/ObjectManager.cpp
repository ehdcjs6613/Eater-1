#include "Component.h"
#include "GameObject.h"
#include "DebugManager.h"
#include "ObjectManager.h"
#include "LoadManager.h"
#include "Camera.h"
#include "EngineData.h"
#include "KeyinputManager.h"
#include "MeshFilter.h"
#include "Light.h"

//�Լ������� ����Ʈ��
Delegate_Map ObjectManager::AwakeFunction;
Delegate_Map ObjectManager::StartFunction;
Delegate_Map ObjectManager::StartUpdate;
Delegate_Map ObjectManager::TransformUpdate;
Delegate_Map ObjectManager::PhysicsUpdate;
Delegate_Map ObjectManager::Update;
Delegate_Map ObjectManager::EndUpdate;

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::PushCreateObject(GameObject* obj)
{
	//������Ʈ�� �־��ٶ� ����� �ִ������� Ȯ��
	//std::vector<GameObject*>::iterator it = ObjectList.begin();
	//for (it; it != ObjectList.end(); it++)
	//{
	//	if ( (*it) == nullptr)
	//	{
	//		//����� ã�Ҵٸ� ����� �־��ְ� �Լ� ����
	//		(*it) = obj;
	//		return;
	//	}
	//}

	//����̾��ٸ� �׳� �־���
	ObjectList.push_back(obj);
}

void ObjectManager::PushDontDeleteObject(GameObject* obj)
{
	std::vector<GameObject*>::iterator it = ObjectList.begin();
	for (it; it != ObjectList.end(); it++)
	{
		//������Ʈ�� ã�Ҵٸ� �Ű��ش�
		if ((*it) == obj)
		{
			GameObject* temp = (*it);
			(*it) = nullptr;

			DontDeleteObjectList.push_back(temp);
			return;
		}
	}

	//������Ʈ ����Ʈ���� ã�����ߴٸ� �׳� �־���
	DontDeleteObjectList.push_back(obj);
}

void ObjectManager::PushDeleteObject(GameObject* obj)
{
	//������Ʈ�� �־��ٶ� ����� �ִ������� Ȯ��
	std::vector<GameObject*>::iterator it = ObjectList.begin();
	for (it; it != ObjectList.end(); it++)
	{
		//������ ������Ʈ�� ã�Ҵٸ� �׿�����Ʈ�� �ϴ� ����Ʈ���� ����
		if ((*it) == obj)
		{
			GameObject* temp = (*it);
			(*it) = nullptr;

			//������ ����Ʈ�� �־��ش�
			DeleteList.push(temp);
		}
	}
}

void ObjectManager::AllDeleteObject()
{
	int count = (int)ObjectList.size();
	for (int i = 0; i < count; i++)
	{
		int comSize =  ObjectList[i]->GetComponentCount();
		for (int j = 0; j < comSize; j++)
		{
			DeleteComponent(ObjectList[i]->GetDeleteComponent(j));
		}
	}
	
	ObjectList.clear();
}

void ObjectManager::Initialize(HWND _g_hWnd)
{

}

void ObjectManager::PushStartUpdate(Component* mComponent)
{
	//���۳�Ʈ���� ������Ʈ �Լ��� ��Ƴ��� ����Ʈ�� ���� ���۳�Ʈ ������Ʈ �Լ��� �־���

	ComponentFunctionData data;
	//Ȱ��ȭ ����
	data.Enabled = &mComponent->Enabled;
	//�Լ� ������
	data.FunctionPointer = std::bind(&Component::StartUpdate, mComponent);
	//���۳�Ʈ ������
	data.ComponentPoiner = mComponent;

	StartUpdate.Push(data);
}

void ObjectManager::PushTransformUpdate(Component* mComponent)
{
	ComponentFunctionData data;
	//Ȱ��ȭ ����
	data.Enabled = &mComponent->Enabled;
	//�Լ� ������
	data.FunctionPointer = std::bind(&Component::TransformUpdate, mComponent);
	//���۳�Ʈ ������
	data.ComponentPoiner = mComponent;

	TransformUpdate.Push(data);
}

void ObjectManager::PushPhysicsUpdate(Component* mComponent)
{
	ComponentFunctionData data;
	//Ȱ��ȭ ����
	data.Enabled = &mComponent->Enabled;
	//�Լ� ������
	data.FunctionPointer = std::bind(&Component::PhysicsUpdate, mComponent);
	//���۳�Ʈ ������
	data.ComponentPoiner = mComponent;

	PhysicsUpdate.Push(data);
}

void ObjectManager::PushUpdate(Component* mComponent)
{
	ComponentFunctionData data;
	//Ȱ��ȭ ����
	data.Enabled = &mComponent->Enabled;
	//�Լ� ������
	data.FunctionPointer = std::bind(&Component::Update, mComponent);
	//���۳�Ʈ ������
	data.ComponentPoiner = mComponent;


	Update.Push(data);
}

void ObjectManager::PushEndUpdate(Component* mComponent)
{
	//���� �������� ����Ǵ� ������Ʈ �Լ�����Ʈ�� �ִ´�
	ComponentFunctionData data;
	//Ȱ��ȭ ����
	data.Enabled = &mComponent->Enabled;
	//�Լ� ������
	data.FunctionPointer = std::bind(&Component::EndUpdate, mComponent);
	//���۳�Ʈ ������
	data.ComponentPoiner = mComponent;

	EndUpdate.Push(data);
}

void ObjectManager::PushStart(Component* mComponent)
{
	ComponentFunctionData data;
	//Ȱ��ȭ ����
	data.Enabled = &mComponent->Enabled;
	//�Լ� ������
	data.FunctionPointer = std::bind(&Component::Start, mComponent);
	//���۳�Ʈ ������
	data.ComponentPoiner = mComponent;

	StartFunction.Push(data);
}

void ObjectManager::PushAwake(Component* mComponent)
{
	ComponentFunctionData data;
	//Ȱ��ȭ ����
	data.Enabled = &mComponent->Enabled;
	//�Լ� ������
	data.FunctionPointer = std::bind(&Component::Awake, mComponent);
	//���۳�Ʈ ������
	data.ComponentPoiner = mComponent;

	AwakeFunction.Push(data);
}

void ObjectManager::PlayUpdate()
{
	//�ѹ��� ����Ǵ� �Լ������� ����Ʈ
	AwakeFunction.Play(true);
	StartFunction.Play(true);

	///���� ��������Ǵ� StartUpdate �Լ� ����Ʈ(�� ���۳�Ʈ���� �ʱ�ȭ�۾��� ���ٶ�)
	StartUpdate.Play();

	///�̵���� ����Ǵ� Update �Լ� ����Ʈ
	TransformUpdate.Play();

	///���� �浹���� Update �Լ� ����Ʈ (�������� ���۳�Ʈ���� ������Ʈ)
	PhysicsUpdate.Play();

	///�߰� �ܰ迡 ����Ǵ� Update �Լ� ����Ʈ (Ŭ���̾�Ʈ�ʿ��� ���� ���۳�Ʈ���� ������Ʈ�ɰ�)
	Update.Play();

	///���� �������� ����Ǵ� Update �Լ� ����Ʈ
	EndUpdate.Play();





	//�۷ι� ������
	Global->mProj	= Camera::GetProj();
	Global->mViewMX = Camera::GetMainView();

	//����Ʈ ������
	Global->mLightViewMX	= DirectionLight::g_DirLight->GetView();
	Global->mLightProj		= DirectionLight::g_DirLight->GetProj();
	Global->mShadowTrans	= DirectionLight::g_DirLight->GetShadowTranspose();

	///��������Ʈ�� �����͸� ����ť�� ��´�
	CreateRenderQueue();

	///��� ������Ʈ ������Ʈ �Ϸ�
}

void ObjectManager::CreateRenderQueue()
{
	//������Ʈ�� ������ ��ŭ ���鼭 ����ť�� MeshData�� �������ش�
	for (int i = 0; i < ShadowData.size(); i++)
	{
		ShadowData.pop();
	}
	
	int count = (int)ObjectList.size();
	
	std::vector<GameObject*>::iterator it = ObjectList.begin();
	for (it; it != ObjectList.end(); it++)
	{	
		RenderData.push((*it)->OneMeshData);
		ShadowData.push((*it)->OneMeshData);
	}
}

void ObjectManager::ClearFunctionList()
{
	AwakeFunction.Clear();
	StartFunction.Clear();

	StartUpdate.Clear();
	TransformUpdate.Clear();
	PhysicsUpdate.Clear();
	Update.Clear();
	EndUpdate.Clear();
}

void ObjectManager::DeleteObject()
{
	//������ ������Ʈ ��ŭ �ݺ����� ����
	for (unsigned i = 0; i < DeleteList.size(); i++)
	{
		//ť���� ����������� ������Ʈ�� ������
		GameObject* temp = DeleteList.front();
		int count = temp->GetComponentCount();

		for (int j = 0; j < count; j++)
		{
			Component* cpt = temp->GetDeleteComponent(j);
			//���۳�Ʈ ���� �Լ������� ����Ʈ���� �����۳�Ʈ�� �Լ������͸�ã�Ƽ� ����
			DeleteComponent(cpt);
		}
		//���ӿ�����Ʈ�� ����
		delete temp;
		temp = nullptr;

		//���� ������ ������ ����Ʈ������ ���ش�
		DeleteList.pop();
	}
}

std::queue<MeshData*>* ObjectManager::GetRenderQueue()
{
	return &RenderData;
}

std::queue<MeshData*>* ObjectManager::GetShadowQueue()
{
	return &ShadowData;
}


void ObjectManager::DeleteComponent(Component* cpt)
{
	//������Ʈ �Լ������Ϳ� �־��� �͵� ����
	if (cpt->FUNCTION_MASK & AWAKE)
	{
		AwakeFunction.Pop(cpt);
	}

	if (cpt->FUNCTION_MASK & START)
	{
		StartFunction.Pop(cpt);
	}

	if (cpt->FUNCTION_MASK & START_UPDATE)
	{
		StartUpdate.Pop(cpt);
	}

	if (cpt->FUNCTION_MASK & Transform_UPDATE)
	{
		TransformUpdate.Pop(cpt);
	}

	if (cpt->FUNCTION_MASK & Physics_UPDATE)
	{
		PhysicsUpdate.Pop(cpt);
	}

	if (cpt->FUNCTION_MASK & UPDATE)
	{
		Update.Pop(cpt);
	}

	if (cpt->FUNCTION_MASK & END_UPDATE)
	{
		EndUpdate.Pop(cpt);
	}


	///��¥ ���۳�Ʈ ����
	delete cpt;
	cpt = nullptr;
}

