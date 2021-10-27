#include "GameEngine.h"

//매니저들
#include "KeyinputManager.h"
#include "LoadManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "DebugManager.h"

//오브젝트
#include "GameObject.h"

//컨퍼넌트
#include "Transform.h"


GameEngine::GameEngine()
{
	//디버깅 매니저
	mDebugManager	= nullptr;
	mLoadManager	= nullptr;
	mObjectManager	= nullptr;
	mSceneManager	= nullptr;
	mKeyManager		= nullptr;

}

GameEngine::~GameEngine()
{

}

///게임 엔진 관련
void GameEngine::Initialize(HWND Hwnd)
{
	//클라쪽에서 넘겨준 데이터 받기
	mHwnd = Hwnd;

	//매니저들 생성
	mKeyManager		= new KeyinputManager();
	mLoadManager	= new LoadManager();
	mObjectManager	= new ObjectManager();
	mSceneManager	= new SceneManager();
	mDebugManager	= new DebugManager();

	//매니저들 초기화
	mKeyManager->Initialize(mHwnd);
	mDebugManager->Initialize();
	mSceneManager->Initialize();
	mObjectManager->Initialize(mHwnd);
	mLoadManager->Initialize();	
}

void GameEngine::Update()
{
	//키관련 업데이트
	mKeyManager->Update();
	mSceneManager->Update();
	mObjectManager->PlayUpdate();
}

void GameEngine::Finish()
{
	delete mKeyManager;
	delete mLoadManager;

	mDebugManager->Delete();
	mSceneManager->Delete();
}

///오브젝트 생성 삭제
GameObject* GameEngine::Instance(std::string ObjName)
{
	//오브젝트 생성
	GameObject* temp = new GameObject();
	mObjectManager->PushCreateObject(temp);

	//Transform 은 기본으로 넣어준다
	temp->AddComponent<Transform>();

	return temp;
}

void GameEngine::Destroy(GameObject* obj)
{
	mObjectManager->PushDeleteObject(obj);
}

/// 스크린 관련 함수들
void GameEngine::PushScene(Scene* mScene, std::string name)
{
	mSceneManager->PushScene(mScene,name);
}

void GameEngine::ChoiceScene(std::string name)
{
	mSceneManager->ChoiceScene(name);
	mSceneManager->SceneStart();

	mObjectManager->PlayStart();
}

///로드 관련 함수들
void GameEngine::LoadMesh(std::string mMeshName, bool Scale, bool LoadAnime)
{
	mLoadManager->LoadMesh(mMeshName, Scale, LoadAnime);
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
