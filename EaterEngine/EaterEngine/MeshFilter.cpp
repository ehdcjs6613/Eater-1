#include "MeshFilter.h"
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
		//최상위 객체를 가져왔다
		ModelData* data	= LoadManager::GetMesh(MeshName);
		Transform* MyTr = gameobject->transform;

		//매쉬 오브젝트 만들기
		for (int i = 0; i < data->MeshList.size(); i++)
		{
			ChangeLoadMeshData(data->MeshList[i], MyTr);
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
	OBJ->OneMeshData->ObjType = OBJECT_TYPE::Base;
	

	Transform*	Tr		= OBJ->AddComponent<Transform>();
	MeshFilter* Filter	= OBJ->AddComponent<MeshFilter>();

	//Transform 연결
	OBJ->transform = Tr;

	Filter->PushModelData(data);

	Tr->Load_Local = *data->LocalTM;
	Tr->Load_World = *data->WorldTM;
	

	LinkHierarchy(Tr, parent);

	//오브젝트 매니저에서 관리할수있도록 넣어준다
	OBJ_Manager->PushCreateObject(OBJ);
	gameobject->PushChildList(OBJ);

	//자식객체 개수만큼 실행
	for (int i = 0; i < ChildCount; i++)
	{
		//재귀 호출
		Filter->ChangeLoadMeshData(data->Child[i],Tr);
	}
}

void MeshFilter::LinkHierarchy(Transform* my, Transform* parent)
{
	my->SetParnet(parent);
	parent->SetChild(my);
}




