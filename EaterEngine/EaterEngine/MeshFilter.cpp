#include "MeshFilter.h"
#include "GameObject.h"
#include "LoadManager.h"
#include "Transform.h"
#include "EngineData.h"
#include "ObjectManager.h"



ObjectManager* MeshFilter::OBJ_Manager = nullptr;
MeshFilter::MeshFilter()
{
	MeshName = "";
}

MeshFilter::~MeshFilter()
{
	
}

void MeshFilter::Start()
{
	if (isLoad == true)
	{
		//�ֻ��� ��ü�� �����Դ�
		ModelData* data	= LoadManager::GetMesh(MeshName);
		Transform* MyTr = gameobject->transform;

		for (int i = 0; i < data->MeshList.size(); i++)
		{
			ChangeLoadMeshData(data->MeshList[i], MyTr);
		}
		MyTr->Child_Local_Updata();
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

	data->indexCount	= mModel->IB->Count;
	data->vertexCount	= mModel->VB->Count;
}

void MeshFilter::ChangeLoadMeshData(LoadMeshData* data, Transform* parent)
{
	int ChildCount = data->Child.size();

	GameObject* OBJ		= new GameObject();
	OBJ->Name			= data->Name;

	Transform* Tr		= OBJ->AddComponent<Transform>();
	MeshFilter* Filter	= OBJ->AddComponent<MeshFilter>();

	//Transform ����
	OBJ->transform = Tr;
	Filter->PushModelData(data);

	Tr->Load_Local = *data->LocalTM;
	Tr->Load_World = *data->WorldTM;
	
	//�θ�� �ڽ��� ��ũ
	Transform::LinkHierarchy(Tr, parent);

	//������Ʈ �Ŵ������� �����Ҽ��ֵ��� �־��ش�
	OBJ_Manager->PushCreateObject(OBJ);
	gameobject->PushChildList(OBJ);

	//�ڽİ�ü ������ŭ ����
	for (int i = 0; i < ChildCount; i++)
	{
		//��� ȣ��
		Filter->ChangeLoadMeshData(data->Child[i],Tr);
	}
}




