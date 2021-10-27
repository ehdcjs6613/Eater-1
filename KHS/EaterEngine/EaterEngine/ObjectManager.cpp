#include "Component.h"
#include "GameObject.h"
#include "DebugManager.h"
#include "ObjectManager.h"
#include "LoadManager.h"
#include "EngineData.h"
#include "Camera.h"
#include "hsKey.h"
#include "MeshFilter.h"
#include "KHParser.h"

/// �ӽ� ���� �߰�.
#include "DH3DEngine.h"


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

	//�׽�Ʈ�� ������ �ʱ�ȭ
	MeshFilterData = nullptr;

	pTest_Engine = nullptr;
	pTest_OFD = nullptr;
	pTest_SRD = nullptr;
	pTest_Mesh = nullptr;

	
}

ObjectManager::~ObjectManager()
{
	
}

void ObjectManager::Test()
{
	//// �׽�Ʈ�� ī�޶� ��ġ
	pTest_OFD = new OneFrameData;
	pTest_OFD->World_Eye_Position = DirectX::SimpleMath::Vector3(10.f, 8.f, -10.f);
	pTest_OFD->Main_Position = DirectX::SimpleMath::Vector3(0.f, 0.f, 0.f);

	

	pTest_SRD = new SharedRenderData;
	pTest_Mesh = new DHParser::Mesh;
	pTest_Mesh->Texture_Key = 0;
	pTest_Mesh->Vcount = MeshFilterData->m_MeshList[0]->m_Final_Vertex.size();
	pTest_Mesh->Tcount = MeshFilterData->m_MeshList[0]->m_MeshFace.size();
	pTest_Mesh->Local_TM = MeshFilterData->m_MeshList[0]->m_WorldTM;
	pTest_Mesh->World_TM = pTest_Mesh->Local_TM;

	////���ؽ� ���� �Ѱ��ֱ�
	for (int i = 0; i < pTest_Mesh->Vcount; i++)
	{
		float x = MeshFilterData->m_MeshList[0]->m_Final_Vertex[i]->m_Pos.x;
		float y = MeshFilterData->m_MeshList[0]->m_Final_Vertex[i]->m_Pos.y;
		float z = MeshFilterData->m_MeshList[0]->m_Final_Vertex[i]->m_Pos.z;
	
		float N_x = MeshFilterData->m_MeshList[0]->m_Final_Vertex[i]->m_Normal.x;
		float N_y = MeshFilterData->m_MeshList[0]->m_Final_Vertex[i]->m_Normal.y;
		float N_z = MeshFilterData->m_MeshList[0]->m_Final_Vertex[i]->m_Normal.z;
	
	
		DHParser::Vertex m_TestVertex;
		m_TestVertex.Pos = DirectX::SimpleMath::Vector3(x, y, z);
		m_TestVertex.Normal = DirectX::SimpleMath::Vector3(N_x, N_y, N_z);
	
		pTest_Mesh->Optimize_Vertex.push_back(m_TestVertex);
	}
	
	//�ε��� ���� �Ѱ��ֱ�
	for (int j = 0; j < MeshFilterData->m_MeshList[0]->m_MeshFace.size(); j++)
	{
		int x = MeshFilterData->m_MeshList[0]->m_MeshFace[j]->m_VertexIndex[0];
		int y =MeshFilterData->m_MeshList[0]->m_MeshFace[j]->m_VertexIndex[2];
		int z =MeshFilterData->m_MeshList[0]->m_MeshFace[j]->m_VertexIndex[1];
	
		pTest_Mesh->Optimize_Index.push_back(x);
		pTest_Mesh->Optimize_Index.push_back(y);
		pTest_Mesh->Optimize_Index.push_back(z);
	}

	pTest_SRD->Render_Mesh_List = new std::vector<DHParser::Mesh>;
	pTest_SRD->Render_Mesh_List->push_back(*pTest_Mesh);
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
	pTest_Engine = new DH3DEngine();
	pTest_Engine->Initialize(_g_hWnd, 1920, 1080);
	pTest_Engine->SetDebug(true);
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
	pTest_OFD->View_Matrix			= Camera::GetMainView();
	pTest_OFD->Projection_Matrix	= Camera::GetProj();
	//�۷ι� ������
	Global->mProj = Camera::GetMainView();
	Global->mViewMX = Camera::GetMainView();

	//��������Ʈ�� �����͸� ����ť�� ��´�
	CreateRenderQueue();


	///������ �۾��� ���⼭?
	
	pTest_Engine->BeginDraw();
	
	pTest_Engine->TextDraw({ (int)(1920 - 350), 10 }, 500, 0, 1, 0, 1, 30, L"ī�޶� ��� ���� : C");
	
	pTest_Engine->RenderDraw(pTest_OFD, pTest_SRD);
	
	pTest_Engine->EndDraw();


	///����
	DeleteObject();
}

void ObjectManager::PlayStart()
{
	AwakeFunction.Play();
	StartFunction.Play();

	Test();
}

void ObjectManager::CreateRenderQueue()
{
	int count = ObjectList.size();
	std::vector<GameObject*>::iterator it = ObjectList.begin();
	for (it; it == ObjectList.end(); it++)
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

