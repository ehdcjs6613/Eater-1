#include "MainHeader.h"
#include "inGame.h"
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
#include "Terrain.h"

void InGame::Awake()
{
	//�ҷ����� �Ž��� ��� �ľ�
	LoadMeshPath("../Resources/Mesh/");
	LoadTexturePath("../Resources/Texture/");

	LoadMesh("Table");
	LoadMesh("Field");
	LoadMesh("CHARACTER_idle", SCALING);
	LoadMesh("Player_Run");
	LoadMesh("Player_Roll", ANIMATION_ONLY);
	LoadMesh("Player_Idle", ANIMATION_ONLY);
	LoadMesh("Pistol", SCALING);
	LoadMesh("Weapon", SCALING);

	LoadTerrainMesh("Terrain", "Terrain_RGB.png", SCALING);
	//LoadTerrainMesh("Terrain3", "Terrain_RGB.png", SCALING);

	LoadTexture("Player.dds");
	LoadTexture("Dump.png");
	LoadTexture("ground01_Albedo.png");
	LoadTexture("ground02_Albedo.png");
	LoadTexture("ground01_Normal.png");
	LoadTexture("ground02_Normal.png");


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

	///�ͷ���
	testobj = Instance("Terrain");
	testobj->AddComponent<MeshFilter>();
	testobj->GetComponent<MeshFilter>()->SetMeshName("Terrain");
	testobj->GetComponent<Terrain>()->AddLayer("ground01_Albedo", "ground01_Normal");
	testobj->GetComponent<Terrain>()->AddLayer("ground02_Albedo", "ground02_Normal");
	testobj->GetComponent<Terrain>()->SetTextureTiling(1.0f / 31.0f, 1.0f / 31.0f);
	testobj->GetTransform()->Rotation = { 0, 0, 0 };


	///ĳ����
	testobj = Instance("CHARACTER");
	testobj->AddComponent<AnimationController>();
	testobj->AddComponent<MeshFilter>();
	testobj->GetComponent<MeshFilter>()->SetMeshName("CHARACTER");
	testobj->GetComponent<MeshFilter>()->SetAnimationName("CHARACTER");
	testobj->GetComponent<AnimationController>()->Choice("idle");

	testobj->GetTransform()->Scale = { 0.2f, 0.2f, 0.2f };
	testobj->GetTransform()->Rotation = { -90.0f, 0.0f, 0.0f };
	testobj->GetTransform()->Position = { 100.0f, 0.0f, 0.0f };

	/// �ٴ�
	//testobj = Instance("Field");
	//testobj->AddComponent<MeshFilter>()->SetMeshName("Field");
	//testobj->GetComponent<Transform>()->Scale = { 0.5f, 0.5f, 0.5f };

	//testobj = Instance("Field1");
	//testobj->AddComponent<MeshFilter>()->SetMeshName("Field");
	//testobj->GetComponent<Transform>()->Rotation = { 90.0f, 0.0f, 0.0f };
	//testobj->GetComponent<Transform>()->Scale = { 0.5f, 0.5f, 0.5f };
	//testobj->GetComponent<Transform>()->Position = { 0.0f, 2.5f, 2.5f };

	//testobj = Instance("Table");
	//testobj->AddComponent<MeshFilter>()->SetMeshName("Table");
	//testobj->GetComponent<Transform>()->Scale = { 0.1f, 0.1f, 0.1f };
	//testobj->GetTransform()->Position = { -5.0f, 0.0f, -5.0f };
}

void InGame::Start()
{
}

void InGame::Update()
{
	testobj->GetComponent<AnimationController>()->Play(1, true);
	
	if (GetKey(VK_LEFT) == true)
	{
		testobj->GetTransform()->Position.x -= 250.0f * GetDeltaTime();
	}
	if (GetKey(VK_RIGHT) == true)
	{
		testobj->GetTransform()->Position.x += 250.0f * GetDeltaTime();
	}
	
	if (GetKey(VK_UP) == true)
	{
		testobj->GetTransform()->Position.z += 250.0f * GetDeltaTime();
	}
	if (GetKey(VK_DOWN) == true)
	{
		testobj->GetTransform()->Position.z -= 250.0f * GetDeltaTime();
	}
}

void InGame::End()
{
}
