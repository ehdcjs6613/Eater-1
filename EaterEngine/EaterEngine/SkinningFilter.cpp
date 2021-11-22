#include "SkinningFilter.h"
#include "GameObject.h"
#include "LoadManager.h"
#include "Transform.h"
#include "EngineData.h"
#include "ObjectManager.h"

SkinningFilter::SkinningFilter()
{

}

SkinningFilter::~SkinningFilter()
{

}

void SkinningFilter::Start()
{
	BoneSize = (int)BoneList->size();
	BoneOffsetTM->resize(BoneSize);
	gameobject->OneMeshData->BoneOffsetTM.resize(BoneSize);
}

void SkinningFilter::Update()
{
	MeshData* data = gameobject->OneMeshData;
	
	//(*BoneList)[1]->SetRotate(0.01f, 0, 0);
	//������ �־��ֱ�
	for (int i = 0; i < BoneSize; i++)
	{
		//���� ����
		DirectX::XMMATRIX BoneWorld = *(*BoneList)[i]->GetWorld();

		//���� ������
		DirectX::XMFLOAT4X4 temp = (*BoneOffsetTM)[i];
		DirectX::XMMATRIX Offset = DirectX::XMLoadFloat4x4(&temp);

		//�׷��� ������������ �Ѱ��ټ��ֵ��� ���� �־���
		(data->BoneOffsetTM)[i] = (Offset * BoneWorld);
	}
}

void SkinningFilter::PushBoneList(std::vector<Transform*>* mBoneList)
{
	// BoneList �� BoneOffsetTM �� 1:1 ��Ī�� �Ǿ���Ѵ�
	BoneList = mBoneList;
}

void SkinningFilter::PushBone_OffsetList(std::vector<DirectX::SimpleMath::Matrix>* mBoneOffsetTM)
{
	BoneOffsetTM = mBoneOffsetTM;
}
