#include "Component.h"
#include "GameObject.h"
#include "DebugManager.h"
#include "ObjectManager.h"

/// �ӽ� ���� �߰�.
#include "DH3DEngine.h"


ObjectManager* ObjectManager::instance = nullptr;
ObjectManager* ObjectManager::GM()
{
	if (instance == nullptr)
	{
		instance = new ObjectManager();
	}

	return instance;
}

ObjectManager::ObjectManager()
{
	pTest_Engine = new DH3DEngine();

	pTest_OFD = new OneFrameData;
	pTest_OFD->View_Matrix = DirectX::SimpleMath::Matrix
	(
		0.993068516, -0.0513942279, -0.105705619, 0.f,
		1.49011612e-08, 0.899335980, -0.437258303, 0.f,
		0.117537417, 0.434227467, 0.893102169, 0.00000000,
		-0.991111338, -0.756038189, 2.71574593, 1.f
	);
	pTest_OFD->Projection_Matrix = DirectX::SimpleMath::Matrix
	(
		1.35799503, 0.f, 0.f, 0.f,
		0.f, 2.41421342, 0.f, 0.f,
		0.f, 0.f, 1.00000012, 1.f,
		0.f, 0.f, -0.000100000012, 0.f
	);
	// �׽�Ʈ�� ī�޶� ��ġ
	pTest_OFD->World_Eye_Position = DirectX::SimpleMath::Vector3(10.f, 8.f, -10.f);
	pTest_OFD->Main_Position = DirectX::SimpleMath::Vector3(0.f, 0.f, 0.f);

	pTest_SRD = new SharedRenderData;

	pTest_Mesh = new DHParser::Mesh;

	pTest_Mesh->Texture_Key = 0;
	pTest_Mesh->Vcount = 24;
	pTest_Mesh->Tcount = 12;
	pTest_Mesh->Local_TM = DirectX::SimpleMath::Matrix
	(
		-1, 0.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 1.f
	);
	pTest_Mesh->World_TM = pTest_Mesh->Local_TM;

	/// �׽�Ʈ�� �ڽ� �׸���
	// Vertex
	TestAddVerTex(1.f, 1.f, 1.f, 0.f, 1.f, 0.f);	// 0
	TestAddVerTex(-1.f, 1.f, 1.f, 0.f, 1.f, 0.f);
	TestAddVerTex(-1.f, 1.f, -1.f, 0.f, 1.f, 0.f);
	TestAddVerTex(1.f, 1.f, -1.f, 0.f, 1.f, 0.f);
	TestAddVerTex(1.f, 1.f, -1.f, 0.f, 0.f, -1.f);
	TestAddVerTex(1.f, 1.f, -1.f, 0.f, 0.f, -1.f);
	TestAddVerTex(-1.f, 1.f, -1.f, 0.f, 0.f, -1.f);
	TestAddVerTex(-1.f, -1.f, -1.f, 0.f, 0.f, 1.f);
	TestAddVerTex(1.f, 1.f, -1.f, -1.f, 0.f, 0.f);
	TestAddVerTex(-1.f, 1.f, -1.f, 1.f, 0.f, 0.f);
	TestAddVerTex(-1.f, 1.f, 1.f, -1.f, 1.f, 0.f);	// 10

	TestAddVerTex(-1.f, -1.f, 1.f, -1.f, 0.f, 0.f);
	TestAddVerTex(-1.f, -1.f, 1.f, 0.f, -1.f, 0.f);
	TestAddVerTex(1.f, -1.f, 1.f, 0.f, -1.f, 0.f);
	TestAddVerTex(1.f, -1.f, -1.f, 0.f, -1.f, 0.f);
	TestAddVerTex(-1.f, -1.f, -1.f, 0.f, -1.f, 0.f);
	TestAddVerTex(1.f, -1.f, 1.f, 1.f, 0.f, 0.f);
	TestAddVerTex(1.f, 1.f, 1.f, 1.f, 0.f, 0.f);
	TestAddVerTex(1.f, 1.f, -1.f, 1.f, 0.f, 0.f);
	TestAddVerTex(1.f, -1.f, -1.f, 1.f, 0.f, 0.f);
	TestAddVerTex(-1.f, -1.f, -1.f, 0.f, 0.f, 1.f); // 20

	TestAddVerTex(-1.f, 1.f, 1.f, 0.f, 0.f, 1.f);
	TestAddVerTex(1.f, 1.f, 1.f, 0.f, 0.f, 1.f);
	TestAddVerTex(1.f, -1.f, 1.f, 0.f, 0.f, 1.f);

	//Index
	TestAddIndex(0);	// 0
	TestAddIndex(2);
	TestAddIndex(1);
	TestAddIndex(2);
	TestAddIndex(0);
	TestAddIndex(3);
	TestAddIndex(4);
	TestAddIndex(6);
	TestAddIndex(5);
	TestAddIndex(6);
	TestAddIndex(4);	// 10

	TestAddIndex(7);
	TestAddIndex(8);
	TestAddIndex(10);
	TestAddIndex(9);
	TestAddIndex(10);
	TestAddIndex(8);
	TestAddIndex(11);
	TestAddIndex(12);
	TestAddIndex(14);
	TestAddIndex(13);	// 20

	TestAddIndex(14);
	TestAddIndex(12);
	TestAddIndex(15);
	TestAddIndex(16);
	TestAddIndex(18);
	TestAddIndex(17);
	TestAddIndex(18);
	TestAddIndex(16);
	TestAddIndex(19);
	TestAddIndex(20);	// 30

	TestAddIndex(22);
	TestAddIndex(21);
	TestAddIndex(22);
	TestAddIndex(20);
	TestAddIndex(23);

	pTest_SRD->Render_Mesh_List = new std::vector<DHParser::Mesh>;
	pTest_SRD->Render_Mesh_List->push_back(*pTest_Mesh);
}

ObjectManager::~ObjectManager()
{
	delete pTest_Engine;
}


void ObjectManager::TestAddVerTex(float _x, float _y, float _z,
	float N_x, float N_y, float N_z)
{
	DHParser::Vertex m_TestVertex;
	m_TestVertex.Pos = DirectX::SimpleMath::Vector3(_x, _y, _z);
	m_TestVertex.Normal = DirectX::SimpleMath::Vector3(N_x, N_y, N_z);

	pTest_Mesh->Optimize_Vertex.push_back(m_TestVertex);
}

void ObjectManager::TestAddIndex(UINT _index)
{
	pTest_Mesh->Optimize_Index.push_back(_index);
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

void ObjectManager::Initialize(HWND _g_hWnd)
{
	// ���� �ʱ�ȭ ( hWnd �ʿ�. )
	pTest_Engine->Initialize(_g_hWnd, 1920, 1080);
	pTest_Engine->SetDebug(true);
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

void ObjectManager::PushStartUpdate(Component* mComponent)
{
	//���۳�Ʈ���� ������Ʈ �Լ��� ��Ƴ��� ����Ʈ�� ���� ���۳�Ʈ ������Ʈ �Լ��� �־���
	StartUpdate.Push(mComponent, std::bind(&Component::StartUpdate, mComponent));
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

	DebugManager::GM()->Print("////////////Update////////////\n");

	//���� ��������Ǵ� StartUpdate �Լ� ����Ʈ
	DebugManager::GM()->Print("->StartUpdate ���� \n");
	StartUpdate.Play();

	//�߰� �ܰ迡 ����Ǵ� Update �Լ� ����Ʈ
	DebugManager::GM()->Print("->DefaultUpdate ����\n");
	Update.Play();

	//���� �������� ����Ǵ� Update �Լ� ����Ʈ
	DebugManager::GM()->Print("->FinalUpdate ����\n");
	EndUpdate.Play();

	///������
	/*
		2021/10/19 06:50 - CDH
		
		< ������� >
			1. ���� ���� ���̱�.
			
	*/
	pTest_Engine->BeginDraw();

	pTest_Engine->TextDraw({ (int)(1920 - 350), 10 }, 500, 0, 1, 0, 1, 30, L"ī�޶� ��� ���� : C");

	pTest_Engine->RenderDraw(pTest_OFD, pTest_SRD);

	pTest_Engine->EndDraw();

	///����
	DeleteObject();
}

void ObjectManager::PlayStart()
{
	DebugManager::GM()->Print("////////////start////////////\n");

	DebugManager::GM()->Print("->Awake ���� \n");
	AwakeFunction.Play();
	DebugManager::GM()->Print("->Start ���� \n");
	StartFunction.Play();
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
			Component* cpt = temp->GetDeleteComponent();
			//���۳�Ʈ ���� �Լ������� ����Ʈ���� �����۳�Ʈ�� �Լ������͸�ã�Ƽ� ����
			DeleteComponent(cpt);
		}

		//���� ������ ������ ����Ʈ������ ���ش�
		DeleteList.pop();
	}
}

void ObjectManager::DeleteComponent(Component* cpt)
{
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

	if (cpt->FUNCTION_MASK & UPDATE)
	{
		Update.Pop(cpt);
	}

	if (cpt->FUNCTION_MASK & END_UPDATE)
	{
		EndUpdate.Pop(cpt);
	}

	///���ʿ��� ������ �Լ������Ϳ� �־��� ���� ������Ű�� �ɵ�




	///��¥ ���۳�Ʈ ����
	delete cpt;
	cpt = nullptr;
}

