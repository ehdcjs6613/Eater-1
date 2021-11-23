#pragma once

#include "EaterEngineDLL.h"
#include <vector>
#include <string>
#include "Component.h"
/// <summary>
/// �Ž������� �ļ����� �޾ƿ��� �����صδ� ���۳�Ʈ
/// </summary>


namespace DirectX
{
	namespace SimpleMath
	{
		struct Matrix;
	}
}

namespace ParserData
{
	class OneAnimation;	
}

class ModelData;
class LoadMeshData;
class Transform;
class ObjectManager;
class MaterialManager;

class  MeshFilter : public Component
{
public:
	EATER_ENGINEDLL MeshFilter();
	virtual ~MeshFilter();

	virtual void Awake() override;

public:
	//�޽��� �̸��� ������ ������ �ε�
	EATER_ENGINEDLL void SetMeshName(std::string mMeshName);
	EATER_ENGINEDLL void SetTextureName(std::string mTextureName);
	EATER_ENGINEDLL void SetNormalTextureName(std::string mTextureName);

	static void SetManager(ObjectManager* obj, MaterialManager* mat);
private:
	//Transform�� �����Ѵ�
	void LinkHierarchy(Transform* my,Transform*parent);

	//LoadMeshData�� ���ӿ� ����� ������Ʈ�� �����ϸ鼭 ���� �־��ش�
	void CreateChild_Mesh(LoadMeshData* data,Transform* parent,  ModelData* modeldata);

	//LoadMeshData�� ���ӿ� ����� ������Ʈ�� �����ϸ鼭 ���� �־��ش�
	void CreateChild_Bone(LoadMeshData* data, Transform* parent, std::vector<Transform*>* mBoneList, std::vector<DirectX::SimpleMath::Matrix>* BoneOffsetList);

	//���ӿ�����Ʈ�� LoadData�� �����ش�
	void PushModelData(LoadMeshData* mModel);

	//�ʱ⼳�� Texture Setting
	void CheckTexture();


	static ObjectManager* OBJ_Manager;
	static MaterialManager* MAT_Manager;
private:
	bool isLoadMesh;			//�Ž� �ε忩��
	bool isLoadTexture;			//�ؽ��� �ε� ����


	std::string MeshName;		//�ε��� �Ž� �̸�
	std::string TextureName;	//�ε��� �ؽ��� �̸�

	std::vector<Transform*> BoneList;
	std::vector<DirectX::SimpleMath::Matrix> BoneOffsetList;
	std::vector<ParserData::OneAnimation*>	AnimData;
	std::vector<GameObject*> MeshList;
	
};

