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


extern "C"
{
	EATER_ENGINEDLL void StartEngine(HWND _g_hWnd);		//GameEngine ����
	EATER_ENGINEDLL void EndEngine();					//GameEngine ����
	EATER_ENGINEDLL void UpdateEngine();				//GameEngine ������Ʈ


	EATER_ENGINEDLL GameObject* Instance();					//������Ʈ ����
	EATER_ENGINEDLL void		Destroy(GameObject* obj);	//������Ʈ ����


	EATER_ENGINEDLL void ChoiceScene(std::string name);		//��ũ�� ����
	EATER_ENGINEDLL void StartScene();						//��ũ�� �ֱ�
	EATER_ENGINEDLL Scene* CreateScene(std::string name);	//��ũ�� ����


	EATER_ENGINEDLL void LoadMesh(std::string mMeshName,bool LoadAnime = false);	//�Ž� �ε�
	EATER_ENGINEDLL void LoadMeshPath(std::string mPath);							//�Ž� �ε� ���
	
}
