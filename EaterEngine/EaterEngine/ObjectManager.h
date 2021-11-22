#pragma once

#include <map>
#include <vector>
#include <queue>
#include <windows.h>
#include "EngineData.h"
#include <functional>
#include "Delegate.h"
#include "EaterEngineDLL.h"
#include "BaseManager.h"


class Camera;
class FBXModel;
class GameObject;
class Component;
class MeshFilter;

class ObjectManager : public BaseManager
{
public:
	~ObjectManager();
	ObjectManager();

	//������ ������Ʈ�� �־���
	void PushCreateObject(GameObject* obj);

	//�����Ǹ� �ȵǴ� ������Ʈ ����Ʈ
	void PushDontDeleteObject(GameObject* obj);

	//������ ������Ʈ�� �־���(���Լ��� �����ų�ܰ迡�� ������Ʈ�� ������������ ������ ���� ��������)
	void PushDeleteObject(GameObject* obj);

	//���� ������Ʈ ����Ʈ�� ����ִ� ������Ʈ�� ���۳�Ʈ ����Ʈ�� ���� ����
	void AllDeleteObject();

	//���� �ʱ�ȭ
	void Initialize(HWND _g_hWnd);

	/// ���� �ܰ�
	static void PushStart(Component* obj);
	static void PushAwake(Component* obj);

	/// ���۳�Ʈ�� ������Ʈ �Լ��� �־��ش�
	static void PushStartUpdate(Component* obj);
	static void PushTransformUpdate(Component* obj);
	static void PushPhysicsUpdate(Component* obj);
	static void PushEndUpdate(Component* obj);
	static void PushUpdate(Component* obj);

	/// ������Ʈ �Լ� ����Ʈ�� �����Ŵ
	void PlayUpdate();

	///�׷��� ���������� ���� �����޼���ť�� ����
	void CreateRenderQueue();

	/// ������Ʈ�� ������ �Լ�����Ʈ�� ��� ������
	void ClearFunctionList();

	///������Ʈ�� �����Ѵ�
	void DeleteObject();

	std::queue<MeshData*>* GetRenderQueue();
	std::queue<MeshData*>* GetShadowQueue();
	
private:
	///������Ʈ ����Ʈ
	std::vector<GameObject*> ObjectList;
	///�����Ǹ� �ȵǴ� ������Ʈ ����Ʈ
	std::vector<GameObject*> DontDeleteObjectList;
	///���������� ��γ����� �������� ������ ������Ʈ����Ʈ
	std::queue<GameObject*> DeleteList;


	///�׷��ȿ��������� ������ �����͵�
	std::queue<MeshData*> RenderData;
	std::queue<MeshData*> ShadowData;
	std::queue<MeshData*> UIData;

	/// ���۴ܰ� �ѹ��� �����
	static Delegate_Map AwakeFunction;		//���۴ܰ� ���� ���� ����Ǵ� �Լ�
	static Delegate_Map StartFunction;		//���۴ܰ��� ����Ǵ� �Լ�


	/// ������Ʈ �ܰ� �����Ӹ��� ����
	static Delegate_Map StartUpdate;		//������� ���۵Ǵ� ������Ʈ
	static Delegate_Map TransformUpdate;	//�̵� ��� ������Ʈ
	static Delegate_Map PhysicsUpdate;		//���� �ൿ ������Ʈ
	static Delegate_Map Update;				//����Ʈ  �߰��ܰ��� ���۵Ǵ� ������Ʈ
	static Delegate_Map EndUpdate;			//���� �������� ����Ǵ� ������Ʈ

	//���۳�Ʈ �������� �ش� �Լ������Ϳ� �־��� �����͸� ����������
	void DeleteComponent(Component* cpt);
	
};