#include "MainHeader.h"
#include "intro.h"
#include "GameObject.h"
#include "MeshFilter.h"
#include "SkinningFilter.h"
#include "AnimationController.h"
#include "Transform.h"
#include "AI.h"
#include "Player.h"
#include "KeyInput.h"
#include "Camera.h"
#include "Light.h"

void intro::Awake()
{
	//�ҷ����� �Ž��� ��� �ľ�
	LoadMeshPath("../Resources/Mesh/");
	LoadTexturePath("../Resources/Texture/");

	LoadMesh("Table");
	LoadMesh("Field");
	LoadMesh("Player_Run", false, false);
	LoadMesh("Player_Roll", false, true);
	LoadMesh("Player_Idle", false, true);
	LoadMesh("Pistol", true, false);
	LoadMesh("Weapon", true, false);

	LoadTexture("Player.dds");
	LoadTexture("Dump.png");


	///ī�޶�
	testobj = Instance("Cam");
	testobj->AddComponent<Camera>();
	testobj->AddComponent<Keyinput>();
	testobj->GetTransform()->Position = { 0,0,-25 };

	///����Ʈ
	testobj = Instance("DirectionLight");
	testobj->AddComponent<DirectionLight>();

	///ĳ����
	testobj = Instance("Player");
	testobj->AddComponent<AnimationController>();
	testobj->AddComponent<MeshFilter>();
	testobj->AddComponent<Player>();

	/// �ٴ�
	testobj = Instance("Field");
	testobj->AddComponent<MeshFilter>()->SetMeshName("Field");
	testobj->GetComponent<Transform>()->Scale = { 0.5f, 0.5f, 0.5f };

	testobj = Instance("Table");
	testobj->AddComponent<MeshFilter>()->SetMeshName("Table");
	testobj->GetComponent<Transform>()->Scale = { 0.1f, 0.1f, 0.1f };
	testobj->GetTransform()->Position = { -5.0f, 0.0f, -5.0f };
}

void intro::Start()
{
	
}

void intro::Update()
{
	
}

void intro::End()
{


}
