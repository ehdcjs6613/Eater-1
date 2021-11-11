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
		//최상위 객체를 가져옴
		ModelData* data	= LoadManager::GetMesh(MeshName);
		Transform* MyTr = gameobject->transform;
		


		//본 오브젝트 만들기
		for (int i = 0; i < data->BoneList.size(); i++)
		{
			int size = (data->MeshList[0]->BoneList)->size();
			CreateChild_Bone(data->BoneList[i], MyTr, &BoneList);
		}


		//매쉬 오브젝트 만들기
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
	
	
	//컨퍼넌트 생성
	Transform*	Tr		= OBJ->AddComponent<Transform>();
	MeshFilter* Filter	= OBJ->AddComponent<MeshFilter>();


	//Transform 연결
	OBJ->transform = Tr;

	//스키닝 매쉬라면
	if (data->Skinning_Object == true)
	{
		SkinningFilter* SF = OBJ->AddComponent<SkinningFilter>();
		//본 리스트 넘겨주기
		SF->PushBoneList(&BoneList);
		//본 오프셋 넘겨주기
		SF->PushBone_OffsetList(data->BoneTMList);

		OBJ->OneMeshData->ObjType = OBJECT_TYPE::Skinning;
	}
	else
	{
		OBJ->OneMeshData->ObjType = OBJECT_TYPE::Base;
	}
	

	//데이터를 넘겨준다 
	Filter->PushModelData(data);
	Tr->Load_Local = *data->LocalTM;
	Tr->Load_World = *data->WorldTM;
	


	//Transform 끼리 연결
	LinkHierarchy(Tr, parent);
	//오브젝트 매니저에서 관리할수있도록 넣어준다
	OBJ_Manager->PushCreateObject(OBJ);
	


	//자식객체 개수만큼 실행
	for (int i = 0; i < ChildCount; i++)
	{
		//재귀 호출
		Filter->CreateChild_Mesh(data->Child[i],Tr);
	}
}

void MeshFilter::CreateChild_Bone(LoadMeshData* data, Transform* parent, std::vector<Transform*>* mBoneList)
{
	GameObject* OBJ = new GameObject();
	OBJ->Name = data->Name;
	OBJ->OneMeshData->ObjType = OBJECT_TYPE::Bone;

	//컨퍼넌트 생성
	Transform*	Tr		= OBJ->AddComponent<Transform>();
	MeshFilter* Filter	= OBJ->AddComponent<MeshFilter>();


	//Transform 연결
	OBJ->transform = Tr;

	Tr->Load_Local = *data->LocalTM;
	Tr->Load_World = *data->WorldTM;

	//Transform 끼리 연결
	LinkHierarchy(Tr, parent);
	//오브젝트 매니저에서 관리할수있도록 넣어준다
	OBJ_Manager->PushCreateObject(OBJ);

	mBoneList->push_back(Tr);

	//자식객체 개수만큼 실행
	int ChildCount = data->Child.size();
	for (int i = 0; i < ChildCount; i++)
	{
		//재귀 호출
		Filter->CreateChild_Bone(data->Child[i], Tr, mBoneList);
	}
}

void MeshFilter::LinkHierarchy(Transform* my, Transform* parent)
{
	my->SetParnet(parent);
	parent->SetChild(my);
}




