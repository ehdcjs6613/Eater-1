#include "MainHeader.h"
#include "Scene.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "DebugManager.h"
#include "Delegate.h"
#include "Component.h"
#include "Transfrom.h"
#include "ObjectManager.h"

SceneManager*	gSceneManager;
DebugManager*	gDebugManger;
ObjectManager*	gObjectManager;

//엔진 생성
EATER_ENGINEDLL void StartEngine()
{
	//스크린 매니저 생성
	gSceneManager	= new SceneManager();
	DebugManager::GM()->init();
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
EATER_ENGINEDLL GameObject* CreateGameObject()
{
	GameObject* temp = new GameObject();
	ObjectManager::GM()->PushCreateObject(temp);
	return temp;
}

//게임 오브젝트 삭제
EATER_ENGINEDLL void DeleteGameObject(GameObject* obj)
{
	ObjectManager::GM()->PushDeleteObject(obj);
}

//실행할 스크린 선택
EATER_ENGINEDLL void ChoiceScene(std::string name)
{
	gSceneManager->ChoiceScene(name);
}

EATER_ENGINEDLL void StartScene()
{
	gSceneManager->SceneStart();
	ObjectManager::GM()->PlayStart();
}

EATER_ENGINEDLL void CreateScene(std::string name, void(*mAwake)(), void(*mStart)(), void(*mUpdate)(), void(*mEnd)())
{
	gSceneManager->CreateScene(name, mAwake,mStart,mUpdate,mEnd);
}


