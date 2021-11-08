#pragma once
struct XVertex
{
	XVertex();
	XVertex(float _x, float _y, float _z) ;
	XVertex(float _x, float _y, float _z,float _r, float _g, float _b)  ;
	~XVertex();
	
	DirectX::XMFLOAT3 m_Pos;
	DirectX::XMFLOAT3 m_Color;
};

struct XVertexTex
{
	XVertexTex();
	XVertexTex(float _x, float _y, float _z, float _u, float _v);
	~XVertexTex();

	DirectX::XMFLOAT3 m_Pos;
	DirectX::XMFLOAT2 m_TexCoord;
};
