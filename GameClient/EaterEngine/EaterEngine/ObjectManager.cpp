#include "GameTimer.h"
#include "Component.h"
#include "GameObject.h"
#include "DebugManager.h"
#include "ObjectManager.h"
/// 임시 엔진 추가.
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
	pGameTimer = new GameTimer();
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
	// 테스트용 카메라 위치
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

	/// 테스트용 박스 그리기
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

	pGameTimer->Reset();
	pTest_SRD->Render_Mesh_List = new std::vector<DHParser::Mesh>;
	pTest_SRD->Render_Mesh_List->push_back(*pTest_Mesh);
}

ObjectManager::~ObjectManager()
{
	delete pGameTimer;
	pGameTimer = nullptr;
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
	//오브젝트를 넣어줄때 빈곳이 있는지부터 확인
	std::vector<GameObject*>::iterator it = ObjectList.begin();
	for (it; it != ObjectList.end(); it++)
	{
		if ( (*it) == nullptr)
		{
			//빈곳을 찾았다면 빈곳에 넣어주고 함수 종료
			(*it) = obj;
			return;
		}
	}

	//빈곳이없다면 그냥 넣어줌
	ObjectList.push_back(obj);
}

void ObjectManager::PushDeleteObject(GameObject* obj)
{
	//오브젝트를 넣어줄때 빈곳이 있는지부터 확인
	std::vector<GameObject*>::iterator it = ObjectList.begin();
	for (it; it != ObjectList.end(); it++)
	{
		//삭제할 오브젝트를 찾았다면 그오브젝트를 일단 리스트에서 뺀다
		if ((*it) == obj)
		{
			GameObject* temp = (*it);
			(*it) = nullptr;

			//삭제할 리스트에 넣어준다
			DeleteList.push(temp);
		}
	}
}

void ObjectManager::Initialize(HWND _g_hWnd)
{
	// 엔진 초기화 ( hWnd 필요. )
	pTest_Engine->Initialize(_g_hWnd, 1920, 1080);
	pTest_Engine->SetDebug(true);
}

void ObjectManager::PushStartUpdate(Component* mComponent)
{
	//컨퍼넌트들의 업데이트 함수만 모아놓은 리스트에 들어온 컨퍼넌트 업데이트 함수를 넣어줌
	StartUpdate.Push(mComponent, std::bind(&Component::Update, mComponent));
}

void ObjectManager::PushDefaultUpdate(Component* mComponent)
{
	DefaultUpdate.Push(mComponent, std::bind(&Component::Update, mComponent));
}

void ObjectManager::PushFinalUpdate(Component* mComponent)
{
	//가장 마지막에 실행되는 업데이트 함수리스트에 넣는다
	FinalUpdate.Push(mComponent, std::bind(&Component::Update, mComponent));
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

	//가장 먼저실행되는 StartUpdate 함수 리스트
	DebugManager::GM()->Print("->StartUpdate 실행 \n");
	StartUpdate.Play();
	
	//중간 단계에 실행되는 Update 함수 리스트
	DebugManager::GM()->Print("->DefaultUpdate 실행\n");
	DefaultUpdate.Play();

	//가장 마지막에 실행되는 Update 함수 리스트
	DebugManager::GM()->Print("->FinalUpdate 실행\n");
	FinalUpdate.Play();

	///랜더링
	/*
		2021/10/19 06:50 - CDH
		
		< 변경사항 >
			1. 엔진 데모 붙이기.
			
	*/
	pTest_Engine->BeginDraw();

	pTest_Engine->TextDraw({ (int)(1920 - 350), 10 }, 500, 0, 1, 0, 1, 30, L"카메라 모드 변경 : C");
	pTest_Engine->Update(pGameTimer);
	pTest_Engine->RenderDraw(pTest_OFD, pTest_SRD);

	pTest_Engine->EndDraw();

	///삭제
	DeleteObject();
}

void ObjectManager::PlayStart()
{
	DebugManager::GM()->Print("////////////start////////////\n");
	DebugManager::GM()->Print("->Awake 실행 \n");
	AwakeFunction.Play();
	DebugManager::GM()->Print("->Start 실행 \n");
	StartFunction.Play();
}

void ObjectManager::ClearFunctionList()
{
	StartUpdate.Clear();
	FinalUpdate.Clear();
}

void ObjectManager::DeleteObject()
{
	//삭제할 오브젝트 만큼 반복문을 돈다
	for (unsigned i = 0; i < DeleteList.size(); i++)
	{
		//큐에서 가장먼저들어온 오브젝트를 꺼낸다
		GameObject* temp = DeleteList.front();

		for (int j = 0; j < temp->GetComponentCount(); j++)
		{
			Component* cpt = temp->GetDeleteComponent();

			//컨퍼넌트 삭제 함수포인터 리스트에서 그컨퍼넌트의 함수포인터를찾아서 삭제
			DeleteComponent(cpt);

			//삭제 했으니 삭제할 리스트에서도 빼준다
			DeleteList.pop();
		}
	}
}

void ObjectManager::DeleteComponent(Component* cpt)
{
	//시작단계의 함수포인터에서 넣어놨던 함수들을 삭제
	AwakeFunction.Pop(cpt);
	StartFunction.Pop(cpt);


	int state = cpt->GetUpdateState();
	//컨퍼넌트가 어떤 업데이트 함수포인터의 들어가있는지 확인하고 삭제
	switch (state)
	{
	case (int)COMPONENT_STATE::DEFAULT_UPDATE:
		DefaultUpdate.Pop(cpt);
		break;
	case (int)COMPONENT_STATE::START_UPDATE:
		StartUpdate.Pop(cpt);
		break;
	case (int)COMPONENT_STATE::END_UPDATE:
		FinalUpdate.Pop(cpt);
		break;
	}

	///이쪽에서 랜더링 함수포인터에 넣었던 것을 삭제시키면 될듯






	///진짜 컨퍼넌트 삭제
	delete cpt;
}
