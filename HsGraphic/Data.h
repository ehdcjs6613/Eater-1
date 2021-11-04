#pragma once
#include "d3d11.h"
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

//�ڷ��� ��ȣ 2173406236
//���̴����� ������ ������
struct ShaderData
{
	ID3D11VertexShader* VertexShader	= nullptr;
	ID3D11PixelShader* PixelShader		= nullptr;
	ID3D11InputLayout* Layout			= nullptr;
};