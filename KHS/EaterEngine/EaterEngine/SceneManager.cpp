#include "SceneManager.h"
#include "ObjectManager.h"
#include "Scene.h"

SceneManager* SceneManager::Instance = nullptr;
SceneManager::SceneManager()
{
	NowScene = nullptr;
}

SceneManager::~SceneManager()
{

}


void SceneManager::SetName(std::string Name)
{
	SceneName = Name;
}

void SceneManager::LoadScene(std::string SceneName)
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

void SceneManager::SceneUpdate()
{
	//��ũ�� ���� ������Ʈ�ϰ� �״��� ���۳�Ʈ�� ������Ʈ
	NowScene->Update();
	///��������?
}

SceneManager* SceneManager::GM()
{
	if (Instance == nullptr)
	{
		Instance = new SceneManager;
	}

	return Instance;
}

