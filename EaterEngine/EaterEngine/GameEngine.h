#pragma once
#include <windows.h>
#include <string>
#include "EaterEngineDLL.h"

/// <summary>
/// ��ü ���� ������ �Ѱ��ϴ� ���ӿ��� Ŭ����
/// Ŀ�ٶ� ���ӿ��� Ʋ
/// </summary>

//���� �Ŵ�����
class DebugManager;
class LoadManager;
class ObjectManager;
class SceneManager;
class KeyinputManager;
class GraphicEngineManager;

class HsGraphic;
class Scene;
//���� ������Ʈ
class GameObject;

class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	
public:
	///Ŭ���̾�Ʈ ���� ���� �Լ���
	///���� ���� ���� �Լ���
	EATER_ENGINEDLL void Initialize(HWND gHwnd,bool mConsoleDebug = true);//�ʱ�ȭ
	EATER_ENGINEDLL void Update();				//���� ����
	EATER_ENGINEDLL void Finish();				//���� ����
	EATER_ENGINEDLL void OnResize(int Change_Width, int Change_Height); //��������
public:
	///������Ʈ ����(������Ʈ �Ŵ���)
	EATER_ENGINEDLL GameObject* Instance(std::string ObjName = "GameObject");	//obj ����
	EATER_ENGINEDLL void		Destroy(GameObject* obj);						//obj ����
public:
	///��ũ�� ����
	EATER_ENGINEDLL void PushScene(Scene* mScene, std::string name);	//�� ����		
	EATER_ENGINEDLL void ChoiceScene(std::string name);					//�� ����
public:
	///�ε� ���� 
	EATER_ENGINEDLL void LoadMeshPath(std::string mPath);
	EATER_ENGINEDLL void LoadTexturePath(std::string mPath);
	EATER_ENGINEDLL void LoadMesh(std::string mMeshName, bool Scale = true, bool LoadAnime = false);
	EATER_ENGINEDLL void LoadTexture(std::string mMeshName);
public:
	///Ű���� 
	EATER_ENGINEDLL bool  GetKeyDown(byte number);	//Ű�ٿ�
	EATER_ENGINEDLL bool  GetKeyUp(byte number);	//Ű��
	EATER_ENGINEDLL bool  GetKey(byte number);		//Ű������������
	EATER_ENGINEDLL bool  GetTogle(byte number);	//Ű on/off
	EATER_ENGINEDLL float GetMousePosX();			//���콺 ��ġ X
	EATER_ENGINEDLL float GetMousePosY();			//���콺 ��ġ Y
private:
	///���� �Ŵ�����
	ObjectManager*			mObjectManager;		//������Ʈ ���� �Ŵ���
	DebugManager*			mDebugManager;		//�����Ŵ���
	LoadManager*			mLoadManager;		//�ε� ���� �Ŵ���
	SceneManager*			mSceneManager;		//��ũ�� ���� �Ŵ���
	KeyinputManager*		mKeyManager;		//Ű��ǲ ���� �Ŵ���
	GraphicEngineManager*	mGraphicManager;	//�׷��ȿ��� ���� �Ŵ���
private:
	///Ŭ���ʿ��� �޾ƾ� �ϴ� ������
	HWND mHwnd; //�ڵ�
	int WinSizeWidth;	//������ ������ ����
	int WinSizeHeight;	//������ ������ ����
	bool ConsoleDebug;
private:
};

