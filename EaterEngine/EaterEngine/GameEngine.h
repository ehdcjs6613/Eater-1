#pragma once
#include <windows.h>
#include <string>
#include "EaterEngineDLL.h"

/// <summary>
/// 전체 게임 엔진을 총괄하는 게임엔진 클래스
/// 커다란 게임엔진 틀
/// </summary>

//각종 매니저들
class DebugManager;
class LoadManager;
class ObjectManager;
class SceneManager;
class KeyinputManager;
class GraphicEngineManager;

class HsGraphic;
class Scene;
//게임 오브젝트
class GameObject;

class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	
public:
	///클라이언트 에서 만질 함수들
	///게임 엔진 관련 함수들
	EATER_ENGINEDLL void Initialize(HWND gHwnd,bool mConsoleDebug = true);//초기화
	EATER_ENGINEDLL void Update();				//엔진 가동
	EATER_ENGINEDLL void Finish();				//엔진 중지
	EATER_ENGINEDLL void OnResize(int Change_Width, int Change_Height); //리사이즈
public:
	///오브젝트 관련(오브젝트 매니저)
	EATER_ENGINEDLL GameObject* Instance(std::string ObjName = "GameObject");	//obj 생성
	EATER_ENGINEDLL void		Destroy(GameObject* obj);						//obj 삭제
public:
	///스크린 관련
	EATER_ENGINEDLL void PushScene(Scene* mScene, std::string name);	//씬 생성		
	EATER_ENGINEDLL void ChoiceScene(std::string name);					//씬 선택
public:
	///로드 관련 
	EATER_ENGINEDLL void LoadMeshPath(std::string mPath);
	EATER_ENGINEDLL void LoadTexturePath(std::string mPath);
	EATER_ENGINEDLL void LoadMesh(std::string mMeshName, bool Scale = true, bool LoadAnime = false);
	EATER_ENGINEDLL void LoadTexture(std::string mMeshName);
public:
	///키관련 
	EATER_ENGINEDLL bool  GetKeyDown(byte number);	//키다운
	EATER_ENGINEDLL bool  GetKeyUp(byte number);	//키업
	EATER_ENGINEDLL bool  GetKey(byte number);		//키누르고있을때
	EATER_ENGINEDLL bool  GetTogle(byte number);	//키 on/off
	EATER_ENGINEDLL float GetMousePosX();			//마우스 위치 X
	EATER_ENGINEDLL float GetMousePosY();			//마우스 위치 Y
private:
	///각종 매니저들
	ObjectManager*			mObjectManager;		//오브젝트 관리 매니저
	DebugManager*			mDebugManager;		//디버깅매니저
	LoadManager*			mLoadManager;		//로드 관련 매니저
	SceneManager*			mSceneManager;		//스크린 관리 매니저
	KeyinputManager*		mKeyManager;		//키인풋 관련 매니저
	GraphicEngineManager*	mGraphicManager;	//그래픽엔진 관리 매니저
private:
	///클라쪽에서 받아야 하는 데이터
	HWND mHwnd; //핸들
	int WinSizeWidth;	//윈도우 사이즈 가로
	int WinSizeHeight;	//윈도우 사이즈 세로
	bool ConsoleDebug;
private:
};

