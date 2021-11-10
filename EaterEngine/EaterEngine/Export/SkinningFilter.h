#pragma once

#include "EaterEngineDLL.h"
#include "Component.h"
#include <vector>
#include <string>

class LoadMeshData;
class Transform;
class ObjectManager;
class GameObject;

namespace ParserData 
{
	class Mesh;
}

namespace DirectX
{
	namespace SimpleMath
	{
		struct Matrix;
	}
}




class SkinningFilter :public Component
{
public:

	EATER_ENGINEDLL SkinningFilter();
	virtual EATER_ENGINEDLL ~SkinningFilter();

	virtual void Awake();
	//���� �־��ش�
	//�޽��� �̸��� ������ ������ �ε�
	EATER_ENGINEDLL void SetMeshName(std::string mMeshName);


	static void SetObjMananager(ObjectManager* obj);

private:
	//���ӿ�����Ʈ�� LoadData�� �����ش�
	void PushModelData(LoadMeshData* mModel);

	//LoadMeshData�� ���ӿ� ����� ������Ʈ�� �����ϸ鼭 ���� �־��ش�
	void ChangeLoadBoneData(LoadMeshData* data, Transform* parent);
	void ChangeLoadMeshData(LoadMeshData* data, Transform* parent);


	//Transform�� �����Ѵ�
	void LinkHierarchy(Transform* my, Transform* parent);

	//�Ž� �ε忩��
	bool isLoad;
	std::string MeshName;

	//��������
	std::vector<DirectX::SimpleMath::Matrix>* BoneTMList;	//�� ��Ʈ����
	std::vector<ParserData::Mesh*>* BoneList;				//�� �Ž�

	//��Ű�� ������Ʈ
	GameObject* SkinningObject;




	static ObjectManager* OBJ_Manager;
};