#pragma once

#include <map>
#include <string>
class Scene;

/// <summary>
/// 스크린을 관리 해주는 스크린 매니저
/// </summary>

class SceneManager
{
public:
	SceneManager();
	~SceneManager();


	//DLL에서 템플릿 못쓰는줄알고..방법찾음 고치자
	Scene* CreateScene(std::string name);


	void LoadScene(std::string SceneName);	//스크린 선택
	void Delete();
	void SceneStart();		//스크린의 Awack Start함수를 실행
	void SceneUpdate();		//스크린의 Update 함수를 실행
private:
	//현재 스크린
	Scene* NowScene;

	//스크린 리스트
	std::map<std::string, Scene*> SceneList;
};
