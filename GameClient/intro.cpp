#include "MainHeader.h"
#include "intro.h";
#include "GameObject.h"
#include "MeshFilter.h"
#include "Transform.h"
#include "AI.h"
#include "KeyInput.h"
#include "Camera.h"

void intro::Awake()
{
	//�ҷ����� �Ž��� ��� �ľ�
	LoadMeshPath("../Resources/Mesh/");
	LoadTesturePath("../Resources/Texture/");
	
	//LoadMesh("Player");
	//LoadMesh("Table");
	LoadMesh("Dome_v03");
	LoadMesh("box");
	LoadTesture("WoodCrate01");


	///ī�޶�
	testobj = Instance();
	testobj->AddComponent<Keyinput>();
	testobj->AddComponent<Camera>();

	///�׽�Ʈ ������Ʈ
	testobj = Instance("box");
	testobj->AddComponent<MeshFilter>()->SetMeshName("Dome_v03");
	testobj->GetTransform()->Position = { 0,0,0 };
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
