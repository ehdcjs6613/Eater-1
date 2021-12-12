#include "MainHeader.h"
#include "intro.h"
#include "GameObject.h"
#include "MeshFilter.h"
#include "SkinningFilter.h"
#include "AnimationController.h"
#include "Transform.h"
#include "Rigidbody.h"
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

	//LoadMesh("Table");
	LoadMesh("Field");
	LoadMesh("Player_Run", false, false);
	LoadMesh("Player_Roll", false, true);
	LoadMesh("Player_Idle", false, true);
	LoadMesh("Pistol", true, false);
	LoadMesh("Weapon", true, false);
	LoadMesh("box", true, false);

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
	//testobj = Instance("Player");
	//testobj->AddComponent<AnimationController>();
	//testobj->AddComponent<MeshFilter>();
	//testobj->AddComponent<Player>();

	/// �ٴ�

	for (int j = -5; j < 5; j++)
	{
		for (int i = -5; i < 5; i++)
		{
			testobj = Instance("Field");
			testobj->AddComponent<MeshFilter>()->SetMeshName("box");
			testobj->AddComponent<Rigidbody>();
			Transform* tr = testobj->GetComponent<Transform>();
			tr->Scale = { 0.1f,0.1f ,0.1f };
			tr->Position = { (float)i,(float)10 + j,(float)0 };
		}
	}


	testobj = Instance("Field");
	testobj->AddComponent<MeshFilter>()->SetMeshName("box");
	testobj->AddComponent<Rigidbody>()->SetType(Rigidbody::STATIC);
	Transform* tr = testobj->GetComponent<Transform>();
	tr->Scale = { 1.0f,1.0f ,1.0f };
	tr->Position = { 0,0,0};
	
	

	//testobj = Instance("Table");
	//testobj->AddComponent<MeshFilter>()->SetMeshName("Table");
	//testobj->GetComponent<Transform>()->Scale = { 0.1f, 0.1f, 0.1f };
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
