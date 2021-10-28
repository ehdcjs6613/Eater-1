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
		//gameobject->OneMeshData->FBXData = gLoadManager->GetMesh(MeshName);
	}
}

void MeshFilter::SetMeshName(std::string mMeshName)
{
	isLoad = true;
	MeshName = mMeshName;
}




