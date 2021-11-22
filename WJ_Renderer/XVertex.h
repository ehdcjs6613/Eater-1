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
	//À§Ä¡
	DirectX::SimpleMath::Vector3 Pos;
	//³ë¸»
	DirectX::SimpleMath::Vector3 Nomal;
	//ÅØ½ºÃÄ
	DirectX::SimpleMath::Vector2 Tex;
	//ÅºÁ¨Æ®
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

