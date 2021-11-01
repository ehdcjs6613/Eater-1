#include "MainHeader.h"
#include "intro.h";
#include "GameObject.h"
#include "MeshFilter.h"
#include "Transform.h"
#include "KeyInput.h"
#include "Camera.h"

void intro::Awake()
{
	//불러오는 매쉬의 경로 파악
	LoadMeshPath("../FBXFile/");
	LoadMesh("Table");

	///카메라
	testobj = Instance();
	testobj->AddComponent<Keyinput>();
	testobj->AddComponent<Camera>();

	
	testobj = Instance("Table");
	testobj->AddComponent<MeshFilter>()->SetMeshName("Table");
	testobj->transform->Position = { 2, 0, 0 };

	
	for (int i = 0; i < 5; i++) 
	{
		testobj = Instance("Table");
		testobj->AddComponent<MeshFilter>()->SetMeshName("Table");
		testobj->transform->Position = {i*2.0f,0,0};
	}
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
