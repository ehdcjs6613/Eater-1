#include "MeshFilter.h"
#include "DebugManager.h"
#include "GameObject.h"
#include "LoadManager.h"
#include "KHParser.h"

extern LoadManager* gLoadManager;
MeshFilter::MeshFilter()
{
	MeshFilterData = nullptr;
	MeshName = "";
}

MeshFilter::~MeshFilter()
{

}

void MeshFilter::Awake()
{
	DebugManager::GM()->Print("MeshFilter Awake 함수 실행 \n");
	//MeshData 불러오기
	

}

void MeshFilter::Start()
{
	MeshFilterData = gLoadManager->GetMesh(MeshName);
	if (MeshFilterData == nullptr)
	{
		DebugManager::GM()->Print("Mesh불러오기 실패 \n");
	}
}

void MeshFilter::EndUpdate()
{
	//모든 업데이트가 끝나고 각각 컨퍼넌트의 정보를 가져옴
}

void MeshFilter::Update()
{
	
}

void MeshFilter::SetMeshName(std::string mMeshName)
{
	MeshName = mMeshName;
}




