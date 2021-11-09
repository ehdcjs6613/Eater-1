#pragma once

#include "EaterEngineDLL.h"

#include <string>
#include "Component.h"
/// <summary>
/// �Ž������� �ļ����� �޾ƿ��� �����صδ� ���۳�Ʈ
/// </summary>

class LoadMeshData;
class Transform;
class ObjectManager;

class  MeshFilter : public Component
{
public:
	EATER_ENGINEDLL MeshFilter();
	virtual ~MeshFilter();

	virtual void Awake() override;

	static void SetObjMananager(ObjectManager* obj);
public:
	//�޽��� �̸��� ������ ������ �ε�
	EATER_ENGINEDLL void SetMeshName(std::string mMeshName);

	//���ӿ�����Ʈ�� LoadData�� �����ش�
	void PushModelData(LoadMeshData* mModel);

	//LoadMeshData�� ���ӿ� ����� ������Ʈ�� �����ϸ鼭 ���� �־��ش�
	void ChangeLoadMeshData(LoadMeshData* data,Transform* parent);

	//Transform�� �����Ѵ�
	void LinkHierarchy(Transform* my,Transform*parent);
private:
	//�Ž� �ε忩��
	bool isLoad;

	std::string MeshName;

	static ObjectManager* OBJ_Manager;

	
};

