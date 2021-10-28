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
	}
}

void MeshFilter::SetMeshName(std::string mMeshName)
{
	isLoad = true;
	MeshName = mMeshName;
}




