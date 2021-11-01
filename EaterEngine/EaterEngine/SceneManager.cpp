#include "SceneManager.h"
#include "ObjectManager.h"
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

void SceneManager::ChoiceScene(std::string SceneName)
{
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
	//��ũ�� ���� ������Ʈ�ϰ� �״��� ���۳�Ʈ�� ������Ʈ
	NowScene->Update();
	///��������?
}


