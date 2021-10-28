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

extern "C" EATER_ENGINEDLL void EngineInitialize(HWND _g_hWnd);		//GameEngine ����
extern "C" EATER_ENGINEDLL void EndEngine();						//GameEngine ����
extern "C" EATER_ENGINEDLL void UpdateEngine();						//GameEngine ������Ʈ
extern "C" EATER_ENGINEDLL void OnReSize(int X,int Y);				//������ ������ ������	


extern "C" EATER_ENGINEDLL GameObject*	Instance(std::string ObjName= "GameObject");//������Ʈ ����
extern "C" EATER_ENGINEDLL void			Destroy(GameObject* obj);					//������Ʈ ����


extern "C" EATER_ENGINEDLL void ChoiceScene(std::string name);		//��ũ�� ����
extern "C" EATER_ENGINEDLL void StartScene();						//��ũ�� �ֱ�


///��ũ�� �����ϱ�
template<typename T>
EATER_ENGINEDLL void CreateScene(std::string Name)
{ 
	T* temp = new T();
	CreateScene(temp,Name);
};
EATER_ENGINEDLL void CreateScene(Scene* mSceneTemp,std::string SceneName);


///�Ž� �ҷ�����
extern "C" EATER_ENGINEDLL void LoadMesh(std::string mMeshName, bool Scale = true,bool LoadAnime = false);	//�Ž� �ε�
extern "C" EATER_ENGINEDLL void LoadMeshPath(std::string mPath);											//�Ž� �ε� ���


///�⺻ ������Ʈ�� �����ϰԻ����ϱ�
//���� ī�޶�
extern "C" EATER_ENGINEDLL GameObject* CreateMainCamera(float x = 0,float y = 0,float z = 0);
extern "C" EATER_ENGINEDLL void	ChoiceMainCamera(GameObject* obj);


///Ű�Է�
extern "C" EATER_ENGINEDLL bool  GetKeyDown(byte number);	//Ű�ٿ�
extern "C" EATER_ENGINEDLL bool  GetKeyUp(byte number);		//Ű��
extern "C" EATER_ENGINEDLL bool  GetKey(byte number);		//Ű������������
extern "C" EATER_ENGINEDLL bool  GetTogle(byte number);		//Ű ���
extern "C" EATER_ENGINEDLL float GetMousePosX();			//���콺 ��ġ X
extern "C" EATER_ENGINEDLL float GetMousePosY();			//���콺 ��ġ Y