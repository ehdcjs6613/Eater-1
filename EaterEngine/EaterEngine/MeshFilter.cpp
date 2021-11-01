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


		gameobject->OneMeshData->IB = data->IB;
		gameobject->OneMeshData->VB = data->VB;
		gameobject->OneMeshData->indexCount = data->indexCount;
		gameobject->OneMeshData->vertexCount = data->vertexCount;
	}
}

void MeshFilter::SetMeshName(std::string mMeshName)
{
	isLoad = true;
	MeshName = mMeshName;
}




