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
		//�ֻ��� ��ü�� ������
		ModelData* data	= LoadManager::GetMesh(MeshName);
		Transform* MyTr = gameobject->transform;
		


		//�� ������Ʈ �����
		for (int i = 0; i < data->BoneList.size(); i++)
		{
			int size = (data->MeshList[0]->BoneList)->size();
			CreateChild_Bone(data->BoneList[i], MyTr, &BoneList);
		}


		//�Ž� ������Ʈ �����
		for (int i = 0; i < data->MeshList.size(); i++)
		{
			CreateChild_Mesh(data->MeshList[i], MyTr);
		}
		int num = 0;
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

	data->mLocal = *(mModel->LocalTM);
	data->mWorld = *(mModel->WorldTM);
}

void MeshFilter::CreateChild_Mesh(LoadMeshData* data, Transform* parent)
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
		SF->PushBone_OffsetList(data->BoneTMList);

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
		Filter->CreateChild_Mesh(data->Child[i],Tr);
	}
}

void MeshFilter::CreateChild_Bone(LoadMeshData* data, Transform* parent, std::vector<Transform*>* mBoneList)
{
	GameObject* OBJ = new GameObject();
	OBJ->Name = data->Name;
	OBJ->OneMeshData->ObjType = OBJECT_TYPE::Bone;

	//���۳�Ʈ ����
	Transform*	Tr		= OBJ->AddComponent<Transform>();
	MeshFilter* Filter	= OBJ->AddComponent<MeshFilter>();


	//Transform ����
	OBJ->transform = Tr;

	Tr->Load_Local = *data->LocalTM;
	Tr->Load_World = *data->WorldTM;

	//Transform ���� ����
	LinkHierarchy(Tr, parent);
	//������Ʈ �Ŵ������� �����Ҽ��ֵ��� �־��ش�
	OBJ_Manager->PushCreateObject(OBJ);

	mBoneList->push_back(Tr);

	//�ڽİ�ü ������ŭ ����
	int ChildCount = data->Child.size();
	for (int i = 0; i < ChildCount; i++)
	{
		//��� ȣ��
		Filter->CreateChild_Bone(data->Child[i], Tr, mBoneList);
	}
}

void MeshFilter::LinkHierarchy(Transform* my, Transform* parent)
{
	my->SetParnet(parent);
	parent->SetChild(my);
}




