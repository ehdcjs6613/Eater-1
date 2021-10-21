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
	
	//GetMesh("Table");


	GameObject* obj = Instance();
	obj->AddComponent<Transfrom>();
	obj->AddComponent<MeshFilter>();
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
