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

	//�׷��� ���� ����
	//pTest_Engine = new DH3DEngine();



	//�Ŵ����� �ʱ�ȭ
	BaseManager::Initialize();
	mKeyManager->Initialize(mHwnd);
	mDebugManager->Initialize(mKeyManager,mConsoleDebug);
	mSceneManager->Initialize();
	mObjectManager->Initialize(mHwnd);
	mLoadManager->Initialize(mGraphicManager);
	mTimeManager->Initialize();
	mLightManager->Initialize();

	MeshFilter::SetManager(mObjectManager, mMaterialManager);
	Light::SetManager(mLightManager);

	//ó�������ϱ��� ������ ������������

	/// <summary>
	/// ���� �κκи� ���ָ� �׷��ȿ��� �Ŵ������� �˾Ƽ� ���ٲ���
	/// �ٸ� �׷��ȿ����� ���������Լ��εȰ� �����Ǵٸ���������
	/// </summary>
	/////////////////////////////////////////////////////////////////
	mGraphicManager->PushEngine<HsGraphic>("����");
	mGraphicManager->PushEngine<DH3DEngine>("����");
	mGraphicManager->PushEngine<KHGraphic>("��Ȳ");
	mGraphicManager->ChoiceEngine("����");
	/////////////////////////////////////////////////////////////////



	mGraphicManager->Initialize(Hwnd, WinSizeWidth, WinSizeHeight);
}

void GameEngine::Update()
{
	mDebugManager->Clear();
	//mDebugManager->printStart();
	//�Ŵ����� ������Ʈ (���۳�Ʈ ������Ʈ�� ����� ������ ������ ���ӿ�����Ʈ OneMeshData�� ����)
	mKeyManager->Update();
	mSceneManager->Update();
	mObjectManager->PlayUpdate();

	mDebugManager->Update();
	mTimeManager->Update();
	mGraphicManager->Update();


	mDebugManager->End();
	//���۳�Ʈ ������Ʈ ��
	//�׷��ȿ������� �Ѱ��� ����ť�� �����Ϸ�

	
	//����ť �Ѱ���
	mGraphicManager->ShadowRender(mObjectManager->GetShadowQueue(), mObjectManager->GetGlobalData());
	mGraphicManager->Render(mObjectManager->GetRenderQueue(), mObjectManager->GetGlobalData());
	mGraphicManager->SSAORender(mObjectManager->GetRenderQueue(), mObjectManager->GetGlobalData());
	mGraphicManager->UIRender(mObjectManager->GetRenderQueue(), mObjectManager->GetGlobalData());


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

	mDebugManager->Print(temp,0,0, DebugManager::MSG_TYPE::MSG_ENGINE);
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


	mDebugManager->Print(ObjName,0,1,DebugManager::MSG_TYPE::MSG_CREATE);
	return temp;
}

GameObject* GameEngine::InstanceModel(std::string ObjName)
{
	ModelData* mModel =	mLoadManager->GetMesh(ObjName);
	

	return nullptr;
}

void GameEngine::Destroy(GameObject* obj)
{
	mObjectManager->PushDeleteObject(obj);
}

/// ��ũ�� ���� �Լ���
void GameEngine::PushScene(Scene* mScene, std::string name)
{
	std::string mStr = "�� ���� :" + name;
	mDebugManager->Print(mStr,0,0,DebugManager::MSG_TYPE::MSG_ENGINE);
	mSceneManager->PushScene(mScene,name);
}

void GameEngine::ChoiceScene(std::string name)
{
	std::string mStr = "���� �� ���� :" + name;
	mDebugManager->Print(mStr, 0, 0 ,DebugManager::MSG_TYPE::MSG_ENGINE);
	
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
	mDebugManager->Print(temp,0,0, DebugManager::MSG_TYPE::MSG_LOAD);
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
