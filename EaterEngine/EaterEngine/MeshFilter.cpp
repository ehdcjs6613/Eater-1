#include "MeshFilter.h"
#include "SkinningFilter.h"
#include "GameObject.h"
#include "LoadManager.h"
#include "Transform.h"
#include "EngineData.h"
#include "Animation.h"
#include "ObjectManager.h"



ObjectManager* MeshFilter::OBJ_Manager = nullptr;
MeshFilter::MeshFilter()
{
	MeshName = "";
}

MeshFilter::~MeshFilter()
{
	
}

void MeshFilter::Awake()
{
	if (isLoad == true)
	{
		////�ֻ��� ��ü�� ������
		ModelData* data = LoadManager::GetMesh(MeshName);
		Transform* MyTr = gameobject->transform;



		//�� ������Ʈ �����
		for (int i = 0; i < data->TopBoneList.size(); i++)
		{
			CreateChild_Bone(data->TopBoneList[i], MyTr, &BoneList, &BoneOffsetList);
		}


		//�Ž� ������Ʈ �����
		for (int i = 0; i < data->TopMeshList.size(); i++)
		{
			CreateChild_Mesh(data->TopMeshList[i], MyTr, data);
		}
	}
}

void MeshFilter::SetObjMananager(ObjectManager* obj)
{
	OBJ_Manager = obj;
}

void MeshFilter::SetMeshName(std::string mMeshName)
{
	isLoad = true;
	MeshName = mMeshName;
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
}

void MeshFilter::CreateChild_Mesh(LoadMeshData* data, Transform* parent, ModelData* modeldata)
{
	int ChildCount = data->Child.size();

	GameObject* OBJ		= new GameObject();
	OBJ->Name			= data->Name;
	
	
	//���۳�Ʈ ����
	Transform*	Tr		= OBJ->AddComponent<Transform>();
	MeshFilter* Filter	= OBJ->AddComponent<MeshFilter>();
	
	//Transform ����
	OBJ->transform = Tr;

	//��Ű�� �Ž����
	if (data->Skinning_Object == true)
	{
		SkinningFilter* SF = OBJ->AddComponent<SkinningFilter>();
		//�� ����Ʈ �Ѱ��ֱ�
		SF->PushBoneList(&BoneList);
		//�� ������ �Ѱ��ֱ�
		SF->PushBone_OffsetList(&BoneOffsetList);

		OBJ->OneMeshData->ObjType = OBJECT_TYPE::Skinning;
	}
	else
	{
		OBJ->OneMeshData->ObjType = OBJECT_TYPE::Base;
	}
	
	//�����͸� �Ѱ��ش� 
	Filter->PushModelData(data);
	Tr->Load_Local = *data->LocalTM;
	Tr->Load_World = *data->WorldTM;
	
	//Transform ���� ����
	LinkHierarchy(Tr, parent);
	//������Ʈ �Ŵ������� �����Ҽ��ֵ��� �־��ش�
	OBJ_Manager->PushCreateObject(OBJ);

	//�ڽİ�ü ������ŭ ����
	for (int i = 0; i < ChildCount; i++)
	{
		//��� ȣ��
		Filter->CreateChild_Mesh(data->Child[i],Tr,modeldata);
	}
}

void MeshFilter::CreateChild_Bone(LoadMeshData* data, Transform* parent, std::vector<Transform*>* mBoneList, std::vector<DirectX::SimpleMath::Matrix>* BoneOffsetList)
{
	GameObject* OBJ = new GameObject();
	OBJ->Name = data->Name;
	OBJ->OneMeshData->ObjType = OBJECT_TYPE::Bone;

	//���۳�Ʈ ����
	Transform*	Tr		= OBJ->AddComponent<Transform>();
	MeshFilter* Filter	= OBJ->AddComponent<MeshFilter>();


	//Animation*	Anime	= OBJ->AddComponent<Animation>();
	//�ִϸ��̼� ������ �־��ֱ�
	//Anime->SetAnimation(data->Animation);

	//Transform ����
	OBJ->transform = Tr;

	Tr->Load_Local = *data->LocalTM;
	Tr->Load_World = *data->WorldTM;


	//Transform ���� ����
	LinkHierarchy(Tr, parent);
	//������Ʈ �Ŵ������� �����Ҽ��ֵ��� �־��ش�
	OBJ_Manager->PushCreateObject(OBJ);

	mBoneList->push_back(Tr);
	BoneOffsetList->push_back(*data->BoneOffset);


	//�ڽİ�ü ������ŭ ����
	int ChildCount = data->Child.size();
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




