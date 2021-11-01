#pragma once
#include <windows.h>
#include <string>
#include "SharedData.h"


#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

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
class GraphicEngine;
class Scene;
//게임 오브젝트
class GameObject;

class DH3DEngine;

class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	
public:
	///클라이언트 에서 만질 함수들
	///게임 엔진 관련 함수들
	void Initialize(HWND gHwnd,bool mConsoleDebug = true);//초기화
	void Update();				//엔진 가동
	void Finish();				//엔진 중지
	void OnResize(float Change_Width, float Change_Height); //리사이즈
public:
	///오브젝트 관련(오브젝트 매니저)
	GameObject* Instance(std::string ObjName = "GameObject");	//obj 생성
	void		Destroy(GameObject* obj);						//obj 삭제
public:
	///스크린 관련
	void PushScene(Scene* mScene, std::string name);	//씬 생성		
	void ChoiceScene(std::string name);					//씬 선택
public:
	///로드 관련 
	void LoadMesh(std::string mMeshName, bool Scale = true, bool LoadAnime = false);
	void LoadMeshPath(std::string mPath);

	
public:
	///키관련 
	bool  GetKeyDown(byte number);	//키다운
	bool  GetKeyUp(byte number);	//키업
	bool  GetKey(byte number);		//키누르고있을때
	bool  GetTogle(byte number);	//키 on/off
	float GetMousePosX();			//마우스 위치 X
	float GetMousePosY();			//마우스 위치 Y
private:
	///각종 매니저들
	ObjectManager*		mObjectManager;		//오브젝트 관리 매니저
	DebugManager*		mDebugManager;		//디버깅매니저
	LoadManager*		mLoadManager;		//로드 관련 매니저
	SceneManager*		mSceneManager;		//스크린 관리 매니저
	KeyinputManager*	mKeyManager;		//키인풋 관련 매니저

private:
	///클라쪽에서 받아야 하는 데이터
	HWND mHwnd; //핸들
	int WinSizeWidth;	//윈도우 사이즈 가로
	int WinSizeHeight;	//윈도우 사이즈 세로
	bool ConsoleDebug;
private:
	///그래픽 엔진
	GraphicEngine* NowGraphicEngine;

	
	//테스트용 엔진
	DH3DEngine*			pTest_Engine;
	OneFrameData*		pTest_OFD;
	SharedRenderData*	pTest_SRD;
	DHParser::Mesh*		pTest_Mesh;
};

