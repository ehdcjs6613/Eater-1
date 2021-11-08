#include "MainHeader.h"
#include "MeshFilter.h"
#include "Transform.h"
#include "AI.h"
#include "KeyInput.h"
#include "Camera.h"
#include "GameObject.h"
#include "intro.h";


intro::intro()
{

	
	//testobj = new GameObject();
	
}

void intro::Awake()
{
	//�ҷ����� �Ž��� ��� �ľ�
	LoadMeshPath("../Resources/Mesh/");
	LoadTesturePath("../Resources/Texture/");
	
	//LoadMesh("Player");
	//LoadMesh("Table");
	LoadMesh("box");
	LoadTesture("WoodCrate01");


	///ī�޶�
	testobj = Instance();
	testobj->AddComponent<Keyinput>();
	testobj->AddComponent<Camera>();

	///�׽�Ʈ ������Ʈ
	testobj = Instance("box");
	testobj->AddComponent<MeshFilter>()->SetMeshName("box");
	testobj->GetTransform()->Position = {0,1,0 };
	testobj->GetTransform()->Scale = { 0.5f,0.5f,0.5f };
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
