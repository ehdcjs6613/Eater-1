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
#include "Rigidbody.h"

void intro::Awake()
{
	//�ҷ����� �Ž��� ��� �ľ�
	LoadMeshPath("../Resources/Mesh/");
	LoadTexturePath("../Resources/Texture/");

	LoadMesh("box");
	LoadMesh("Terrain2");
	LoadMesh("Sphere");

	LoadTexture("Dump.png");

	///ī�޶�
	testobj = Instance("Cam");
	testobj->AddComponent<Camera>();
	testobj->AddComponent<Keyinput>();
	testobj->GetTransform()->Position = { 0,0,-25 };

	///����Ʈ
	testobj = Instance("DirectionLight");
	testobj->AddComponent<DirectionLight>();

	///�ͷ���
	testobj = Instance("obj");
	Mf = testobj->AddComponent<MeshFilter>();
	Tr = testobj->GetComponent<Transform>();
	Rig = testobj->AddComponent<Rigidbody>();
	
	Rig->CreateTriangleCollider("Terrain2");
	Mf->SetMeshName("Terrain2");
	Tr->Position = { 0,10,0 };
	Tr->Rotation = { 0,0,0 };

	for (int i = 0; i < 9; i++)
	{
		///��
		testobj = Instance("obj");
		Mf	= testobj->AddComponent<MeshFilter>();
		Rig = testobj->AddComponent<Rigidbody>();
		Tr	= testobj->GetComponent<Transform>();
	
		Mf->SetMeshName("Sphere");
		Rig->CreateSphereCollider(0.5f);
		Tr->Position = { (float)i,30,(float)i};
		Tr->Scale = { 0.5f,0.5f,0.5f };
	}

	//testobj = Instance("obj");
	//Mf = testobj->AddComponent<MeshFilter>();
	//Rig = testobj->AddComponent<Rigidbody>();
	//Tr = testobj->GetComponent<Transform>();
	//testobj->GetComponent<Player>();
	//
	//Mf->SetMeshName("Sphere");
	//Rig->CreateSphereCollider(0.5f);
	//Tr->Position = { (float)0,30,(float)0 };
	//Tr->Scale = { 0.5f,0.5f,0.5f };
	
	
	
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
