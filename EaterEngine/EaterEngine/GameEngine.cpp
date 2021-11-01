#include "GameEngine.h"

//매니저들
#include "KeyinputManager.h"
#include "LoadManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "DebugManager.h"
#include "Camera.h"
//오브젝트
#include "GameObject.h"

//컨퍼넌트
#include "Transform.h"

//테스트용
#include "DH3DEngine.h"
#include "GraphicsEngine.h"


GameEngine::GameEngine()
{
	//디버깅 매니저
	mDebugManager	= nullptr;
	mLoadManager	= nullptr;
	mObjectManager	= nullptr;
	mSceneManager	= nullptr;
	mKeyManager		= nullptr;

	//그래픽 엔진 테스트용
	NowGraphicEngine = nullptr;

	//기본 윈도우 사이즈 설정
	WinSizeWidth	= 1920;
	WinSizeHeight	= 1080;

	//윈도우 핸들
	mHwnd = NULL;
}

GameEngine::~GameEngine()
{

}

///게임 엔진 관련
void GameEngine::Initialize(HWND Hwnd, bool mConsoleDebug)
{
	//클라쪽에서 넘겨준 데이터 받기
	mHwnd = Hwnd;

	//매니저들 생성
	mKeyManager		= new KeyinputManager();
	mLoadManager	= new LoadManager();
	mObjectManager	= new ObjectManager();
	mSceneManager	= new SceneManager();
	mDebugManager	= new DebugManager();

	//그래픽 엔진 생성
	pTest_Engine = new DH3DEngine();




	//매니저들 초기화
	mKeyManager->Initialize(mHwnd);
	mDebugManager->Initialize(mKeyManager,mConsoleDebug);
	mSceneManager->Initialize();
	mObjectManager->Initialize(mHwnd);
	//테스트용 이곳에 그래픽엔진을 넘겨주면된다
	mLoadManager->Initialize(pTest_Engine);
	pTest_OFD = new OneFrameData();
	pTest_SRD = new SharedRenderData();

	pTest_Engine->Initialize(Hwnd, WinSizeWidth, WinSizeHeight);
	pTest_Engine->SetDebug(true);

	
	mDebugManager->printStart();
}

void GameEngine::Update()
{
	//매니저들 업데이트 (컨퍼넌트 업데이트후 변경된 사항을 각각의 게임오브젝트 OneMeshData에 전달)
	mKeyManager->Update();
	mSceneManager->Update();
	mObjectManager->PlayUpdate();
	mDebugManager->Update();
	




	/// 테스트용
	////////////////////////////////////////////////////////////////////////////////////
	pTest_OFD->World_Eye_Position	= DirectX::SimpleMath::Vector3(10.f, 8.f, -10.f);
	pTest_OFD->Main_Position		= DirectX::SimpleMath::Vector3(0.f, 0.f, 0.f);
	pTest_OFD->View_Matrix			= *Camera::GetMainView();
	pTest_OFD->Projection_Matrix	= *Camera::GetProj();
	pTest_SRD->Render_Mesh_List		= mObjectManager->GetDHRenderQueue();
	//업데이트가 끝나고 랜더링 테스트용
	pTest_Engine->BeginDraw();
	pTest_Engine->TextDraw({ (int)(1920 - 350), 10 }, 500, 0, 1, 0, 1, 30, L"카메라 모드 변경 : C");
	pTest_Engine->RenderDraw(pTest_OFD, pTest_SRD);
	pTest_Engine->EndDraw();
	////////////////////////////////////////////////////////////////////////////////////
	



	//랜더링이 끝나고 오브젝트 Delete
	mObjectManager->DeleteObject();
	mObjectManager->DeleteRenderQueue();
}

void GameEngine::Finish()
{
	delete mKeyManager;
	delete mLoadManager;

	mDebugManager->Delete();
	mSceneManager->Delete();
}

void GameEngine::OnResize(float Change_Width, float Change_Height)
{
	//윈도우 크기 재설정
	WinSizeWidth	= Change_Width;
	WinSizeHeight	= Change_Height;
		
	//그래픽 엔진의 리사이즈 함수를 넣으면 될듯
	pTest_Engine->On_Resize(WinSizeWidth, WinSizeHeight);
	mDebugManager->Print("윈도우 사이즈 변경",DebugManager::MSG_TYPE::MSG_ENGINE);
}

///오브젝트 생성 삭제
GameObject* GameEngine::Instance(std::string ObjName)
{
	//오브젝트 생성
	GameObject* temp = new GameObject();
	mObjectManager->PushCreateObject(temp);
	temp->Name = ObjName;
	//Transform 은 기본으로 넣어준다
	Transform* Tr = temp->AddComponent<Transform>();
	temp->transform = Tr;


	mDebugManager->Print(ObjName, DebugManager::MSG_TYPE::MSG_CREATE);
	return temp;
}

void GameEngine::Destroy(GameObject* obj)
{
	mObjectManager->PushDeleteObject(obj);
}

/// 스크린 관련 함수들
void GameEngine::PushScene(Scene* mScene, std::string name)
{
	std::string mStr = "씬 생성 :" + name;
	mDebugManager->Print(mStr,DebugManager::MSG_TYPE::MSG_ENGINE);
	mSceneManager->PushScene(mScene,name);
}

void GameEngine::ChoiceScene(std::string name)
{
	std::string mStr = "현재 씬 선택 :" + name;
	mDebugManager->Print(mStr, DebugManager::MSG_TYPE::MSG_ENGINE);
	
	//씬 선택후 이전 씬 의 정보들을 모두지움
	mObjectManager->AllDeleteObject();
	mObjectManager->ClearFunctionList();
	mSceneManager->ChoiceScene(name);

	//씬 선택이 되면 씬자체의 Awack와 Start 함수 실행 그리고나서 컨퍼넌트의 Awack와 Start 도 실행 
	mSceneManager->SceneStart();
	mObjectManager->PlayStart();
}

///로드 관련 함수들
void GameEngine::LoadMesh(std::string mMeshName, bool Scale, bool LoadAnime)
{
	mLoadManager->LoadMesh(mMeshName, Scale, LoadAnime);
	mDebugManager->Print(mMeshName, DebugManager::MSG_TYPE::MSG_LOAD);
}

void GameEngine::LoadMeshPath(std::string mPath)
{
	mLoadManager->LoadMeshPath(mPath);
}

///키인풋 함수들
bool GameEngine::GetKeyDown(byte number)
{
	//키를 한번 눌렀을때  true
	return mKeyManager->GetKeyDown(number);
}

bool GameEngine::GetKeyUp(byte number)
{
	//키를 한번땠을때 true
	return mKeyManager->GetKeyUp(number);
}

bool GameEngine::GetKey(byte number)
{
	//키를누르고있을때 프레임마다 true
	return mKeyManager->GetKey(number);
}

bool GameEngine::GetTogle(byte number)
{
	//한번 키를 누르면 on 다시누르면 off
	return mKeyManager->GetKeyToggle(number);
}

float GameEngine::GetMousePosX()
{
	//마우스 위치 X좌표
	return mKeyManager->GetMousePos()->x;
}

float GameEngine::GetMousePosY()
{
	//마우스 위치 y좌표
	return mKeyManager->GetMousePos()->y;
}
