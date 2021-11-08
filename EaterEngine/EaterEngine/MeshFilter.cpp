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
		//최상위 객체를 가져왔다
		ModelData* data	= LoadManager::GetMesh(MeshName);

		//탑오브젝트가 한개면 그냥 자기자신을 내보내면되고
		//여러개면 자기자신을 최상위로두고 아래로 오브젝트를 생성한다
		if (data->TopObjCount > 1)
		{

		}
		else
		{
			PushModelData(data->MeshList[0]);
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




