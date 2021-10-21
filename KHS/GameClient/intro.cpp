#include "MainHeader.h"
#include "Scene.h"
#include "intro.h";
#include "GameObject.h"
#include "MeshFilter.h"
#include "Transfrom.h"

#include "AI.h"

void intro::Awake()
{
	//불러오는 매쉬의 경로 파악
	LoadMeshPath("../FBXFile/");
	LoadMesh("Table");
	
	
}

void intro::Start()
{
	GameObject* obj = Instance();
	obj->AddComponent<Transfrom>();
	obj->AddComponent<MeshFilter>();
	MeshFilter* temp = obj->GetComponent<MeshFilter>();
	GetMeshFilter("Table", temp);
}

void intro::Update()
{


}

void intro::End()
{


}
