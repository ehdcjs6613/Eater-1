#pragma once
#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

#include <string>
class SceneManager;
class GameObject;
class Scene;


extern "C"
{
	EATER_ENGINEDLL void StartEngine();		//GameEngine 시작
	EATER_ENGINEDLL void EndEngine();		//GameEngine 종료
	EATER_ENGINEDLL void UpdateEngine();	//GameEngine 업데이트


	EATER_ENGINEDLL GameObject* Instance();							//오브젝트 생성
	EATER_ENGINEDLL void		Destroy(GameObject* obj);			//오브젝트 삭제


	EATER_ENGINEDLL void ChoiceScene(std::string name);					//스크린을 생성한다
	EATER_ENGINEDLL void StartScene();	//스크린 넣기

	

	//스크린 생성
	EATER_ENGINEDLL Scene* CreateScene(std::string name);


	
}
