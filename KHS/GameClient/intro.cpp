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

	//�ҷ����� �Ž��� ��� �ľ�
	LoadMeshPath("../FBXFile/");
	LoadMesh("Table");
}

void intro::Start()
{
	GameObject* obj = Instance();
	obj->AddComponent<MeshFilter>();
	MeshFilter* temp = obj->GetComponent<MeshFilter>();
	temp->SetMeshName("Table");

}

void intro::Update()
{
	
}

void intro::End()
{


}
