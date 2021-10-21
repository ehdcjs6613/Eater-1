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



Scene* SceneManager::CreateScene(std::string name)
{
	Scene* temp = new Scene();
	temp->Name = name;
	//temp->PushFunction(mAwake, mStart, mUpdate, mEnd);
	SceneList.insert({ name,temp });
	return temp;
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
