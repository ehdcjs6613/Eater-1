#include "MainHeader.h"

GameEngine* gGameEngine;

///엔진 관련
EATER_ENGINEDLL void EngineInitialize(HWND _g_hWnd)
{
	gGameEngine = new GameEngine();
	gGameEngine->Initialize(_g_hWnd);
}

EATER_ENGINEDLL void EndEngine()
{
	//gDebugManger->Delete();
}

EATER_ENGINEDLL void UpdateEngine()
{
	gGameEngine->Update();
}
///오브젝트 관련
EATER_ENGINEDLL GameObject* Instance(std::string ObjName)
{
	return gGameEngine->Instance(ObjName);
}

EATER_ENGINEDLL void Destroy(GameObject* obj)
{
	gGameEngine->Destroy(obj);
}


///씬 관련
EATER_ENGINEDLL void ChoiceScene(std::string name)
{
	gGameEngine->ChoiceScene(name);
}

EATER_ENGINEDLL void StartScene()
{
	//SceneManager::GM()->SceneStart();
	//ObjectManager::GM()->PlayStart();
}

EATER_ENGINEDLL void CreateScene(Scene* mSceneTemp, std::string SceneName)
{
	gGameEngine->PushScene(mSceneTemp, SceneName);
}

EATER_ENGINEDLL void LoadMesh(std::string mMeshName, bool Scale,bool LoadAnime)
{
	//gLoadManager->LoadMesh(mMeshName, Scale,LoadAnime);
}

///로드 관련
EATER_ENGINEDLL void LoadMeshPath(std::string mPath)
{
	//gLoadManager->LoadMeshPath(mPath);
}

EATER_ENGINEDLL GameObject* CreateMainCamera(float x, float y, float z)
{
	//오브젝트 생성
	//GameObject* temp = new GameObject();
	//ObjectManager::GM()->PushCreateObject(temp);
	//
	////필요 컨퍼넌트 생성
	//temp->AddComponent<Transform>();
	//temp->AddComponent<Camera>();
	//
	////메인카메라로 지정
	//Camera* tempCamera = temp->GetComponent<Camera>();
	//tempCamera->MainCamera = true;
	//
	//Transform* tempTransform = temp->GetComponent<Transform>();
	//tempTransform->SetLocalUpdate(true);
	//
	//ObjectManager::GM()->PushMainCamObject(temp);
	return nullptr;
}

EATER_ENGINEDLL void ChoiceMainCamera(GameObject* obj)
{
	//Camera* tempCamera = obj->GetComponent<Camera>();
	//tempCamera->MainCamera = true;
	//
	//Transform* tempTransform = obj->GetComponent<Transform>();
	//tempTransform->SetLocalUpdate(true);
	//
	//ObjectManager::GM()->PushMainCamObject(obj);
}


///키관련
EATER_ENGINEDLL bool GetKeyDown(byte number)
{
	return gGameEngine->GetKeyDown(number);
}

EATER_ENGINEDLL bool GetKeyUp(byte number)
{
	return gGameEngine->GetKeyUp(number);
}

EATER_ENGINEDLL bool GetKey(byte number)
{
	return gGameEngine->GetKey(number);
}

EATER_ENGINEDLL bool GetTogle(byte number)
{
	return gGameEngine->GetTogle(number);
}

EATER_ENGINEDLL float GetMousePosX()
{
	return gGameEngine->GetMousePosX();
}

EATER_ENGINEDLL float GetMousePosY()
{
	return gGameEngine->GetMousePosY();
}

