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
class Material;

class ObjectManager;

class  MeshFilter : public Component
{
public:
	EATER_ENGINEDLL MeshFilter();
	virtual ~MeshFilter();

public:
	virtual void Start() override;

public:
	//�޽��� �̸��� ������ ������ �ε�
	EATER_ENGINEDLL void SetMeshName(std::string mMeshName);
	EATER_ENGINEDLL void SetTextureName(std::string mTextureName);
	EATER_ENGINEDLL void SetNormalTextureName(std::string mTextureName);
	EATER_ENGINEDLL void SetAnimationName(std::string mTextureName);

public:
	void SetObjectData() override;

	static void SetManager(ObjectManager* obj);

private:
	//Transform�� �����Ѵ�
	void LinkHierarchy(Transform* my,Transform*parent);

	void CreateMesh();

	//LoadMeshData�� ���ӿ� ����� ������Ʈ�� �����ϸ鼭 ���� �־��ش�
	void CreateChild_Mesh(LoadMeshData* data,Transform* parent,  ModelData* modeldata);

	//LoadMeshData�� ���ӿ� ����� ������Ʈ�� �����ϸ鼭 ���� �־��ش�
	void CreateChild_Bone(LoadMeshData* data, Transform* parent, std::vector<GameObject*>* mBoneList, std::vector<DirectX::SimpleMath::Matrix>* BoneOffsetList);

	//���ӿ�����Ʈ�� LoadData�� �����ش�
	void PushModelData(LoadMeshData* mModel);

	//�ʱ⼳�� Texture Setting
	void CheckTexture();
	void CheckAnimation();

private:
	static ObjectManager* OBJ_Manager;

	bool isLoad_Mesh;			//�Ž� �ε忩��
	bool isLoad_Texture;		//�ؽ��� �ε� ����
	bool isLoad_Animation;		//�ִϸ��̼� �ε忩��

	std::string MeshName;		//�ε��� �Ž� �̸�
	std::string TextureName;	//�ε��� �ؽ��� �̸�
	std::string AnimationName;	//�ε��� �ִϸ��̼� �̸�

	Material* Materials;		//Material Data

	//������Ʈ���� GameObject Ÿ������ ����
	std::vector<GameObject*>	BoneList;

	//�������� ����Ʈ
	std::vector<DirectX::SimpleMath::Matrix> BoneOffsetList;

	//������ ������Ʈ ����Ʈ
	std::vector<GameObject*> MeshList;
	
};

