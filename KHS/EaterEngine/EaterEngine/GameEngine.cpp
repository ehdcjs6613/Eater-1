#include "GameEngine.h"

//�Ŵ�����
#include "KeyinputManager.h"
#include "LoadManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "DebugManager.h"

//������Ʈ
#include "GameObject.h"

//���۳�Ʈ
#include "Transform.h"

//�׽�Ʈ��
#include "DH3DEngine.h"
#include "GraphicsEngine.h"


GameEngine::GameEngine()
{
	//����� �Ŵ���
	mDebugManager	= nullptr;
	mLoadManager	= nullptr;
	mObjectManager	= nullptr;
	mSceneManager	= nullptr;
	mKeyManager		= nullptr;

	//�׷��� ���� �׽�Ʈ��
	NowGraphicEngine = nullptr;

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
void GameEngine::Initialize(HWND Hwnd)
{
	//Ŭ���ʿ��� �Ѱ��� ������ �ޱ�
	mHwnd = Hwnd;

	//�Ŵ����� ����
	mKeyManager		= new KeyinputManager();
	mLoadManager	= new LoadManager();
	mObjectManager	= new ObjectManager();
	mSceneManager	= new SceneManager();
	mDebugManager	= new DebugManager();

	//�׷��� ���� ����
	pTest_Engine = new DH3DEngine();




	//�Ŵ����� �ʱ�ȭ
	mKeyManager->Initialize(mHwnd);
	mDebugManager->Initialize();
	mSceneManager->Initialize();
	mObjectManager->Initialize(mHwnd);
	//�׽�Ʈ�� �̰��� �׷��ȿ����� �Ѱ��ָ�ȴ�
	mLoadManager->Initialize(pTest_Engine);


	pTest_Engine->Initialize(Hwnd, WinSizeWidth, WinSizeHeight);
	
	//NowGraphicEngine->Initialize(Hwnd, WinSizeWidth, WinSizeHeight);
}

void GameEngine::Update()
{
	//�Ŵ����� ������Ʈ
	mKeyManager->Update();
	mSceneManager->Update();
	mObjectManager->PlayUpdate();
	
	//������ ����ť�� �۷ι� �����͸� �Ѱ��ش�
	//NowGraphicEngine->Render(mObjectManager->GetRenderQueue(), mObjectManager->GetGlobalData());

	//������Ʈ�� ������ ������ �׽�Ʈ��
	//pTest_Engine->BeginDraw();
	//pTest_Engine->TextDraw({ (int)(1920 - 350), 10 }, 500, 0, 1, 0, 1, 30, L"ī�޶� ��� ���� : C");
	//pTest_Engine->RenderDraw(pTest_OFD, pTest_SRD);
	//pTest_Engine->EndDraw();


	//�������� ������ ������Ʈ Delete
	mObjectManager->DeleteObject();
}

void GameEngine::Finish()
{
	delete mKeyManager;
	delete mLoadManager;

	mDebugManager->Delete();
	mSceneManager->Delete();
}

void GameEngine::OnResize(float Change_Width, float Change_Height)
{
	//������ ũ�� �缳��
	WinSizeWidth	= Change_Width;
	WinSizeHeight	= Change_Height;
		
	//�׷��� ������ �������� �Լ��� ������ �ɵ�
}

///������Ʈ ���� ����
GameObject* GameEngine::Instance(std::string ObjName)
{
	//������Ʈ ����
	GameObject* temp = new GameObject();
	mObjectManager->PushCreateObject(temp);

	//Transform �� �⺻���� �־��ش�
	temp->AddComponent<Transform>();

	return temp;
}

void GameEngine::Destroy(GameObject* obj)
{
	mObjectManager->PushDeleteObject(obj);
}

/// ��ũ�� ���� �Լ���
void GameEngine::PushScene(Scene* mScene, std::string name)
{
	mSceneManager->PushScene(mScene,name);
}

void GameEngine::ChoiceScene(std::string name)
{
	mSceneManager->ChoiceScene(name);
	mSceneManager->SceneStart();

	mObjectManager->PlayStart();
}

///�ε� ���� �Լ���
void GameEngine::LoadMesh(std::string mMeshName, bool Scale, bool LoadAnime)
{
	mLoadManager->LoadMesh(mMeshName, Scale, LoadAnime);
}

void GameEngine::LoadMeshPath(std::string mPath)
{
	mLoadManager->LoadMeshPath(mPath);
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
	return mKeyManager->GetMousePos()->x;
}

float GameEngine::GetMousePosY()
{
	//���콺 ��ġ y��ǥ
	return mKeyManager->GetMousePos()->y;
}
