#pragma once
#include <functional>
#include <map>
#include <string>
class Scene;

/// <summary>
/// 스크린을 관리 해주는 스크린 매니저
/// </summary>

#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif


class SceneManager
{
public:
	~SceneManager();

	template<typename T>
	void CreateScene(typename std::enable_if<std::is_base_of<Scene, T>::value, bool>::type t = std::is_base_of<Scene, T>::value);
	EATER_ENGINEDLL void SetName(std::string Name);

	void LoadScene(std::string SceneName);	//스크린 선택
	void Delete();
	void SceneStart();		//스크린의 Awack Start함수를 실행
	void SceneUpdate();		//스크린의 Update 함수를 실행


	
	static EATER_ENGINEDLL SceneManager* GM();
private:
	//현재 스크린
	Scene* NowScene;
	std::string SceneName;

	//스크린 리스트
	std::map<std::string, Scene*> SceneList;
private:
	//싱글톤
	SceneManager();
	static SceneManager* Instance;
};

template<typename T>
inline void SceneManager::CreateScene(typename std::enable_if<std::is_base_of<Scene, T>::value, bool>::type t)
{
	T* temp = new T();

	temp->AwakeFunction = std::bind(&T::Awake, temp);
	temp->StartFunction = std::bind(&T::Start, temp);
	temp->UpdateFunction = std::bind(&T::Update, temp);
	temp->EndFunction = std::bind(&T::End, temp);

	SceneList.insert({ SceneName, temp });
}
