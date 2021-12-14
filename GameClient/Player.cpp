#include "Player.h"
#include "Transform.h"
#include "MeshFilter.h"
#include "GameObject.h"
#include "MainHeader.h"
#include "Rigidbody.h"

Player::Player()
{
	Tr = nullptr;
	Mf = nullptr;
}

Player::~Player()
{
	
}

void Player::Awake()
{
	//컨퍼넌트 가져오기
	Tr = gameobject->GetTransform();
	Mf = gameobject->GetComponent<MeshFilter>();
	ri = gameobject->GetComponent<Rigidbody>();
}

void Player::Start()
{
	Mf->SetMeshName("box");
	ri->CreateBoxCollider(1.0f);
	Tr->Position = { 0,5,0 };
}

void Player::Update()
{
	float Speed = 5.0f * GetDeltaTime();

	if (GetKey(VK_RIGHT))
	{
		Move = true;
		ri->SetTranlate(Speed, 0, 0);
	}
	if (GetKey(VK_LEFT))
	{
		ri->SetTranlate(-Speed, 0, 0);
	}
	if (GetKey(VK_UP))
	{
		ri->SetTranlate(0, 0, Speed);
	}
	if (GetKey(VK_DOWN))
	{
		ri->SetTranlate(0, 0, -Speed);
	}

	if (GetKeyDown(VK_SPACE))
	{
		ri->SetTranlate(0, 1,0);
	}

	//else
	//{
	//	Move = false;
	//}
	//
	//if (GetKey('Q'))
	//{
	//	gameobject->transform->SetRotate(0,1,0);
	//}
	//else if (GetKey('E'))
	//{
	//	gameobject->transform->SetRotate(0, 1, 0);
	//}

}


