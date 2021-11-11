#pragma once

#include <SimpleMath.h>
#include <DirectXMath.h>
struct Deferred32
{
	//��ġ
	DirectX::SimpleMath::Vector3 Pos;
	//�ؽ���
	DirectX::SimpleMath::Vector2 Tex;
	//�븻
	DirectX::SimpleMath::Vector3 Nomal;
	//ź��Ʈ
	DirectX::SimpleMath::Vector3 Tangent;
};

struct Skinning32
{
	//��ġ
	DirectX::SimpleMath::Vector3 Pos;
	//�ؽ���
	DirectX::SimpleMath::Vector2 Tex;
	//�븻
	DirectX::SimpleMath::Vector3 Nomal;
	//ź��Ʈ
	DirectX::SimpleMath::Vector3 Tangent;


	UINT BoneIndex[4];
	float BoneWeights[4];
};