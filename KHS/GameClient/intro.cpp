#include "MainHeader.h"
#include "Scene.h"
#include "intro.h";
#include "GameObject.h"
#include "MeshFilter.h"
#include "Transfrom.h"
#include "AI.h"

void intro::Awake()
{
	//�ҷ����� �Ž��� ��� �ľ�
	LoadMeshPath("../FBXFile/");
	LoadMesh("Table");


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
