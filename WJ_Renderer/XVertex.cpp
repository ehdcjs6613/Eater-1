#include "OneCompile.h"
#include "XVertex.h"
//==================================================================================================//
XVertex::XVertex() : m_Pos(0, 0,0)  , m_Color(0,0,0)
{
}


XVertex::XVertex(float _x, float _y, float _z) : m_Pos(_x, _y, _z), m_Color(0, 0, 0)
{
}

XVertex::XVertex(float _x, float _y,float _z ,float _r, float _g, float _b) : m_Pos(_x, _y,_z), m_Color(_r, _g, _b)
{
}

XVertex::~XVertex()
{
}
//==================================================================================================//
XVertexTex::XVertexTex():  m_Pos(0, 0, 0), m_TexCoord(0, 0)
{
}

XVertexTex::XVertexTex(float _x, float _y, float _z, float _u, float _v):m_Pos(_x,_y,_z),m_TexCoord(_u,_v)
{
}

XVertexTex::~XVertexTex()
{
}
