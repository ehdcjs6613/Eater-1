
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
//���� ����
EATER_ENGINEDLL void StartEngine(HWND _g_hWnd)
{
	//��ũ�� �Ŵ��� ����
	gKeyinput = new hsKey();
	gLoadManager = new LoadManager();
	gHwnd = _g_hWnd;
	
	ObjectManager::GM()->CreateEngine(_g_hWnd);

	//�ʱ�ȭ
	gLoadManager->init();
	DebugManager::GM()->init();
}

//���� ����
EATER_ENGINEDLL void EndEngine()
{
	SceneManager::GM()->Delete();
	gDebugManger->Delete();
}

//���� ������Ʈ 
EATER_ENGINEDLL void UpdateEngine()
{
	//�Լ� �����͸���Ʈ�� ����
	gKeyinput->UpdataMouseCursor(gHwnd);

	SceneManager::GM()->SceneUpdate();
	ObjectManager::GM()->PlayUpdate();
}

//���� ������Ʈ ����
EATER_ENGINEDLL GameObject* Instance()
{
	GameObject* temp = new GameObject();
	ObjectManager::GM()->PushCreateObject(temp);
	//Ʈ������ ���۳�Ʈ�� �ٿ��� ����
	temp->AddComponent<Transform>();
	return temp;
}

//���� ������Ʈ ����
EATER_ENGINEDLL void Destroy(GameObject* obj)
{
	ObjectManager::GM()->PushDeleteObject(obj);
}

//������ �� ����
EATER_ENGINEDLL void ChoiceScene(std::string name)
{
	SceneManager::GM()->LoadScene(name);
}

//�� ����
EATER_ENGINEDLL void StartScene()
{
	SceneManager::GM()->SceneStart();
	ObjectManager::GM()->PlayStart();
}

//�Ž��� �ε��Ѵ�
EATER_ENGINEDLL void LoadMesh(std::string mMeshName, bool Scale,bool LoadAnime)
{
	gLoadManager->LoadMesh(mMeshName, Scale,LoadAnime);
}

//�ε��� �Ž� ��� ����
EATER_ENGINEDLL void LoadMeshPath(std::string mPath)
{
	gLoadManager->LoadMeshPath(mPath);
}

EATER_ENGINEDLL GameObject* CreateMainCamera(float x, float y, float z)
{
	//������Ʈ ����
	GameObject* temp = new GameObject();
	ObjectManager::GM()->PushCreateObject(temp);

	//�ʿ� ���۳�Ʈ ����
	temp->AddComponent<Transform>();
	temp->AddComponent<Camera>();

	//����ī�޶�� ����
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

EATER_ENGINEDLL float GetMousePosX()
{
	return gKeyinput->GetMousePos()->x;
}

EATER_ENGINEDLL float GetMousePosY()
{
	return gKeyinput->GetMousePos()->y;
}

