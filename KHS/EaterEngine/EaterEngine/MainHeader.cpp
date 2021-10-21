
#include "MainHeader.h"
#include "Scene.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "DebugManager.h"
#include "Delegate.h"
#include "Component.h"
#include "Transfrom.h"
#include "ObjectManager.h"
#include "LoadManager.h"
#include "KHParser.h"



SceneManager*	gSceneManager;
DebugManager*	gDebugManger;
ObjectManager*	gObjectManager;
LoadManager*	gLoadManager;

//FBXParser*		gParser;

//엔진 생성
EATER_ENGINEDLL void StartEngine(HWND _g_hWnd)
{
	//스크린 매니저 생성
	gSceneManager = new SceneManager();
	gLoadManager = new LoadManager();


	//초기화
	gLoadManager->init();
	DebugManager::GM()->init();
	ObjectManager::GM()->Initialize(_g_hWnd);
}

//엔진 종료
EATER_ENGINEDLL void EndEngine()
{
	gSceneManager->Delete();
	gDebugManger->Delete();
}

//엔진 업데이트
EATER_ENGINEDLL void UpdateEngine()
{
	//함수 포인터리스트를 실행
	gSceneManager->SceneUpdate();
	ObjectManager::GM()->PlayUpdate();
}

//게임 오브젝트 생성
EATER_ENGINEDLL GameObject* Instance()
{
	GameObject* temp = new GameObject();
	ObjectManager::GM()->PushCreateObject(temp);
	return temp;
}

//게임 오브젝트 삭제
EATER_ENGINEDLL void Destroy(GameObject* obj)
{
	ObjectManager::GM()->PushDeleteObject(obj);
}

//실행할 스크린 선택
EATER_ENGINEDLL void ChoiceScene(std::string name)
{
	gSceneManager->LoadScene(name);
}

EATER_ENGINEDLL void StartScene()
{
	gSceneManager->SceneStart();
	ObjectManager::GM()->PlayStart();
}

EATER_ENGINEDLL Scene* CreateScene(std::string name)
{
	return  gSceneManager->CreateScene(name);
}

EATER_ENGINEDLL void LoadMesh(std::string mMeshName, bool Scale,bool LoadAnime)
{
	gLoadManager->LoadMesh(mMeshName, Scale,LoadAnime);
}

EATER_ENGINEDLL void LoadMeshPath(std::string mPath)
{
	gLoadManager->LoadMeshPath(mPath);
}

EATER_ENGINEDLL FBXModel* GetMesh(std::string mMeshName)
{
	return nullptr;
}


