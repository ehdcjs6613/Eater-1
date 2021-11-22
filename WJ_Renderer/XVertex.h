#pragma once

#include "OneCompile.h"

struct XVertex
{
	XVertex();
	XVertex(float _x, float _y, float _z) ;
	XVertex(float _x, float _y, float _z,float _r, float _g, float _b)  ;
	~XVertex();
	
	DirectX::XMFLOAT3 m_Pos;
	DirectX::XMFLOAT3 m_Color;
};
struct XVertexGrid
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT4 Color;
};


struct XVertexDef
{
	//��ġ
	DirectX::SimpleMath::Vector3 Pos;
	//�븻
	DirectX::SimpleMath::Vector3 Nomal;
	//�ؽ���
	DirectX::SimpleMath::Vector2 Tex;
	//ź��Ʈ
	DirectX::SimpleMath::Vector3 Tangent;
};

struct XVertexTex
{
	XVertexTex();
	XVertexTex(float _x, float _y, float _z, float _u, float _v);
	~XVertexTex();

	DirectX::XMFLOAT3 m_Pos;
	DirectX::XMFLOAT2 m_TexCoord;
};

