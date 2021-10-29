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
	GameObject* obj = Instance();
	obj->AddComponent<Keyinput>();
	obj->AddComponent<Camera>();

	//불러오는 매쉬의 경로 파악
	LoadMeshPath("../FBXFile/");
	LoadMesh("Table");
}

void intro::Start()
{
	GameObject* obj = Instance();
	obj->AddComponent<MeshFilter>();
	MeshFilter* temp = obj->GetComponent<MeshFilter>();
	temp->SetMeshName("Table");
	t = obj->GetComponent<Transform>();



	
	

	for (int i = -5; i < 5; i++)
	{
		for (int j = -5; j < 5; j++)
		{
			obj = Instance();
			obj->AddComponent<MeshFilter>();
			temp = obj->GetComponent<MeshFilter>();
			temp->SetMeshName("Table");
			Transform* tr = obj->GetComponent<Transform>();
			tr->Position = { (float)i*2,0,(float)j*2 };
		}
	}

}

void intro::Update()
{
	
}

void intro::End()
{


}
