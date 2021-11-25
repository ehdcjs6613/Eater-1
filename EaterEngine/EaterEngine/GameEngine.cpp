#include "GameEngine.h"

//�Ŵ�����
#include "KeyinputManager.h"
#include "LoadManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"
#include "DebugManager.h"
#include "GraphicEngineManager.h"
#include "TimeManager.h"
#include "MaterialManager.h"
#include "LightManager.h"

#include "ParserData.h"
#include "EngineData.h"
//������Ʈ
#include "GameObject.h"

//���۳�Ʈ
#include "Transform.h"
#include "Camera.h"
#include "MeshFilter.h"
#include "SkinningFilter.h"
#include "Light.h"

//�׽�Ʈ��
#include "HsGraphic.h"
#include "DH3DEngine.h"
#include "KHGraphic.h"

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
	mKeyManager			= new KeyinputManager();
	mLoadManager		= new LoadManager();
	mObjectManager		= new ObjectManager();
	mSceneManager		= new SceneManager();
	mDebugManager		= new DebugManager();
	mGraphicManager		= new GraphicEngineManager();
	mTimeManager		= new TimeManager();
	mMaterialManager	= new MaterialManager();
	mLightManager		= new LightManager();

	//�Ŵ����� ��ǲ
	MeshFilter::SetManager(mObjectManager, mMaterialManager);
	Light::SetManager(mLightManager);

	//�Ŵ����� �ʱ�ȭ
	BaseManager::Initialize();
	mKeyManager->Initialize(mHwnd);
	mDebugManager->Initialize(mKeyManager,mConsoleDebug);
	mSceneManager->Initialize();
	mObjectManager->Initialize(mHwnd);
	mLoadManager->Initialize(mGraphicManager);
	mTimeManager->Initialize();
	mLightManager->Initialize();
	mMaterialManager->Initialize();

	Component::SetManager(mTimeManager, mKeyManager);


	mGraphicManager->Initialize(Hwnd, WinSizeWidth, WinSizeHeight, mObjectManager);


	//ó�������ϱ��� ������ ������������

	/// <summary>
	/// ���� �κκи� ���ָ� �׷��ȿ��� �Ŵ������� �˾Ƽ� ���ٲ���
	/// �ٸ� �׷��ȿ����� ���������Լ��εȰ� �����Ǵٸ���������
	/// </summary>
	/////////////////////////////////////////////////////////////////

	//mGraphicManager->PushEngine<HsGraphic>("����");
	//mGraphicManager->PushEngine<DH3DEngine>("����");
	//mGraphicManager->PushEngine<KHGraphic>("��Ȳ");
	//mGraphicManager->ChoiceEngine("����");

	//������ ���� 2 	����3������ ���ҽ�Ű�ڴ� (�� �������� �� = 2 * 3)
	mGraphicManager->SplitWindow(1, 1);

	//������ ������ �ѹ��� �ִ´�
	//mGraphicManager->PushEngine(0, new HsGraphic(), "����");
	mGraphicManager->PushEngine(0, new KHGraphic(), "��Ȳ");
	//mGraphicManager->PushEngine(2, new DH3DEngine(), "����");
	//mGraphicManager->PushEngine(3, new DH3DEngine(), "����0");



	//mGraphicManager->PushEngine(1, new HsGraphic(), "����0");
	//mGraphicManager->PushEngine(2, new HsGraphic(), "����1");
	//mGraphicManager->PushEngine(3, new DH3DEngine(), "����1");
	//mGraphicManager->PushEngine(4, new HsGraphic(), "����2");
	//mGraphicManager->PushEngine(5, new KHGraphic(), "��Ȳ0");
	//mGraphicManager->PushEngine(6, new KHGraphic(), "��Ȳ1");
	//mGraphicManager->PushEngine(7, new HsGraphic(), "����3");
	//mGraphicManager->PushEngine(8, new HsGraphic(), "����4");
	//mGraphicManager->PushEngine(9, new KHGraphic(), "��Ȳ2");
	//mGraphicManager->PushEngine(10, new KHGraphic(), "��Ȳ3");
	//mGraphicManager->PushEngine(11, new HsGraphic(), "����5");
	//mGraphicManager->PushEngine(12, new DH3DEngine(), "����2");
	//mGraphicManager->PushEngine(13, new HsGraphic(), "����6");
	//mGraphicManager->PushEngine(14, new HsGraphic(), "����7");
	//mGraphicManager->PushEngine(15, new DH3DEngine(), "����3");


	/////////////////////////////////////////////////////////////////
}

void GameEngine::Update()
{
	
	//�Ŵ����� ������Ʈ (���۳�Ʈ ������Ʈ�� ����� ������ ������ ���ӿ�����Ʈ OneMeshData�� ����)
	//Ÿ�ӸŴ����� ��������Ǿ����
	mTimeManager->Update();
	mKeyManager->Update();
	mSceneManager->Update();
	mObjectManager->PlayUpdate();
	mDebugManager->Update();
	

	//���۳�Ʈ ������Ʈ ��
	//�׷��ȿ������� �Ѱ��� ����ť�� �����Ϸ�

	
	//����ť �Ѱ���
	mGraphicManager->ShadowRender(mObjectManager->GetRenderQueue(), mObjectManager->GetGlobalData());
	mGraphicManager->Render(mObjectManager->GetRenderQueue(), mObjectManager->GetGlobalData());
	mGraphicManager->SSAORender(mObjectManager->GetRenderQueue(), mObjectManager->GetGlobalData());
	mGraphicManager->UIRender(mObjectManager->GetRenderQueue(), mObjectManager->GetGlobalData());


	//�������� ������ ������Ʈ Delete
	mObjectManager->DeleteObject();
}

void GameEngine::Finish()
{
	delete mKeyManager;
	delete mLoadManager;

	mDebugManager->Delete();
	mSceneManager->Delete();

	BaseManager::Reset();
}

void GameEngine::OnResize(int Change_Width, int Change_Height)
{
	//������ ũ�� �缳��
	WinSizeWidth	= Change_Width;
	WinSizeHeight	= Change_Height;
		

	//ī�޶��� ��ȭ�� ����� �־��ش�
	Camera::SetSize(Change_Width, Change_Height);

	//�׷����ʿ� ����Ÿ���� �����ؾ��ϱ⶧���� 
	mGraphicManager->OnReSize(Change_Width, Change_Height);
	Camera::CreateProj(Change_Width, Change_Height);


	std::string Width = std::to_string(Change_Width);
	std::string Height = std::to_string(Change_Height);;
	std::string temp = "������ ������ ����:"+ Width+","+ Height;
	Camera::SetSize(Change_Width, Change_Height);
}

///������Ʈ ���� ����
GameObject* GameEngine::Instance(std::string ObjName)
{
	DebugManager::Line();
	//������Ʈ ����
	GameObject* temp = new GameObject();
	mObjectManager->PushCreateObject(temp);
	temp->Name = ObjName;
	DebugManager::Print(DebugManager::MSG_TYPE::MSG_CREATE, "GameObject", ObjName, false);

	//Transform �� �⺻���� �־��ش�
	Transform* Tr = temp->AddComponent<Transform>();
	temp->transform = Tr;


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
	mSceneManager->PushScene(mScene,name);
}

void GameEngine::ChoiceScene(std::string name)
{
	std::string mStr = "���� �� ���� :" + name;
	
	//�� ������ ���� �� �� �������� �������
	mObjectManager->AllDeleteObject();
	mObjectManager->ClearFunctionList();
	mSceneManager->ChoiceScene(name);

	//�� ������ �Ǹ� ����ü�� Awack�� Start �Լ� ���� �׸����� ���۳�Ʈ�� Awack�� Start �� ���� 
	mSceneManager->SceneStart();
	//mObjectManager->PlayStart();
}

///�ε� ���� �Լ���
void GameEngine::LoadMesh(std::string mMeshName, bool Scale, bool LoadAnime)
{
	std::string temp = "�Ž��� �ε��մϴ� : " + mMeshName;
	mLoadManager->LoadMesh(mMeshName, Scale, LoadAnime);
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

float GameEngine::GetdeltaTime()
{
	return mTimeManager->DeltaTime();
}

void GameEngine::CreateObject()
{
	GameObject* light = Instance();
	light->AddComponent<DirectionLight>();
}
