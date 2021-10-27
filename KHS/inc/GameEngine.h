#pragma once
#include <windows.h>
//#include "SceneManager.h"
#include <string>

#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

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
class GraphicEngine;

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
	void Initialize(HWND gHwnd);//�ʱ�ȭ
	void Update();				//���� ����
	void Finish();				//���� ����
public:
	///������Ʈ ����(������Ʈ �Ŵ���)
	GameObject* Instance(std::string ObjName = "GameObject");	//obj ����
	void		Destroy(GameObject* obj);						//obj ����
public:
	///Ŭ���ʿ��� ���ϰ� ������Ʈ �����ϱ�����
	void CreateCamera();	//ī�޶� ����
public:
	///��ũ�� ����
	void PushScene(Scene* mScene, std::string name);	//�� ����		
	void ChoiceScene(std::string name);					//�� ����
public:
	///�ε� ���� 
	void LoadMesh(std::string mMeshName, bool Scale = true, bool LoadAnime = false);
	void LoadMeshPath(std::string mPath);
public:
	///Ű���� 
	bool  GetKeyDown(byte number);	//Ű�ٿ�
	bool  GetKeyUp(byte number);	//Ű��
	bool  GetKey(byte number);		//Ű������������
	bool  GetTogle(byte number);	//Ű on/off
	float GetMousePosX();			//���콺 ��ġ X
	float GetMousePosY();			//���콺 ��ġ Y
private:
	///���� �Ŵ�����
	ObjectManager*		mObjectManager;		//������Ʈ ���� �Ŵ���
	DebugManager*		mDebugManager;		//�����Ŵ���
	LoadManager*		mLoadManager;		//�ε� ���� �Ŵ���
	SceneManager*		mSceneManager;		//��ũ�� ���� �Ŵ���
	KeyinputManager*	mKeyManager;		//Ű��ǲ ���� �Ŵ���
private:
	///Ŭ���ʿ��� �޾ƾ� �ϴ� ������
	HWND mHwnd; //�ڵ�
	int WinSizeWidth;	//������ ������ ����
	int WinSizeHeight;	//������ ������ ����
private:
	///�׷��� ����
	GraphicEngine* NowGraphicEngine;

	//�׽�Ʈ�� ����
	








};

