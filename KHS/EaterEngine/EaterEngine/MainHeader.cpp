
#include "MainHeader.h"
#include "Scene.h"
#include "hsKey.h"
#include "GameObject.h"
#include "Delegate.h"
#include "Component.h"
#include "Transform.h"
#include "Camera.h"
#include "MeshFilter.h"
#include "KHParser.h"
#include "DebugManager.h"
#include "ObjectManager.h"
#include "LoadManager.h"

DebugManager* gDebugManger;
ObjectManager* gObjectManager;
LoadManager* gLoadManager;
hsKey*		gKeyinput;
HWND		gHwnd;

//엔진 생성
EATER_ENGINEDLL void StartEngine(HWND _g_hWnd)
{
	//스크린 매니저 생성
	gKeyinput = new hsKey();
	gLoadManager = new LoadManager();
	gHwnd = _g_hWnd;
	
	ObjectManager::GM()->CreateEngine(_g_hWnd);

	//초기화
	gLoadManager->init();
	DebugManager::GM()->init();
}

//엔진 종료
EATER_ENGINEDLL void EndEngine()
{
	SceneManager::GM()->Delete();
	gDebugManger->Delete();
}

//엔진 업데이트 
EATER_ENGINEDLL void UpdateEngine()
{
	//함수 포인터리스트를 실행
	gKeyinput->UpdataMouseCursor(gHwnd);

	SceneManager::GM()->SceneUpdate();
	ObjectManager::GM()->PlayUpdate();
}

//게임 오브젝트 생성
EATER_ENGINEDLL GameObject* Instance(std::string ObjName)
{
	GameObject* temp = new GameObject();
	ObjectManager::GM()->PushCreateObject(temp);
	//트렌스폼 컨퍼넌트는 붙여서 생성
	temp->AddComponent<Transform>();
	return temp;
}

//게임 오브젝트 삭제
EATER_ENGINEDLL void Destroy(GameObject* obj)
{
	ObjectManager::GM()->PushDeleteObject(obj);
}

//실행할 씬 선택
EATER_ENGINEDLL void ChoiceScene(std::string name)
{
	SceneManager::GM()->LoadScene(name);
}

//씬 시작
EATER_ENGINEDLL void StartScene()
{
	SceneManager::GM()->SceneStart();
	ObjectManager::GM()->PlayStart();
}

//매쉬를 로드한다
EATER_ENGINEDLL void LoadMesh(std::string mMeshName, bool Scale,bool LoadAnime)
{
	gLoadManager->LoadMesh(mMeshName, Scale,LoadAnime);
}

//로드할 매쉬 경로 설정
EATER_ENGINEDLL void LoadMeshPath(std::string mPath)
{
	gLoadManager->LoadMeshPath(mPath);
}

EATER_ENGINEDLL GameObject* CreateMainCamera(float x, float y, float z)
{
	//오브젝트 생성
	GameObject* temp = new GameObject();
	ObjectManager::GM()->PushCreateObject(temp);

	//필요 컨퍼넌트 생성
	temp->AddComponent<Transform>();
	temp->AddComponent<Camera>();

	//메인카메라로 지정
	Camera* tempCamera = temp->GetComponent<Camera>();
	tempCamera->MainCamera = true;

	Transform* tempTransform = temp->GetComponent<Transform>();
	tempTransform->SetLocalUpdate(true);

	ObjectManager::GM()->PushMainCamObject(temp);
	return temp;
}

EATER_ENGINEDLL void ChoiceMainCamera(GameObject* obj)
{
	Camera* tempCamera = obj->GetComponent<Camera>();
	tempCamera->MainCamera = true;

	Transform* tempTransform = obj->GetComponent<Transform>();
	tempTransform->SetLocalUpdate(true);

	ObjectManager::GM()->PushMainCamObject(obj);
}

EATER_ENGINEDLL bool GetKeyDown(byte number)
{
	return gKeyinput->GetKeyDown(number);
}

EATER_ENGINEDLL bool GetKeyUp(byte number)
{
	return gKeyinput->GetKeyUp(number);
}

EATER_ENGINEDLL bool GetKey(byte number)
{
	return gKeyinput->GetKey(number);
}

EATER_ENGINEDLL bool GetTogle(byte number)
{
	return gKeyinput->GetKeyToggle(number);
}

EATER_ENGINEDLL float GetMousePosX()
{
	return gKeyinput->GetMousePos()->x;
}

EATER_ENGINEDLL float GetMousePosY()
{
	return gKeyinput->GetMousePos()->y;
}

