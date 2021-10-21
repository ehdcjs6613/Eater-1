#pragma once
#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

#include <string>
#include <windows.h>
class GameObject;
class Scene;
class FBXModel;


extern "C"
{
	EATER_ENGINEDLL void StartEngine(HWND _g_hWnd);		//GameEngine 시작
	EATER_ENGINEDLL void EndEngine();					//GameEngine 종료
	EATER_ENGINEDLL void UpdateEngine();				//GameEngine 업데이트


	EATER_ENGINEDLL GameObject* Instance();					//오브젝트 생성
	EATER_ENGINEDLL void		Destroy(GameObject* obj);	//오브젝트 삭제


	EATER_ENGINEDLL void ChoiceScene(std::string name);		//스크린 선택
	EATER_ENGINEDLL void StartScene();						//스크린 넣기
	EATER_ENGINEDLL Scene* CreateScene(std::string name);	//스크린 생성


	EATER_ENGINEDLL void LoadMesh(std::string mMeshName, bool Scale = true,bool LoadAnime = false);	//매쉬 로드
	EATER_ENGINEDLL void LoadMeshPath(std::string mPath);	//매쉬 로드 경로

	//매쉬를 가져옴
	EATER_ENGINEDLL	FBXModel* GetMesh(std::string mMeshName);

	
}
