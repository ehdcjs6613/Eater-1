#include "GameEngine.h"

//�Ŵ�����
#include "KeyinputManager.h"
#include "LoadManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "DebugManager.h"
#include "GraphicEngineManager.h"

#include "ParserData.h"
#include "EngineData.h"
//������Ʈ
#include "GameObject.h"

//���۳�Ʈ
#include "Transform.h"
#include "Camera.h"

//�׽�Ʈ��
#include "HsGraphic.h";


GameEngine::GameEngine()
{
	mDebugManager	= nullptr;
	mLoadManager	= nullptr;
	mObjectManager	= nullptr;
	mSceneManager	= nullptr;
	mKeyManager		= nullptr;


	//�⺻ ������ ������ ����
	WinSizeWidth	= 1920;
	WinSizeHeight	= 1080;

	//������ �ڵ�
	mHwnd = NULL;
}

GameEngine::~GameEngine()
{

}

///���� ���� ����
void GameEngine::Initialize(HWND Hwnd, bool mConsoleDebug)
{
	//Ŭ���ʿ��� �Ѱ��� ������ �ޱ�
	mHwnd = Hwnd;

	//�Ŵ����� ����
	mKeyManager		= new KeyinputManager();
	mLoadManager	= new LoadManager();
	mObjectManager	= new ObjectManager();
	mSceneManager	= new SceneManager();
	mDebugManager	= new DebugManager();
	mGraphicManager = new GraphicEngineManager();

	//�׷��� ���� ����
	//pTest_Engine = new DH3DEngine();



	//�Ŵ����� �ʱ�ȭ
	mKeyManager->Initialize(mHwnd);
	mDebugManager->Initialize(mKeyManager,mConsoleDebug);
	mSceneManager->Initialize();
	mObjectManager->Initialize(mHwnd);
	mLoadManager->Initialize(mGraphicManager);
	




	/// <summary>
	/// ���� �κκи� ���ָ� �׷��ȿ��� �Ŵ������� �˾Ƽ� ���ٲ���
	/// �ٸ� �׷��ȿ����� ���������Լ��εȰ� �����Ǵٸ���������
	/// </summary>
	/////////////////////////////////////////////////////////////////
	mGraphicManager->PushEngine<HsGraphic>("����");
	mGraphicManager->ChoiceEngine("����");
	/////////////////////////////////////////////////////////////////



	mGraphicManager->Initialize(Hwnd, WinSizeWidth, WinSizeHeight);
	//ó�������ϱ��� ������ ������������
	mDebugManager->printStart();
}

void GameEngine::Update()
{
	//�Ŵ����� ������Ʈ (���۳�Ʈ ������Ʈ�� ����� ������ ������ ���ӿ�����Ʈ OneMeshData�� ����)
	mKeyManager->Update();
	mSceneManager->Update();
	mObjectManager->PlayUpdate();
	mDebugManager->Update();
	//���۳�Ʈ ������Ʈ ��
	//�׷��ȿ������� �Ѱ��� ����ť�� �����Ϸ�


	//����ť �Ѱ���
	mGraphicManager->Render(mObjectManager->GetRenderQueue(), mObjectManager->GetGlobalData());


	//�������� ������ ������Ʈ Delete
	mObjectManager->DeleteObject();
	//mObjectManager->DeleteRenderQueue();
}

void GameEngine::Finish()
{
	delete mKeyManager;
	delete mLoadManager;

	mDebugManager->Delete();
	mSceneManager->Delete();
}

void GameEngine::OnResize(int Change_Width, int Change_Height)
{
	//������ ũ�� �缳��
	WinSizeWidth	= Change_Width;
	WinSizeHeight	= Change_Height;
		
	//�׷��� ������ �������� �Լ��� ������ �ɵ�
	mGraphicManager->OnReSize(Change_Width, Change_Height);
	mDebugManager->Print("������ ������ ����",DebugManager::MSG_TYPE::MSG_ENGINE);
}

///������Ʈ ���� ����
GameObject* GameEngine::Instance(std::string ObjName)
{
	//������Ʈ ����
	GameObject* temp = new GameObject();
	mObjectManager->PushCreateObject(temp);
	temp->Name = ObjName;

	//Transform �� �⺻���� �־��ش�
	Transform* Tr = temp->AddComponent<Transform>();
	temp->transform = Tr;


	mDebugManager->Print(ObjName, DebugManager::MSG_TYPE::MSG_CREATE);
	return temp;
}

void GameEngine::Destroy(GameObject* obj)
{
	mObjectManager->PushDeleteObject(obj);
}

/// ��ũ�� ���� �Լ���
void GameEngine::PushScene(Scene* mScene, std::string name)
{
	std::string mStr = "�� ���� :" + name;
	mDebugManager->Print(mStr,DebugManager::MSG_TYPE::MSG_ENGINE);
	mSceneManager->PushScene(mScene,name);
}

void GameEngine::ChoiceScene(std::string name)
{
	std::string mStr = "���� �� ���� :" + name;
	mDebugManager->Print(mStr, DebugManager::MSG_TYPE::MSG_ENGINE);
	
	//�� ������ ���� �� �� �������� �������
	mObjectManager->AllDeleteObject();
	mObjectManager->ClearFunctionList();
	mSceneManager->ChoiceScene(name);

	//�� ������ �Ǹ� ����ü�� Awack�� Start �Լ� ���� �׸����� ���۳�Ʈ�� Awack�� Start �� ���� 
	mSceneManager->SceneStart();
	mObjectManager->PlayStart();
}

///�ε� ���� �Լ���
void GameEngine::LoadMesh(std::string mMeshName, bool Scale, bool LoadAnime)
{
	std::string temp = "�Ž��� �ε��մϴ� : " + mMeshName;
	mLoadManager->LoadMesh(mMeshName, Scale, LoadAnime);
	mDebugManager->Print(temp, DebugManager::MSG_TYPE::MSG_LOAD);
}

void GameEngine::LoadTexture(std::string mTextureName)
{
	mLoadManager->LoadTexture(mTextureName);
}

void GameEngine::LoadMeshPath(std::string mPath)
{
	mLoadManager->LoadMeshPath(mPath);
}

void GameEngine::LoadTexturePath(std::string mPath)
{
	mLoadManager->LoadTexturePath(mPath);
}

///Ű��ǲ �Լ���
bool GameEngine::GetKeyDown(byte number)
{
	//Ű�� �ѹ� ��������  true
	return mKeyManager->GetKeyDown(number);
}

bool GameEngine::GetKeyUp(byte number)
{
	//Ű�� �ѹ������� true
	return mKeyManager->GetKeyUp(number);
}

bool GameEngine::GetKey(byte number)
{
	//Ű�������������� �����Ӹ��� true
	return mKeyManager->GetKey(number);
}

bool GameEngine::GetTogle(byte number)
{
	//�ѹ� Ű�� ������ on �ٽô����� off
	return mKeyManager->GetKeyToggle(number);
}

float GameEngine::GetMousePosX()
{
	//���콺 ��ġ X��ǥ
	return (float)mKeyManager->GetMousePos()->x;
}

float GameEngine::GetMousePosY()
{
	//���콺 ��ġ y��ǥ
	return (float)mKeyManager->GetMousePos()->y;
}
