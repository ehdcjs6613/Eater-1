#include "Player.h"
#include "AnimationController.h"
#include "Transform.h"
#include "MeshFilter.h"
#include "GameObject.h"
#include "MainHeader.h"

Player::Player()
{
	AC = nullptr;
	Tr = nullptr;
	Mf = nullptr;
}

Player::~Player()
{

}

void Player::Awake()
{
	//���۳�Ʈ ��������
	AC = gameobject->GetComponent<AnimationController>();
	Tr = gameobject->GetComponent<Transform>();
	Mf = gameobject->GetComponent<MeshFilter>();

}

void Player::Start()
{
	//���۳�Ʈ �ʱ�ȭ
	Mf->SetMeshName("Enemy_Run");
	Mf->SetTextureName("Player");
	Mf->SetAnimationName("Enemy");

	Tr->Position = { 0 ,0, 0 };
	Tr->Scale = { 1 ,1, 1 };
	Tr->Rotation = { 90 ,0,0 };
}


