#include "SkinningFilter.h"
#include "GameObject.h"
#include "LoadManager.h"
#include "Transform.h"
#include "EngineData.h"
#include "Animation.h"
#include "ObjectManager.h"

ObjectManager* SkinningFilter::OBJ_Manager = nullptr;
SkinningFilter::SkinningFilter()
{
	isLoad = false;
	MeshName = "";
}

SkinningFilter::~SkinningFilter()
{

}

void SkinningFilter::Awake()
{
	if (isLoad == true)
	{
		//�ֻ��� ��ü�� �����Դ�
		ModelData* data = LoadManager::GetMesh(MeshName);
		Transform* MyTr = gameobject->transform;

		//�Ž� ������Ʈ �����
		for (int i = 0; i < data->MeshList.size(); i++)
		{
			ChangeLoadMeshData(data->MeshList[i], MyTr);
		}

		//�� ������Ʈ �����
		for (int i = 0; i < data->BoneList.size(); i++)
		{
			ChangeLoadBoneData(data->BoneList[i], MyTr);
		}
	}
}

void SkinningFilter::SetMeshName(std::string mMeshName)
{
	isLoad = true;
	MeshName = mMeshName;
}

void SkinningFilter::SetObjMananager(ObjectManager* obj)
{
	OBJ_Manager = obj;
}

void SkinningFilter::PushModelData(LoadMeshData* mModel)
{
	MeshData* data = gameobject->OneMeshData;

	data->IB = mModel->IB;
	data->VB = mModel->VB;

	data->mLocal = *(mModel->LocalTM);
	data->mWorld = *(mModel->WorldTM);

	data->indexCount = mModel->IB->Count;
	data->vertexCount = mModel->VB->Count;
}

void SkinningFilter::ChangeLoadBoneData(LoadMeshData* data, Transform* parent)
{
	int ChildCount = data->Child.size();

	GameObject* OBJ = new GameObject();
	OBJ->Name = data->Name;

	Transform*		Tr			= OBJ->AddComponent<Transform>();
	SkinningFilter* Filter		= OBJ->AddComponent<SkinningFilter>();
	Animation*		Anime		= OBJ->AddComponent<Animation>();

	//Transform ����
	OBJ->transform = Tr;
	gameobject->OneMeshData->ObjType = OBJECT_TYPE::Bone;


	Tr->Load_Local = *data->LocalTM;
	Tr->Load_World = *data->WorldTM;


	LinkHierarchy(Tr, parent);

	//������Ʈ �Ŵ������� �����Ҽ��ֵ��� �־��ش�
	OBJ_Manager->PushCreateObject(OBJ);
	gameobject->PushChildList(OBJ);
	for (int i = 0; i < ChildCount; i++)
	{
		//��� ȣ��
		Filter->ChangeLoadBoneData(data->Child[i], Tr);
	}
}

void SkinningFilter::ChangeLoadMeshData(LoadMeshData* data, Transform* parent)
{
	int ChildCount = data->Child.size();

	GameObject* OBJ = new GameObject();
	OBJ->Name = data->Name;

	//��Ű�� ������Ʈ�� ���Դٸ�
	if (data->Skinning_Object == true)
	{
		BoneList		= data->BoneList;
		SkinningObject	= OBJ;
		OBJ->OneMeshData->BoneOffsetTM = data->BoneTMList;
		OBJ->OneMeshData->ObjType = OBJECT_TYPE::Skinning;
	}

	Transform*		Tr	   = OBJ->AddComponent<Transform>();
	SkinningFilter* Filter = OBJ->AddComponent<SkinningFilter>();

	//Transform ����
	OBJ->transform = Tr;

	Filter->PushModelData(data);

	Tr->Load_Local = *data->LocalTM;
	Tr->Load_World = *data->WorldTM;


	LinkHierarchy(Tr, parent);

	//������Ʈ �Ŵ������� �����Ҽ��ֵ��� �־��ش�
	OBJ_Manager->PushCreateObject(OBJ);
	gameobject->PushChildList(OBJ);

	//�ڽİ�ü ������ŭ ����
	for (int i = 0; i < ChildCount; i++)
	{
		//��� ȣ��
		Filter->ChangeLoadMeshData(data->Child[i], Tr);
	}
}

void SkinningFilter::LinkHierarchy(Transform* my, Transform* parent)
{
	my->SetParnet(parent);
	parent->SetChild(my);
}

