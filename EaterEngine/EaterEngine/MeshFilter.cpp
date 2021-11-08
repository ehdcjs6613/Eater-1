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
		//�ֻ��� ��ü�� �����Դ�
		ModelData* data	= LoadManager::GetMesh(MeshName);

		//ž������Ʈ�� �Ѱ��� �׳� �ڱ��ڽ��� ��������ǰ�
		//�������� �ڱ��ڽ��� �ֻ����εΰ� �Ʒ��� ������Ʈ�� �����Ѵ�
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




