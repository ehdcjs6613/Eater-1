#pragma once
#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

#include <string>
class GameObject;
class Scene;


extern "C"
{
	EATER_ENGINEDLL void StartEngine();		//GameEngine 시작
	EATER_ENGINEDLL void EndEngine();		//GameEngine 종료
	EATER_ENGINEDLL void UpdateEngine();	//GameEngine 업데이트


	EATER_ENGINEDLL GameObject* CreateGameObject();					//오브젝트 생성
	EATER_ENGINEDLL void		DeleteGameObject(GameObject* obj);	//오브젝트 삭제


	EATER_ENGINEDLL void ChoiceScene(std::string name);					//스크린을 생성한다
	EATER_ENGINEDLL void StartScene();	//스크린 넣기

	//스크린 생성
	EATER_ENGINEDLL void CreateScene
	(
		std::string name,	//스크린 이름
		void(*mAwake)(),	//스크린 Awake 함수포인터
		void(*mStart)(),	//스크린 Start	함수포인터
		void(*mUpdate)(),	//스크린 Update  함수포인터
		void(*mEnd)()		//스크린 End		함수포인터
	);	

}
