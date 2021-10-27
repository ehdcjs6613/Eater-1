#include "MainHeader.h"

GameEngine* gGameEngine;

///���� ����
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
///������Ʈ ����
EATER_ENGINEDLL GameObject* Instance(std::string ObjName)
{
	return gGameEngine->Instance(ObjName);
}

EATER_ENGINEDLL void Destroy(GameObject* obj)
{
	gGameEngine->Destroy(obj);
}


///�� ����
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

///�ε� ����
EATER_ENGINEDLL void LoadMeshPath(std::string mPath)
{
	//gLoadManager->LoadMeshPath(mPath);
}

EATER_ENGINEDLL GameObject* CreateMainCamera(float x, float y, float z)
{
	//������Ʈ ����
	//GameObject* temp = new GameObject();
	//ObjectManager::GM()->PushCreateObject(temp);
	//
	////�ʿ� ���۳�Ʈ ����
	//temp->AddComponent<Transform>();
	//temp->AddComponent<Camera>();
	//
	////����ī�޶�� ����
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


///Ű����
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

