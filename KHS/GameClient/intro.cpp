#include "MainHeader.h"
#include "intro.h";
#include "GameObject.h"
#include "MeshFilter.h"
#include "Transform.h"
#include "Camera.h"
#include "KeyInput.h"
#include "AI.h"

void intro::Awake()
{
	//불러오는 매쉬의 경로 파악
	LoadMeshPath("../FBXFile/");
	LoadMesh("Table");
}

void intro::Start()
{
	//GameObject* obj = Instance();
	//obj->AddComponent<MeshFilter>();
	//MeshFilter* temp = obj->GetComponent<MeshFilter>();
	//temp->SetMeshName("Table");

	

	GameObject* obj = Instance();
	obj->AddComponent<Keyinput>();
	obj->AddComponent<Camera>();
	ChoiceMainCamera(obj);
}

void intro::Update()
{
	if (GetKeyDown(VK_SPACE))
	{
		int num = 0;
	}
}

void intro::End()
{


}
