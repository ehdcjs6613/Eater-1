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
	//불러오는 매쉬의 경로 파악
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
	LoadMesh("Sphere", true, false);

	LoadTexture("Player.dds");
	LoadTexture("Dump.png");


	///카메라
	testobj = Instance("Cam");
	testobj->AddComponent<Camera>();
	testobj->AddComponent<Keyinput>();
	testobj->GetTransform()->Position = { 0,0,-25 };

	///라이트
	testobj = Instance("DirectionLight");
	testobj->AddComponent<DirectionLight>();

	///캐릭터
	//testobj = Instance("Player");
	//testobj->AddComponent<AnimationController>();
	//testobj->AddComponent<MeshFilter>();
	//testobj->AddComponent<Player>();

	/// 바닥
	for (int i = 0; i < 10; i++)
	{
		testobj = Instance("Field");
		testobj->AddComponent<MeshFilter>()->SetMeshName("Sphere");
		Rigidbody* rig = testobj->AddComponent<Rigidbody>();
		Transform* tr = testobj->GetComponent<Transform>();
	
		rig->SetGrvity(true);
		rig->CreateSphereCollider(0.5f);
		tr->Scale = { 0.5f,0.5f ,0.5f };
		tr->Position = { (float)i,(float)25 + (i*2),(float)0 };
	}

	testobj = Instance("Field");
	testobj->AddComponent<MeshFilter>()->SetMeshName("Sphere");
	Rigidbody* rig = testobj->AddComponent<Rigidbody>();
	Transform* tr = testobj->GetComponent<Transform>();
	rig->SetGrvity(true);
	rig->SetType(false);
	rig->CreateTriangleCollider();
	tr->Scale = { 0.5f,0.5f ,0.5f };
	tr->Position = { -20,4,-20 };




	testobj = Instance("Field");
	testobj->AddComponent<MeshFilter>();
	testobj->AddComponent<Rigidbody>();
	testobj->AddComponent<Player>();



	//testobj = Instance("Field");
	//testobj->AddComponent<MeshFilter>()->SetMeshName("box");
	//Rigidbody* rig= testobj->AddComponent<Rigidbody>();
	//Transform* tr = testobj->GetComponent<Transform>();
	//rig->SetType(false);
	//rig->CreateBoxCollider(20.0f,1.0f,1.0f);
	//tr->Scale = { 20.0f,1.0f ,1.0f };
	//tr->Position = { 0,1,20 };
	//
	//testobj = Instance("Field");
	//testobj->AddComponent<MeshFilter>()->SetMeshName("box");
	//rig = testobj->AddComponent<Rigidbody>();
	//tr = testobj->GetComponent<Transform>();
	//rig->SetType(false);
	//rig->CreateBoxCollider(20.0f, 1.0f, 1.0f);
	//tr->Scale = { 20.0f,1.0f ,1.0f };
	//tr->Position = { 0,1,-20 };
	//
	//
	//testobj = Instance("Field");
	//testobj->AddComponent<MeshFilter>()->SetMeshName("box");
	//rig = testobj->AddComponent<Rigidbody>();
	//tr = testobj->GetComponent<Transform>();
	//rig->SetType(false);
	//rig->CreateBoxCollider(1.0f, 1.0f, 20.0f);
	//tr->Scale = { 1.0f,1.0f ,20.0f };
	//tr->Position = { 20,1,0 };
	//
	//
	//testobj = Instance("Field");
	//testobj->AddComponent<MeshFilter>()->SetMeshName("box");
	//rig = testobj->AddComponent<Rigidbody>();
	//tr = testobj->GetComponent<Transform>();
	//rig->SetType(false);
	//rig->CreateBoxCollider(1.0f, 1.0f, 20.0f);
	//tr->Scale = { 1.0f,1.0f ,20.0f };
	//tr->Position = { -20,1,0 };

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
