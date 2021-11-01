#include "GameEngine.h"

//�Ŵ�����
#include "KeyinputManager.h"
#include "LoadManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "DebugManager.h"
#include "Camera.h"
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

	//�׷��� ���� ����
	pTest_Engine = new DH3DEngine();




	//�Ŵ����� �ʱ�ȭ
	mKeyManager->Initialize(mHwnd);
	mDebugManager->Initialize(mKeyManager,mConsoleDebug);
	mSceneManager->Initialize();
	mObjectManager->Initialize(mHwnd);
	//�׽�Ʈ�� �̰��� �׷��ȿ����� �Ѱ��ָ�ȴ�
	mLoadManager->Initialize(pTest_Engine);
	pTest_OFD = new OneFrameData();
	pTest_SRD = new SharedRenderData();

	pTest_Engine->Initialize(Hwnd, WinSizeWidth, WinSizeHeight);
	pTest_Engine->SetDebug(true);

	
	mDebugManager->printStart();
}

void GameEngine::Update()
{
	//�Ŵ����� ������Ʈ (���۳�Ʈ ������Ʈ�� ����� ������ ������ ���ӿ�����Ʈ OneMeshData�� ����)
	mKeyManager->Update();
	mSceneManager->Update();
	mObjectManager->PlayUpdate();
	mDebugManager->Update();
	




	/// �׽�Ʈ��
	////////////////////////////////////////////////////////////////////////////////////
	pTest_OFD->World_Eye_Position	= DirectX::SimpleMath::Vector3(10.f, 8.f, -10.f);
	pTest_OFD->Main_Position		= DirectX::SimpleMath::Vector3(0.f, 0.f, 0.f);
	pTest_OFD->View_Matrix			= *Camera::GetMainView();
	pTest_OFD->Projection_Matrix	= *Camera::GetProj();
	pTest_SRD->Render_Mesh_List		= mObjectManager->GetDHRenderQueue();
	//������Ʈ�� ������ ������ �׽�Ʈ��
	pTest_Engine->BeginDraw();
	pTest_Engine->TextDraw({ (int)(1920 - 350), 10 }, 500, 0, 1, 0, 1, 30, L"ī�޶� ��� ���� : C");
	pTest_Engine->RenderDraw(pTest_OFD, pTest_SRD);
	pTest_Engine->EndDraw();
	////////////////////////////////////////////////////////////////////////////////////
	



	//�������� ������ ������Ʈ Delete
	mObjectManager->DeleteObject();
	mObjectManager->DeleteRenderQueue();
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
	pTest_Engine->On_Resize(WinSizeWidth, WinSizeHeight);
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
	mLoadManager->LoadMesh(mMeshName, Scale, LoadAnime);
	mDebugManager->Print(mMeshName, DebugManager::MSG_TYPE::MSG_LOAD);
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
