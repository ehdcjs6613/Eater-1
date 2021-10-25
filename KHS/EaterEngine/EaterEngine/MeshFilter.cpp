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
	DebugManager::GM()->Print("MeshFilter Awake �Լ� ���� \n");
	//MeshData �ҷ�����
	

}

void MeshFilter::Start()
{
	MeshFilterData = gLoadManager->GetMesh(MeshName);
	if (MeshFilterData == nullptr)
	{
		DebugManager::GM()->Print("Mesh�ҷ����� ���� \n");
	}
}

void MeshFilter::EndUpdate()
{
	//��� ������Ʈ�� ������ ���� ���۳�Ʈ�� ������ ������
}

void MeshFilter::Update()
{
	
}

void MeshFilter::SetMeshName(std::string mMeshName)
{
	MeshName = mMeshName;
}




