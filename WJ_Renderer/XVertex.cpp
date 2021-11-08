#include "OneCompile.h"
#include "XVertex.h"

XVertex::XVertex() : m_Pos(0, 0)  , m_Color(0,0,0)
{
}

XVertex::XVertex(float _x, float _y) : m_Pos(_x, _y ) , m_Color(0, 0, 0)
{
	
}

XVertex::XVertex(float _x, float _y, float _z) : m_Pos(_x, _y), m_Color(0, 0, 0)
{
}

XVertex::XVertex(float _x, float _y, float _r, float _g, float _b) : m_Pos(_x, _y), m_Color(_r, _g, _b)
{
}

XVertex::~XVertex()
{
}
