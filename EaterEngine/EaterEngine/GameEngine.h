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
class TimeManager;
class MaterialManager;
class LightManager;
class PhysManager;

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
	void Initialize(HWND gHwnd,bool mConsoleDebug = true);	//�ʱ�ȭ
	void Update();											//���� ����
	void Finish();											//���� ����
	void OnResize(int Change_Width, int Change_Height);		//��������
public:
	///������Ʈ ����(������Ʈ �Ŵ���)
	GameObject* Instance(std::string ObjName = "GameObject");			//obj ���� (�� ���ӿ�����Ʈ)
	void		Destroy(GameObject* obj);								//obj ����
public:
	///��ũ�� ����
	void PushScene(Scene* mScene, std::string name);	//�� ����		
	void ChoiceScene(std::string name);					//�� ����
public:
	///�ε� ���� 
	void LoadMeshPath(std::string mPath);
	void LoadTexturePath(std::string mPath);
	void LoadMesh(std::string mMeshName, bool Scale = true, bool LoadAnime = false);
	void LoadTexture(std::string mMeshName);
public:
	///Ű���� 
	bool  GetKeyDown(byte number);	//Ű�ٿ�
	bool  GetKeyUp(byte number);	//Ű��
	bool  GetKey(byte number);		//Ű������������
	bool  GetTogle(byte number);	//Ű on/off
	float GetMousePosX();			//���콺 ��ġ X
	float GetMousePosY();			//���콺 ��ġ Y
public:
	///ī�޶� ����
	//Vector3 GetCameraLocalPosition_UP();
	//Vector3 GetCameraLocalPosition_Right();
	//Vector3 GetCameraLocalPosition_Look();
public:
	///�ð� ����
	float GetdeltaTime();

private:
	void CreateObject();			//�⺻ ���� ������Ʈ

private:
	///���� �Ŵ�����
	ObjectManager*			mObjectManager;		// ������Ʈ ���� �Ŵ���
	DebugManager*			mDebugManager;		// �����Ŵ���
	LoadManager*			mLoadManager;		// �ε� ���� �Ŵ���
	SceneManager*			mSceneManager;		// ��ũ�� ���� �Ŵ���
	KeyinputManager*		mKeyManager;		// Ű��ǲ ���� �Ŵ���
	GraphicEngineManager*	mGraphicManager;	// �׷��ȿ��� ���� �Ŵ���
	TimeManager*			mTimeManager;		// �ð� ���� Ÿ�ӸŴ���
	MaterialManager*		mMaterialManager;	// ���׸��� ���� �Ŵ���
	LightManager*			mLightManager;		// ����Ʈ ���� �Ŵ���
	PhysManager*			mPhysManager;		// ���� ���� �Ŵ���
private:
	///Ŭ���ʿ��� �޾ƾ� �ϴ� ������
	HWND mHwnd; //�ڵ�
	int WinSizeWidth;	//������ ������ ����
	int WinSizeHeight;	//������ ������ ����
	bool ConsoleDebug;
private:
};

