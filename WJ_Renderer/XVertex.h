#pragma once
struct XVertex
{
	XVertex();
	XVertex(float _x, float _y)  ;
	XVertex(float _x, float _y,float _z)  ;
	XVertex(float _x, float _y, float _r, float _g, float _b)  ;
	~XVertex();
	
	DirectX::XMFLOAT2 m_Pos;
	DirectX::XMFLOAT3 m_Color;
};

