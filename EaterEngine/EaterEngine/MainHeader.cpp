#include "MainHeader.h"
#include "GameEngine.h"
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

EATER_ENGINEDLL void OnReSize(int X, int Y)
{
	//ó�� ���� ���°� �ƴҶ�
	if (gGameEngine != nullptr)
	{
		gGameEngine->OnResize(X, Y);
	}
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

EATER_ENGINEDLL void CreateSceneSub(Scene* mSceneTemp, std::string SceneName)
{
	gGameEngine->PushScene(mSceneTemp, SceneName);
}

EATER_ENGINEDLL void LoadMesh(std::string mMeshName, bool Scale,bool LoadAnime)
{
	gGameEngine->LoadMesh(mMeshName);
}

///�ε� ����
EATER_ENGINEDLL void LoadMeshPath(std::string mPath)
{
	gGameEngine->LoadMeshPath(mPath);
}

EATER_ENGINEDLL void LoadTesture(std::string mPath)
{
	gGameEngine->LoadTexture(mPath);
}

EATER_ENGINEDLL void LoadTesturePath(std::string mPath)
{
	gGameEngine->LoadTexturePath(mPath);
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

