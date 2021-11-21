#include "MainHeader.h"
#include "GameEngine.h"
GameEngine* gGameEngine;

///���� ����
 void EngineInitialize(HWND _g_hWnd)
{
	gGameEngine = new GameEngine();
	gGameEngine->Initialize(_g_hWnd);
}

void EndEngine()
{
	//gDebugManger->Delete();
}

 void UpdateEngine()
{
	gGameEngine->Update();
}

 void OnReSize(int X, int Y)
{
	//ó�� ���� ���°� �ƴҶ�
	if (gGameEngine != nullptr)
	{
		gGameEngine->OnResize(X, Y);
	}
}

///������Ʈ ����
 GameObject* Instance(std::string ObjName)
{
	return gGameEngine->Instance(ObjName);
}

 void Destroy(GameObject* obj)
{
	gGameEngine->Destroy(obj);
}


///�� ����
 void ChoiceScene(std::string name)
{
	gGameEngine->ChoiceScene(name);
}

 void CreateSceneSub(Scene* mSceneTemp, std::string SceneName)
{
	gGameEngine->PushScene(mSceneTemp, SceneName);
}

 void LoadMesh(std::string mMeshName, bool Scale,bool LoadAnime)
{
	gGameEngine->LoadMesh(mMeshName,Scale,LoadAnime);
}

///�ε� ����
 void LoadMeshPath(std::string mPath)
{
	gGameEngine->LoadMeshPath(mPath);
}

 void LoadTesture(std::string mPath)
{
	gGameEngine->LoadTexture(mPath);
}

 void LoadTesturePath(std::string mPath)
{
	gGameEngine->LoadTexturePath(mPath);
}

///Ű����
 bool GetKeyDown(byte number)
{
	return gGameEngine->GetKeyDown(number);
}

 bool GetKeyUp(byte number)
{
	return gGameEngine->GetKeyUp(number);
}

 bool GetKey(byte number)
{
	return gGameEngine->GetKey(number);
}

 bool GetTogle(byte number)
{
	return gGameEngine->GetTogle(number);
}

 float GetMousePosX()
{
	return gGameEngine->GetMousePosX();
}

 float GetMousePosY()
{
	return gGameEngine->GetMousePosY();
}


 /// �ð� ����
 float GetDeltaTime()
 {
	 return gGameEngine->GetdeltaTime();
 }

