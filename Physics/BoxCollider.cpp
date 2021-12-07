
#include "VertexPositionColor.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider() : m_Size{1,1,1}
{
	//---
	//Hight
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Awake()
{

}

void BoxCollider::Start()
{

}

void BoxCollider::StartUpdate()
{
}

void BoxCollider::TransformUpdate()
{
}

void BoxCollider::PhysicsUpdate()
{
	CalculateOBB();
	CalculateAABB();
}

void BoxCollider::Update()
{
	Draw();
}

void BoxCollider::EndUpdate()
{
}

void BoxCollider::Draw()
{
	
	

}

void BoxCollider::CalculateOBB()
{

}

void BoxCollider::CalculateAABB()
{

}

void BoxCollider::Initialize(ID3D11DeviceContext* _pDeviceContext)
{
	m_DeviceContext =  _pDeviceContext;
}
