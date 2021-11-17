#include "SceneManager.h"
#include "ObjectManager.h"
#include "DebugManager.h"
#include "Scene.h"

SceneManager::SceneManager()
{
	NowScene = nullptr;
}

SceneManager::~SceneManager()
{

}

void SceneManager::PushScene(Scene* mScene, std::string SceneName)
{
	SceneList.insert({ SceneName,mScene});
}

void SceneManager::Initialize()
{

}

void SceneManager::ChoiceScene(std::string mSceneName)
{
	SceneName = mSceneName;
	//���� �����Ҷ����ƴ� � ���� �������ִٰ� �ٸ������� ������
	if (NowScene != nullptr)
	{
		NowScene->End();

		NowScene = nullptr;
	}

	if (SceneList.find(SceneName) == SceneList.end())
	{
		//ã�� ������ ��� �����ڵ�
	}

	NowScene = SceneList[SceneName];
}


void SceneManager::Delete()
{
	NowScene = nullptr;

	//��� ��ũ�� ����
	SceneList.clear();
}

void SceneManager::SceneStart()
{
	NowScene->Awake();
	NowScene->Start();
}

void SceneManager::SceneEnd()
{
	if (NowScene != nullptr)
	{
		NowScene->End();
	}
}

void SceneManager::Update()
{
	std::string temp = "���� ���õ� �� :" + SceneName;
	DebugManager::Print(temp, 80, 2, DebugManager::MSG_TYPE::MSG_ENGINE);

	//��ũ�� ���� ������Ʈ�ϰ� �״��� ���۳�Ʈ�� ������Ʈ
	NowScene->Update();
	///��������?
}


