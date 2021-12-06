#include "BoxCollider.h"

BoxCollider::BoxCollider() : m_Size{1,1,1}
{
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
	//그려주기 함수

}

void BoxCollider::CalculateOBB()
{

}

void BoxCollider::CalculateAABB()
{

}
