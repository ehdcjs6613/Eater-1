#include "Player.h"
#include "AnimationController.h"
#include "Transform.h"
#include "MeshFilter.h"
#include "GameObject.h"
#include "MainHeader.h"

void Player::Awake()
{
	//���۳�Ʈ ��������
	AC = gameobject->GetComponent<AnimationController>();
	Tr = gameobject->GetComponent<Transform>();
	Mf = gameobject->GetComponent<MeshFilter>();

	//���۳�Ʈ �ʱ�ȭ
	Mf->SetMeshName("Enemy_Run");
	Mf->SetTextureName("Player");
	Mf->SetAnimationName("Enemy");
}

void Player::Start()
{
	Tr->Position	= { 0 ,0, 0 };
	Tr->Scale		= { 1 ,1, 1 };
	Tr->Rotation	= { 90 ,0,0 };

	AC->Choice("Roll");
}

void Player::Update()
{
	//����Ű
	if (GetKey(VK_UP))
	{
		Tr->SetTranlate(0, 0, -GetDeltaTime());
		AC->Choice("Run");
	}

	if (GetKey(VK_DOWN))
	{
		Tr->SetTranlate(0, 0, GetDeltaTime());
		AC->Choice("Run");
	}

	if (GetKey(VK_RIGHT))
	{
		Tr->SetTranlate(GetDeltaTime(), 0, 0);
		AC->Choice("Run");
	}
	if (GetKey(VK_LEFT))
	{
		Tr->SetTranlate(-GetDeltaTime(), 0,0);
		AC->Choice("Run");
	}

	AC->Play(1, true);
}
