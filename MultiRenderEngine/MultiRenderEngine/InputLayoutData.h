#pragma once

#include "SimpleMath.h"
struct MeshVertex
{
	//��ġ
	DirectX::SimpleMath::Vector3 Pos;
	//uv
	DirectX::SimpleMath::Vector2 Tex;
	//�븻
	DirectX::SimpleMath::Vector3 Normal;
	//ź��Ʈ
	DirectX::SimpleMath::Vector3 Tangent;
};

struct SkinVertex
{
	//�� �ε���
	UINT BoneIndex1[4];
	UINT BoneIndex2[4];

	//�� ������
	float BoneWeight1[4];
	float BoneWeight2[4];

	//��ġ
	DirectX::SimpleMath::Vector3 Pos;
	//uv
	DirectX::SimpleMath::Vector2 Tex;
	//�븻
	DirectX::SimpleMath::Vector3 Normal;
	//ź��Ʈ
	DirectX::SimpleMath::Vector3 Tangent;
};