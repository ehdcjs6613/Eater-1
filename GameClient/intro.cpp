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
	//LoadMesh("Table");
	LoadMesh("Dome_v03");
	LoadMesh("box");
	LoadTesture("WoodCrate01");


	///카메라
	testobj = Instance();
	testobj->AddComponent<Keyinput>();
	testobj->AddComponent<Camera>();

	///테스트 오브젝트
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
