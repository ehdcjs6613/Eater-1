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
	//불러오는 매쉬의 경로 파악
	LoadMeshPath("../Resources/Mesh/");
	LoadTesturePath("../Resources/Texture/");
	
	//LoadMesh("Player");
	LoadMesh("Table");
	//LoadMesh("Dome_v03");
	//LoadMesh("EnemyB");
	LoadTesture("WoodCrate01");


	///카메라
	testobj = Instance();
	testobj->AddComponent<Keyinput>();
	testobj->AddComponent<Camera>();

	//testobj = Instance("box");
	//testobj->AddComponent<MeshFilter>()->SetMeshName("EnemyB");
	//testobj->GetTransform()->Position = { 0 ,0,0 };
	//testobj->GetTransform()->Scale = { 1000 ,1000,1000 };
	//testobj->GetTransform()->Rotation = { 90 ,0,0 };



	testobj = Instance("Table");
	testobj->AddComponent<MeshFilter>()->SetMeshName("Table");
	testobj->GetTransform()->Position = { 0 ,0,0 };
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
