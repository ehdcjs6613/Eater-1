#pragma once
#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

#include "SceneManager.h"
#include <string>
#include <windows.h>


class SceneManager;
class MeshFilter;
class GameObject;
class Scene;
class FBXModel;




extern "C" EATER_ENGINEDLL void StartEngine(HWND _g_hWnd);		//GameEngine 시작
extern "C" EATER_ENGINEDLL void EndEngine();					//GameEngine 종료
extern "C" EATER_ENGINEDLL void UpdateEngine();				//GameEngine 업데이트


extern "C" EATER_ENGINEDLL GameObject*	Instance();					//오브젝트 생성
extern "C" EATER_ENGINEDLL void			Destroy(GameObject* obj);	//오브젝트 삭제


extern "C" EATER_ENGINEDLL void ChoiceScene(std::string name);		//스크린 선택
extern "C" EATER_ENGINEDLL void StartScene();						//스크린 넣기


///스크린 생성하기
template<typename T>
EATER_ENGINEDLL void CreateScene(std::string Name)
{ 
	SceneManager::GM()->SetName(Name);
	SceneManager::GM()->CreateScene<T>(); 
};


///매쉬 불러오기
extern "C" EATER_ENGINEDLL void LoadMesh(std::string mMeshName, bool Scale = true,bool LoadAnime = false);	//매쉬 로드
extern "C" EATER_ENGINEDLL void LoadMeshPath(std::string mPath);											//매쉬 로드 경로


///기본 오브젝트들 간단하게생성하기
//메인 카메라
extern "C" EATER_ENGINEDLL GameObject* CreateMainCamera(float x = 0,float y = 0,float z = 0);
extern "C" EATER_ENGINEDLL void	ChoiceMainCamera(GameObject* obj);


///키입력
extern "C" EATER_ENGINEDLL bool GetKeyDown(byte number);
extern "C" EATER_ENGINEDLL bool GetKeyUp(byte number);
extern "C" EATER_ENGINEDLL bool GetKey(byte number);
extern "C" EATER_ENGINEDLL float GetMousePosX();
extern "C" EATER_ENGINEDLL float GetMousePosY();