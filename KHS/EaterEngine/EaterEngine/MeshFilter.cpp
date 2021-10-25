#include "MeshFilter.h"
#include "DebugManager.h"
#include "GameObject.h"
#include "LoadManager.h"
#include "KHParser.h"
#include "Transform.h"
#include "EngineData.h"

extern LoadManager* gLoadManager;

std::vector<MeshData*> MeshFilter::MeshList;
MeshFilter::MeshFilter()
{
	MeshFilterData = nullptr;
	MeshName = "";
}

MeshFilter::~MeshFilter()
{
	Meshtemp->FBXData = nullptr;
	delete Meshtemp;
}


void MeshFilter::Start()
{
	transform = gameobject->GetComponent<Transform>();
	if (isLoad == true)
	{
		//매쉬 데이터를 생성해주고
		Meshtemp = new MeshData;
		Meshtemp->FBXData = gLoadManager->GetMesh(MeshName);

		//모든 MeshFiliter들끼리 공유하는 리스트에 넣어준다
		MeshList.push_back(Meshtemp);
	}
}

void MeshFilter::EndUpdate()
{
	//모든 업데이트가 끝나고 각각 컨퍼넌트의 정보를 가져옴
	Meshtemp->mWorld	= transform->GetWorld();
	Meshtemp->Pos		= transform->Position;
}

void MeshFilter::SetMeshName(std::string mMeshName)
{
	isLoad = true;
	MeshName = mMeshName;
}

std::vector<MeshData*>* MeshFilter::GetMeshData()
{
	return &MeshList;
}




