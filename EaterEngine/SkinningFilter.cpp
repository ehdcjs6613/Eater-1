#include "SkinningFilter.h"
#include "GameObject.h"
#include "LoadManager.h"
#include "Transform.h"
#include "EngineData.h"
#include "Animation.h"
#include "ObjectManager.h"

SkinningFilter::SkinningFilter()
{

}

SkinningFilter::~SkinningFilter()
{

}

void SkinningFilter::Update()
{
	//�����͸� �ֱ��� ���� ������ ����
	MeshData* data = gameobject->OneMeshData;
	data->BoneOffsetTM.clear();

	//������ ���
	int BoneSize =  (int)BoneList->size();
	//data->BoneOffsetTM.resize(BoneSize);
	(*BoneList)[1]->SetRotate(0, 0, 0.01f);
	//(*BoneList)[27]->SetRotate(0, 0, 0.01f);

	//������ �־��ֱ�
	for (int i = 0; i < BoneList->size(); i++)
	{
		//���� ����
		DirectX::XMMATRIX BoneWorld = *(*BoneList)[i]->GetWorld();

		//���� ������
		DirectX::XMFLOAT4X4 temp = (*BoneOffsetTM)[i];
		DirectX::XMMATRIX Offset = DirectX::XMLoadFloat4x4(&temp);

		//�׷��� ������������ �Ѱ��ټ��ֵ��� ���� �־���
		(data->BoneOffsetTM).push_back(Offset * BoneWorld);
	}
	int num = 0;
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
