#include "Component.h"
#include "GameObject.h"
#include "DebugManager.h"
#include "ObjectManager.h"
#include "LoadManager.h"
#include "EngineData.h"
#include "Camera.h"
#include "hsKey.h"
#include "KHParser.h"

/// 임시 엔진 추가.
#include "DH3DEngine.h"
extern LoadManager* gLoadManager;
extern hsKey* gKeyinput;

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
	Global = new GlobalData();

	//테스트용 데이터 초기화
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
	//// 테스트용 카메라 위치
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

	////버텍스 정보 넘겨주기
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
	
	//인덱스 정보 넘겨주기
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

EATER_ENGINEDLL void ObjectManager::PushMainCamObject(GameObject* obj)
{
	MainCam = obj->GetComponent<Camera>();
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

void ObjectManager::AllDeleteObject()
{
	//시작 함수 포인터 리스트 삭제
	AwakeFunction.Clear();
	StartFunction.Clear();

	//업데이트 함수 포인터 리스트 삭제
	StartUpdate.Clear();
	Update.Clear();
	EndUpdate.Clear();
}

EATER_ENGINEDLL void ObjectManager::CreateEngine(HWND _g_hWnd)
{
	pTest_Engine = new DH3DEngine();
	pTest_Engine->Initialize(_g_hWnd, 1920, 1080);
	pTest_Engine->SetDebug(true);
}

void ObjectManager::PushStartUpdate(Component* mComponent)
{
	//컨퍼넌트들의 업데이트 함수만 모아놓은 리스트에 들어온 컨퍼넌트 업데이트 함수를 넣어줌
	StartUpdate.Push(mComponent, std::bind(&Component::StartUpdate, mComponent));
}

void ObjectManager::PushUpdate(Component* mComponent)
{
	Update.Push(mComponent, std::bind(&Component::Update, mComponent));
}

void ObjectManager::PushEndUpdate(Component* mComponent)
{
	//가장 마지막에 실행되는 업데이트 함수리스트에 넣는다
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
	gKeyinput->KeyUpDate();
	
	//가장 먼저실행되는 StartUpdate 함수 리스트
	DebugManager::GM()->Print("->StartUpdate 실행 \n");
	StartUpdate.Play();

	//중간 단계에 실행되는 Update 함수 리스트
	DebugManager::GM()->Print("->DefaultUpdate 실행\n");
	Update.Play();

	//가장 마지막에 실행되는 Update 함수 리스트
	DebugManager::GM()->Print("->FinalUpdate 실행\n");
	EndUpdate.Play();

	///업데이트 작업끝 그래픽엔진으로 넘겨줄 데이터 정리
	//pTest_OFD->View_Matrix = MeshTransform->GetWorld();
	DirectX::XMFLOAT4X4 view =
	{
		0.993068516, -0.0513942279, -0.105705619, 0.f,
		1.49011612e-08, 0.899335980, -0.437258303, 0.f,
		0.117537417, 0.434227467, 0.893102169, 0.00000000,
		-0.991111338, -0.756038189, 2.71574593, 1.f
	};

	pTest_OFD->View_Matrix = MainCam->GetView();
	pTest_OFD->Projection_Matrix = MainCam->GetProj();
	//pTest_OFD->Projection_Matrix = DirectX::SimpleMath::Matrix
	//(
	//	1.35799503, 0.f, 0.f, 0.f,
	//	0.f, 2.41421342, 0.f, 0.f,
	//	0.f, 0.f, 1.00000012, 1.f,
	//	0.f, 0.f, -0.000100000012, 0.f
	//);





	///랜더링 작업을 여기서?
	
	pTest_Engine->BeginDraw();
	
	pTest_Engine->TextDraw({ (int)(1920 - 350), 10 }, 500, 0, 1, 0, 1, 30, L"카메라 모드 변경 : C");
	
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


	MeshFilterData = gLoadManager->GetMesh("Table");
	Test();
}

void ObjectManager::ClearFunctionList()
{
	StartUpdate.Clear();
	Update.Clear();
}

void ObjectManager::DeleteObject()
{
	//삭제할 오브젝트 만큼 반복문을 돈다
	for (unsigned i = 0; i < DeleteList.size(); i++)
	{
		//큐에서 가장먼저들어온 오브젝트를 꺼낸다
		GameObject* temp = DeleteList.front();
		int count = temp->GetComponentCount();
		for (int j = 0; j < count; j++)
		{
			Component* cpt = temp->GetDeleteComponent(j);
			//컨퍼넌트 삭제 함수포인터 리스트에서 그컨퍼넌트의 함수포인터를찾아서 삭제
			DeleteComponent(cpt);
		}

		//삭제 했으니 삭제할 리스트에서도 빼준다
		DeleteList.pop();
	}
}

void ObjectManager::DeleteComponent(Component* cpt)
{
	//업데이트 함수포인터에 넣었던 것들 삭제
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

	




	///진짜 컨퍼넌트 삭제
	delete cpt;
	cpt = nullptr;
}

