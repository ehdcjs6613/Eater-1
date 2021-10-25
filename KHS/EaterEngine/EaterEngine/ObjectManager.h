#pragma once

#include <map>
#include <vector>
#include <queue>
#include <windows.h>
#include "EngineData.h"
#include <functional>
#include "Delegate.h"
#include "../SharedData.h"

#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

class Camera;
class FBXModel;
class GameObject;
class Component;
class DH3DEngine;
class MeshFilter;

class ObjectManager
{
public:
	~ObjectManager();

	//������ ������Ʈ�� �־���
	EATER_ENGINEDLL void PushCreateObject(GameObject* obj);
	//����ī�޶� ������Ʈ�� �־��ش�
	EATER_ENGINEDLL void PushMainCamObject(GameObject* obj);

	//������ ������Ʈ�� �־���(���Լ��� �����ų�ܰ迡�� ������Ʈ�� ������������ ������ ���� ��������)
	EATER_ENGINEDLL void PushDeleteObject(GameObject* obj);

	//���� ������Ʈ ����Ʈ�� ����ִ� ������Ʈ�� ���۳�Ʈ ����Ʈ�� ���� ����
	EATER_ENGINEDLL void AllDeleteObject();

	//���� �ʱ�ȭ
	EATER_ENGINEDLL void CreateEngine(HWND _g_hWnd);

	/// <summary>
	/// ���� �ܰ�
	/// </summary>
	EATER_ENGINEDLL void PushStart(Component* obj);
	EATER_ENGINEDLL void PushAwake(Component* obj);

	/// <summary>
	/// ������Ʈ �ܰ�
	/// </summary>
	EATER_ENGINEDLL void PushStartUpdate(Component* obj);
	EATER_ENGINEDLL void PushUpdate(Component* obj);
	EATER_ENGINEDLL void PushEndUpdate(Component* obj);



	//������Ʈ �Լ� ����Ʈ�� �����Ŵ
	void PlayUpdate();
	void PlayStart();


	//������Ʈ�� ������ �Լ�����Ʈ�� ��� ������
	void ClearFunctionList();

	//�̱��� Ŭ����
	EATER_ENGINEDLL static ObjectManager* GM();
private:
	static ObjectManager* instance;
	ObjectManager();


	std::vector<GameObject*> ObjectList;
	std::queue<GameObject*> DeleteList;
	GlobalData* Global;



	/// <summary>
	/// �׽�Ʈ��
	/// </summary>
	std::string MeshName;
	FBXModel* MeshFilterData;


	DH3DEngine* pTest_Engine;
	OneFrameData* pTest_OFD;
	SharedRenderData* pTest_SRD;
	DHParser::Mesh* pTest_Mesh;

	void Test();
	Camera* MainCam;






	/// <summary>
	/// ���۴ܰ� �ѹ��� �����
	/// </summary>
	Delegate_Map<Component> AwakeFunction;		//���۴ܰ� ���� ���� ����Ǵ� �Լ�
	Delegate_Map<Component> StartFunction;		//���۴ܰ��� ����Ǵ� �Լ�


	/// <summary>
	/// ������Ʈ �ܰ� �����Ӹ��� ����
	/// </summary>
	Delegate_Map<Component> StartUpdate;		//������� ���۵Ǵ� ������Ʈ
	Delegate_Map<Component> Update;				//����Ʈ  �߰��ܰ��� ���۵Ǵ� ������Ʈ
	Delegate_Map<Component> EndUpdate;			//���� �������� ����Ǵ� ������Ʈ


	

	//������Ʈ�� �����Ѵ�
	void DeleteObject();
	void DeleteComponent(Component* cpt);
};