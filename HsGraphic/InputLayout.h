#pragma once

#include <SimpleMath.h>
#include <DirectXMath.h>
struct Deferred32
{
	//��ġ
	DirectX::SimpleMath::Vector3 Pos;
	//�븻
	DirectX::SimpleMath::Vector2 Tex;
	//�ؽ���
	DirectX::SimpleMath::Vector3 Nomal;
	//ź��Ʈ
	DirectX::SimpleMath::Vector3 Tangent;
};

struct Skinning32
{
	UINT BoneIndex01[4];
	UINT BoneIndex02[4];

	float BoneWeights01[4];
	float BoneWeights02[4];
	
	//��ġ
	DirectX::SimpleMath::Vector3 Pos;
	//�ؽ���
	DirectX::SimpleMath::Vector2 Tex;
	//�븻
	DirectX::SimpleMath::Vector3 Nomal;
	//ź��Ʈ
	DirectX::SimpleMath::Vector3 Tangent;


};

struct Debug32
{
	//��ġ
	DirectX::XMFLOAT3 Pos;
	//�÷�
	DirectX::XMFLOAT3 Color;
};