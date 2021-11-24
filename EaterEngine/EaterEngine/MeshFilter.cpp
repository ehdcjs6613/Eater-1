#include "MeshFilter.h"
#include "SkinningFilter.h"
#include "GameObject.h"
#include "LoadManager.h"
#include "Transform.h"
#include "EngineData.h"
#include "Animator.h"
#include "ObjectManager.h"
#include "Material.h"
#include "MaterialManager.h"


ObjectManager* MeshFilter::OBJ_Manager = nullptr;
MaterialManager* MeshFilter::MAT_Manager = nullptr;

MeshFilter::MeshFilter()
{
	MeshName = "";
}

MeshFilter::~MeshFilter()
{

}

void MeshFilter::Awake()
{
	if (isLoadMesh == true)
	{
		////�ֻ��� ��ü�� ������
		ModelData* data = LoadManager::GetMesh(MeshName);
		Transform* MyTr = gameobject->transform;
		gameobject->OneMeshData->ObjType = OBJECT_TYPE::GAMEOBJECT;

		
		if(data->TopMeshList[0]->Skinning_Object)
		{
			BoneList.resize(data->BoneList->size());
			BoneOffsetList.resize(data->BoneOffsetList->size());
		}
		
		//�� ������Ʈ �����
		for(int i = 0; i < data->TopBoneList.size(); i++)
		{
			CreateChild_Bone(data->TopBoneList[i], MyTr, &BoneList, &BoneOffsetList);
		}


		//�Ž� ������Ʈ �����
		for(int i = 0; i < data->TopMeshList.size(); i++)
		{
			CreateChild_Mesh(data->TopMeshList[i], MyTr, data);
		}

		//Texture Check & Setting..
		CheckTexture();

	}
}

void MeshFilter::SetManager(ObjectManager* obj, MaterialManager* mat)
{
	OBJ_Manager = obj;
	MAT_Manager = mat;
}

void MeshFilter::SetMeshName(std::string mMeshName)
{
	isLoadMesh = true;
	MeshName = mMeshName;
}

void MeshFilter::SetTextureName(std::string mTextureName)
{
	isLoadTexture = true;
	TextureName = mTextureName;
}

void MeshFilter::SetNormalTextureName(std::string mTextureName)
{


}

void MeshFilter::PushModelData(LoadMeshData* mModel)
{
	MeshData* data = gameobject->OneMeshData;

	data->IB = mModel->IB;
	data->VB = mModel->VB;

	data->Diffuse = mModel->Diffuse;
	data->Normal = mModel->Normal;

	data->mLocal = *(mModel->LocalTM);
	data->mWorld = *(mModel->WorldTM);

	// Diffuse Map�� ���°�� Dump Map���� �⺻ ���..
	if (data->Diffuse == nullptr)
	{
		data->Diffuse = LoadManager::GetTexture("Dump");
	}
}

void MeshFilter::CheckTexture()
{
	// ������ Texture�� ������� �ε��� Diffuse ��� �ش� Texture ����..
	if (TextureName.empty() == false)
	{
		// �ش� Object Mesh Data..
		MeshData* data = gameobject->OneMeshData;

		// ���� Texture Buffer..
		TextureBuffer* texBuffer = LoadManager::GetTexture(TextureName);

		// �ش� Texture�� Load���� ���� ��� ���� Texture ���..
		if (texBuffer == nullptr)
		{
			return;
		}

		// Texture ����..
		data->Diffuse = texBuffer;
	}
}

void MeshFilter::CreateChild_Mesh(LoadMeshData* data, Transform* parent, ModelData* modeldata)
{
	int ChildCount = (int)data->Child.size();

	GameObject* OBJ = new GameObject();
	OBJ->Name = data->Name;


	//���۳�Ʈ ����
	Transform* Tr = OBJ->AddComponent<Transform>();
	MeshFilter* Filter = OBJ->AddComponent<MeshFilter>();

	//Transform ����
	OBJ->transform = Tr;

	//��Ű�� �Ž����
	if (data->Skinning_Object == true)
	{
		SkinningFilter* SF = OBJ->AddComponent<SkinningFilter>();
		//�� ������ �Ѱ��ֱ� ,�� ����Ʈ �Ѱ��ֱ�
		SF->PushBoneList(&BoneList);
		SF->PushBone_OffsetList(&BoneOffsetList);

		OBJ->OneMeshData->ObjType = OBJECT_TYPE::SKINNING;
	}
	else
	{
		OBJ->OneMeshData->ObjType = OBJECT_TYPE::BASE;
	}

	// Material Data..
	if (data->Material)
	{
		Material* mat = OBJ->AddComponent<Material>();

		// �ش� Material Data..
		MaterialData matData;
		matData.Ambient = data->Material->m_Material_Ambient;
		matData.Diffuse = data->Material->m_Material_Diffuse;
		matData.Specular = data->Material->m_Material_Specular;

		// �ش� Material ����..
		mat->SetMaterialData(matData);

		// Material ���..
		MAT_Manager->AddMaterial(mat);
	}

	//�����͸� �Ѱ��ش� 
	Filter->PushModelData(data);
	Tr->Load_Local = *data->LocalTM;
	Tr->Load_World = *data->WorldTM;

	//Transform ���� ����
	//LinkHierarchy(Tr, parent);
	//������Ʈ �Ŵ������� �����Ҽ��ֵ��� �־��ش�
	OBJ_Manager->PushCreateObject(OBJ);

	//�ڽİ�ü ������ŭ ����
	for (int i = 0; i < ChildCount; i++)
	{
		//��� ȣ��
		Filter->CreateChild_Mesh(data->Child[i], Tr, modeldata);
	}
}

void MeshFilter::CreateChild_Bone(LoadMeshData* data, Transform* parent, std::vector<Transform*>* mBoneList, std::vector<DirectX::SimpleMath::Matrix>* BoneOffsetList)
{
	GameObject* OBJ = new GameObject();
	OBJ->Name = data->Name;
	OBJ->OneMeshData->ObjType = OBJECT_TYPE::BONE;

	//���۳�Ʈ ����
	Transform* Tr		= OBJ->AddComponent<Transform>();
	MeshFilter* Filter	= OBJ->AddComponent<MeshFilter>();

	Animator* Anime = OBJ->AddComponent<Animator>();
	//�ִϸ��̼� ������ �־��ֱ�
	Anime->SetAnimation(data->Animation);

	//Transform ����
	OBJ->transform = Tr;

	Tr->Load_Local = *data->LocalTM;
	Tr->Load_World = *data->WorldTM;


	//Transform ���� ����
	LinkHierarchy(Tr, parent);
	//������Ʈ �Ŵ������� �����Ҽ��ֵ��� �־��ش�
	OBJ_Manager->PushCreateObject(OBJ);

	//���� �ش��ϴ� Transform�� ��������
	(*mBoneList)[data->BoneIndex] = Tr;
	(*BoneOffsetList)[data->BoneIndex] = (*data->BoneOffset);

	//�ڽİ�ü ������ŭ ����
	int ChildCount = (int)data->Child.size();
	for (int i = 0; i < ChildCount; i++)
	{
		//��� ȣ��
		Filter->CreateChild_Bone(data->Child[i], Tr, mBoneList, BoneOffsetList);
	}
}

void MeshFilter::LinkHierarchy(Transform* my, Transform* parent)
{
	my->SetParnet(parent);
	parent->SetChild(my);
}




