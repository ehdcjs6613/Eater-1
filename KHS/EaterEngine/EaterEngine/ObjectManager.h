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
	ObjectManager();

	//������ ������Ʈ�� �־���
	void PushCreateObject(GameObject* obj);

	//������ ������Ʈ�� �־���(���Լ��� �����ų�ܰ迡�� ������Ʈ�� ������������ ������ ���� ��������)
	void PushDeleteObject(GameObject* obj);

	//���� ������Ʈ ����Ʈ�� ����ִ� ������Ʈ�� ���۳�Ʈ ����Ʈ�� ���� ����
	void AllDeleteObject();

	//���� �ʱ�ȭ
	void Initialize(HWND _g_hWnd);

	/// ���� �ܰ�
	static EATER_ENGINEDLL void PushStart(Component* obj);
	static EATER_ENGINEDLL void PushAwake(Component* obj);

	/// ���۳�Ʈ�� ������Ʈ �Լ��� �־��ش�
	static EATER_ENGINEDLL void PushStartUpdate(Component* obj);
	static EATER_ENGINEDLL void PushTransformUpdate(Component* obj);
	static EATER_ENGINEDLL void PushPhysicsUpdate(Component* obj);
	static EATER_ENGINEDLL void PushEndUpdate(Component* obj);
	static EATER_ENGINEDLL void PushUpdate(Component* obj);

	/// ������Ʈ �Լ� ����Ʈ�� �����Ŵ
	void PlayUpdate();
	void PlayStart();

	///�׷��� ���������� ���� �����޼���ť�� ����
	void CreateRenderQueue();


	/// ������Ʈ�� ������ �Լ�����Ʈ�� ��� ������
	void ClearFunctionList();
private:
	std::vector<GameObject*> ObjectList;
	std::queue<GameObject*> DeleteList;

	///�׷��ȿ��������� ������ �����͵�
	std::queue<MeshData*> RenderData;
	GlobalData* Global;


	/// �׽�Ʈ��
	////////////////////////////////////////////
	std::string MeshName;
	FBXModel* MeshFilterData;

	DH3DEngine* pTest_Engine;

	OneFrameData* pTest_OFD;
	SharedRenderData* pTest_SRD;
	DHParser::Mesh* pTest_Mesh;

	void Test();
	////////////////////////////////////////////


	/// ���۴ܰ� �ѹ��� �����
	static Delegate_Map<Component> AwakeFunction;		//���۴ܰ� ���� ���� ����Ǵ� �Լ�
	static Delegate_Map<Component> StartFunction;		//���۴ܰ��� ����Ǵ� �Լ�


	/// ������Ʈ �ܰ� �����Ӹ��� ����
	static Delegate_Map<Component> StartUpdate;			//������� ���۵Ǵ� ������Ʈ
	static Delegate_Map<Component> TransformUpdate;		//�̵� ��� ������Ʈ
	static Delegate_Map<Component> PhysicsUpdate;		//���� �ൿ ������Ʈ
	static Delegate_Map<Component> Update;				//����Ʈ  �߰��ܰ��� ���۵Ǵ� ������Ʈ
	static Delegate_Map<Component> EndUpdate;			//���� �������� ����Ǵ� ������Ʈ


	///������Ʈ�� �����Ѵ�
	void DeleteObject();
	void DeleteComponent(Component* cpt);
};