#include "MeshFilter.h"
#include "GameObject.h"
#include "LoadManager.h"
#include "EngineData.h"

extern LoadManager* gLoadManager;

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
		LoadData* data = LoadManager::GetMesh(MeshName);

		if (data != nullptr && data != nullptr)
		{
			gameobject->OneMeshData->IB = data->IB;
			gameobject->OneMeshData->VB = data->VB;
			gameobject->OneMeshData->indexCount = data->IB->Count;
			gameobject->OneMeshData->vertexCount = data->VB->Count;;
		}

	}
}

void MeshFilter::SetMeshName(std::string mMeshName)
{
	isLoad = true;
	MeshName = mMeshName;
}




