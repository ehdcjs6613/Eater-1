#pragma once
#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

#include "GameEngine.h"
#include <functional>
#include <string>
#include <windows.h>


class GameObject;
class Scene;
extern GameEngine* gGameEngine;

extern "C" EATER_ENGINEDLL void EngineInitialize(HWND _g_hWnd);		//GameEngine 시작
extern "C" EATER_ENGINEDLL void EndEngine();						//GameEngine 종료
extern "C" EATER_ENGINEDLL void UpdateEngine();						//GameEngine 업데이트
extern "C" EATER_ENGINEDLL void OnReSize(int X,int Y);				//윈도우 사이즈 재조정	

///게임 오브젝트 생성
extern "C" EATER_ENGINEDLL GameObject*	Instance(std::string ObjName= "GameObject");//오브젝트 생성
extern "C" EATER_ENGINEDLL void			Destroy(GameObject* obj);					//오브젝트 삭제


extern "C" EATER_ENGINEDLL void ChoiceScene(std::string name);		//스크린 선택
extern "C" EATER_ENGINEDLL void StartScene();						//스크린 넣기


///스크린 생성하기
template<typename T>
EATER_ENGINEDLL void CreateScene(std::string Name)
{ 
	T* temp = new T();
	CreateScene(temp,Name);
};
EATER_ENGINEDLL void CreateScene(Scene* mSceneTemp,std::string SceneName);


///매쉬 불러오기
extern "C" EATER_ENGINEDLL void LoadMesh(std::string mMeshName, bool Scale = true,bool LoadAnime = false);	//매쉬 로드
extern "C" EATER_ENGINEDLL void LoadMeshPath(std::string mPath);											//매쉬 로드 경로
extern "C" EATER_ENGINEDLL void LoadTesture(std::string mPath);
extern "C" EATER_ENGINEDLL void LoadTesturePath(std::string mPath);


///키입력
extern "C" EATER_ENGINEDLL bool  GetKeyDown(byte number);	//키다운
extern "C" EATER_ENGINEDLL bool  GetKeyUp(byte number);		//키업
extern "C" EATER_ENGINEDLL bool  GetKey(byte number);		//키누르고있을때
extern "C" EATER_ENGINEDLL bool  GetTogle(byte number);		//키 토글
extern "C" EATER_ENGINEDLL float GetMousePosX();			//마우스 위치 X
extern "C" EATER_ENGINEDLL float GetMousePosY();			//마우스 위치 Y