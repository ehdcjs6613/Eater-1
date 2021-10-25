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




extern "C" EATER_ENGINEDLL void StartEngine(HWND _g_hWnd);		//GameEngine ����
extern "C" EATER_ENGINEDLL void EndEngine();					//GameEngine ����
extern "C" EATER_ENGINEDLL void UpdateEngine();				//GameEngine ������Ʈ


extern "C" EATER_ENGINEDLL GameObject*	Instance();					//������Ʈ ����
extern "C" EATER_ENGINEDLL void			Destroy(GameObject* obj);	//������Ʈ ����


extern "C" EATER_ENGINEDLL void ChoiceScene(std::string name);		//��ũ�� ����
extern "C" EATER_ENGINEDLL void StartScene();						//��ũ�� �ֱ�


///��ũ�� �����ϱ�
template<typename T>
EATER_ENGINEDLL void CreateScene(std::string Name)
{ 
	SceneManager::GM()->SetName(Name);
	SceneManager::GM()->CreateScene<T>(); 
};


///�Ž� �ҷ�����
extern "C" EATER_ENGINEDLL void LoadMesh(std::string mMeshName, bool Scale = true,bool LoadAnime = false);	//�Ž� �ε�
extern "C" EATER_ENGINEDLL void LoadMeshPath(std::string mPath);											//�Ž� �ε� ���


///�⺻ ������Ʈ�� �����ϰԻ����ϱ�
//���� ī�޶�
extern "C" EATER_ENGINEDLL GameObject* CreateMainCamera(float x = 0,float y = 0,float z = 0);
extern "C" EATER_ENGINEDLL void	ChoiceMainCamera(GameObject* obj);


///Ű�Է�
extern "C" EATER_ENGINEDLL bool GetKeyDown(byte number);
extern "C" EATER_ENGINEDLL bool GetKeyUp(byte number);
extern "C" EATER_ENGINEDLL bool GetKey(byte number);
extern "C" EATER_ENGINEDLL float GetMousePosX();
extern "C" EATER_ENGINEDLL float GetMousePosY();