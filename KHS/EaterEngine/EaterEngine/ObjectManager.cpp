#include "Component.h"
#include "GameObject.h"
#include "DebugManager.h"
#include "ObjectManager.h"
#include "LoadManager.h"
#include "Camera.h"
#include "EngineData.h"
#include "KeyinputManager.h"
#include "MeshFilter.h"

//�Լ������� ����Ʈ��
Delegate_Map<Component> ObjectManager::AwakeFunction;
Delegate_Map<Component> ObjectManager::StartFunction;
Delegate_Map<Component> ObjectManager::StartUpdate;
Delegate_Map<Component> ObjectManager::TransformUpdate;
Delegate_Map<Component> ObjectManager::PhysicsUpdate;
Delegate_Map<Component> ObjectManager::Update;
Delegate_Map<Component> ObjectManager::EndUpdate;

ObjectManager::ObjectManager()
{
	Global = new GlobalData();
}

ObjectManager::~ObjectManager()
{
	delete Global;
	Global = nullptr;
}

GlobalData* ObjectManager::GetGlobalData()
{
	return Global;
}

void ObjectManager::PushCreateObject(GameObject* obj)
{
	//������Ʈ�� �־��ٶ� ����� �ִ������� Ȯ��
	std::vector<GameObject*>::iterator it = ObjectList.begin();
	for (it; it != ObjectList.end(); it++)
	{
		if ( (*it) == nullptr)
		{
			//����� ã�Ҵٸ� ����� �־��ְ� �Լ� ����
			(*it) = obj;
			return;
		}
	}

	//����̾��ٸ� �׳� �־���
	ObjectList.push_back(obj);
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
	//���� �Լ� ������ ����Ʈ ����
	AwakeFunction.Clear();
	StartFunction.Clear();

	//������Ʈ �Լ� ������ ����Ʈ ����
	StartUpdate.Clear();
	Update.Clear();
	EndUpdate.Clear();
}

void ObjectManager::Initialize(HWND _g_hWnd)
{
	//pTest_Engine = new DH3DEngine();
	//pTest_Engine->Initialize(_g_hWnd, 1920, 1080);
	//pTest_Engine->SetDebug(true);
}

void ObjectManager::PushStartUpdate(Component* mComponent)
{
	//���۳�Ʈ���� ������Ʈ �Լ��� ��Ƴ��� ����Ʈ�� ���� ���۳�Ʈ ������Ʈ �Լ��� �־���
	StartUpdate.Push(mComponent, std::bind(&Component::StartUpdate, mComponent));
}

void ObjectManager::PushTransformUpdate(Component* obj)
{
	TransformUpdate.Push(obj, std::bind(&Component::TransformUpdate, obj));
}

void ObjectManager::PushPhysicsUpdate(Component* obj)
{
	PhysicsUpdate.Push(obj, std::bind(&Component::PhysicsUpdate, obj));
}

void ObjectManager::PushUpdate(Component* mComponent)
{
	Update.Push(mComponent, std::bind(&Component::Update, mComponent));
}

void ObjectManager::PushEndUpdate(Component* mComponent)
{
	//���� �������� ����Ǵ� ������Ʈ �Լ�����Ʈ�� �ִ´�
	EndUpdate.Push(mComponent, std::bind(&Component::EndUpdate, mComponent));
}

void ObjectManager::PushStart(Component* mComponent)
{
	StartFunction.Push(mComponent, std::bind(&Component::Start, mComponent));
}

void ObjectManager::PushAwake(Component* mComponent)
{
	AwakeFunction.Push(mComponent, std::bind(&Component::Awake, mComponent));
}

void ObjectManager::PlayUpdate()
{
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

	///������Ʈ �۾��� �׷��ȿ������� �Ѱ��� ������ ����



	//�۷ι� ������
	Global->mProj = Camera::GetMainView();
	Global->mViewMX = Camera::GetMainView();

	///��������Ʈ�� �����͸� ����ť�� ��´�
	CreateRenderQueue();
	CreateDHRenderQueue();

	///��� ������Ʈ ������Ʈ �Ϸ�
}
void ObjectManager::DeleteRenderQueue()
{
	DHRenderData.clear();
}


void ObjectManager::PlayStart()
{
	AwakeFunction.Play();
	StartFunction.Play();

	//Test();
}

void ObjectManager::CreateRenderQueue()
{
	//������Ʈ�� ������ ��ŭ ���鼭 ����ť�� MeshData�� �������ش�

	int count = ObjectList.size();
	
	std::vector<GameObject*>::iterator it = ObjectList.begin();
	for (it; it != ObjectList.end(); it++)
	{
		RenderData.push((*it)->OneMeshData);
	}
}

void ObjectManager::ClearFunctionList()
{
	StartUpdate.Clear();
	Update.Clear();
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

		//���� ������ ������ ����Ʈ������ ���ش�
		DeleteList.pop();
	}
}

void ObjectManager::CreateDHRenderQueue()
{
	//�׽�Ʈ�� ������ ����ť �����..

	int count = ObjectList.size();

	std::vector<GameObject*>::iterator it = ObjectList.begin();
	for (it; it != ObjectList.end(); it++)
	{
		DHParser::Mesh temp = DHParser::Mesh();
		
		MeshData* data = (*it)->OneMeshData;

		if (DHRenderData.size() == count) { return; }
		if (data->IB == nullptr || data->VB == nullptr) { continue; }

		temp.Texture_Key	= 0;
		temp.Tcount			= data->indexCount;
		temp.Index_Buffer	= data->IB->IndexBufferPointer;
		temp.Vertex_Buffer	= data->VB->VertexbufferPointer;
		temp.World_TM		= *data->mWorld;
		temp.Local_TM		= *data->mWorld;


		DHRenderData.push_back(temp);
	}
}

std::vector<DHParser::Mesh>* ObjectManager::GetDHRenderQueue()
{
	return &DHRenderData;
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

