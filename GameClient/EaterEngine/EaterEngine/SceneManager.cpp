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



void SceneManager::CreateScene(std::string name, void(*mAwake)(), void(*mStart)(), void(*mUpdate)(), void(*mEnd)())
{
	Scene* temp = new Scene();
	temp->Name = name;
	temp->PushFunction(mAwake, mStart, mUpdate, mEnd);
	SceneList.insert({ name,temp });
}

void SceneManager::ChoiceScene(std::string SceneName)
{
	if (SceneList.find(SceneName) == SceneList.end())
	{
		//찾지 못했을 경우 에러코드
	}

	NowScene = SceneList[SceneName];


	//ObjectManager::GM()->PlayStart();
}

 
void SceneManager::Delete()
{
	NowScene = nullptr;
	//모든 스크린 삭제
	SceneList.clear();
}


void SceneManager::SceneStart()
{
	NowScene->Awake();
	NowScene->Start();
}

void SceneManager::SceneUpdate()
{
	//스크린 먼저 업데이트하고 그다음 컨퍼넌트들 업데이트
	NowScene->Update();
	///삭제여부?
}
