#include "MainHeader.h"
#include "intro.h";
#include "GameObject.h"
#include "MeshFilter.h"
//#include "AI.h"
//#include "KeyInput.h"
#include "Camera.h"

void intro::Awake()
{
	//�ҷ����� �Ž��� ��� �ľ�
	LoadMeshPath("../Resources/Mesh/");
	LoadTesturePath("../Resources/Texture/");
	
	LoadMesh("Table");
	LoadTesture("WoodCrate01");


	///ī�޶�
	testobj = Instance();
	//testobj->AddComponent<AI>();
	testobj->AddComponent<Camera>();
	//
	//
	//testobj = Instance("Table");
	//testobj->AddComponent<MeshFilter>()->SetMeshName("Table");
	//testobj->transform->Position = { 2, 0, 0 };
	//
	//
	//for (int i = 0; i < 5; i++) 
	//{
	//	testobj = Instance("Table");
	//	testobj->AddComponent<MeshFilter>()->SetMeshName("Table");
	//	testobj->transform->Position = {i*2.0f,0,0};
	//}
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
