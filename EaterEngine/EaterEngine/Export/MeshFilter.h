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
	EATER_ENGINEDLL void SetAnimationName(std::string mTextureName);


	static void SetManager(ObjectManager* obj, MaterialManager* mat);
private:
	//Transform�� �����Ѵ�
	void LinkHierarchy(Transform* my,Transform*parent);

	//LoadMeshData�� ���ӿ� ����� ������Ʈ�� �����ϸ鼭 ���� �־��ش�
	void CreateChild_Mesh(LoadMeshData* data,Transform* parent,  ModelData* modeldata);

	//LoadMeshData�� ���ӿ� ����� ������Ʈ�� �����ϸ鼭 ���� �־��ش�
	void CreateChild_Bone(LoadMeshData* data, Transform* parent, std::vector<GameObject*>* mBoneList, std::vector<DirectX::SimpleMath::Matrix>* BoneOffsetList);

	//���ӿ�����Ʈ�� LoadData�� �����ش�
	void PushModelData(LoadMeshData* mModel);

	//�ʱ⼳�� Texture Setting
	void CheckTexture();
	void CheckAnimation();


	static ObjectManager* OBJ_Manager;
	static MaterialManager* MAT_Manager;
private:
	bool isLoad_Mesh;			//�Ž� �ε忩��
	bool isLoad_Texture;		//�ؽ��� �ε� ����
	bool isLoad_Animation;		//�ִϸ��̼� �ε忩��


	std::string MeshName;		//�ε��� �Ž� �̸�
	std::string TextureName;	//�ε��� �ؽ��� �̸�
	std::string AnimationName;	//�ε��� �ִϸ��̼� �̸�


	//������Ʈ���� GameObject Ÿ������ ����
	std::vector<GameObject*>	BoneList;

	//�������� ����Ʈ
	std::vector<DirectX::SimpleMath::Matrix> BoneOffsetList;

	//������ ������Ʈ ����Ʈ
	std::vector<GameObject*> MeshList;
	
};

