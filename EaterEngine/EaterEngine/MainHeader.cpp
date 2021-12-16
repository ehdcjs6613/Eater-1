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

 void LoadMesh(std::string mMeshName, UINT parsingMode)
{
	gGameEngine->LoadMesh(mMeshName, parsingMode);
}

 void LoadTerrainMesh(std::string mMeshName, std::string maskName, UINT parsingMode)
 {
	 gGameEngine->LoadTerrain(mMeshName, maskName, parsingMode);
 }

///�ε� ����
 void LoadMeshPath(std::string mPath)
{
	gGameEngine->LoadMeshPath(mPath);
}

 void LoadTexture(std::string mPath)
{
	gGameEngine->LoadTexture(mPath);
}

 void LoadTexturePath(std::string mPath)
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

 //Vector3 GetCameraLocalPosition_UP()
 //{
//	 return gGameEngine->GetCameraLocalPosition_UP();
 //}
 //
 //Vector3 GetCameraLocalPosition_Right()
 //{
//	 return gGameEngine->GetCameraLocalPosition_Right();
 //}
 //
 //Vector3 GetCameraLocalPosition_Look()
 //{
//	 return gGameEngine->GetCameraLocalPosition_Look();
 //}

 /*DirectX::SimpleMath::Vector3 GetCameraLocalPosition_UP()
 {
	 return DirectX::SimpleMath::Vector3;
 }*/


 /// �ð� ����
 float GetDeltaTime()
 {
	 return gGameEngine->GetdeltaTime();
 }

