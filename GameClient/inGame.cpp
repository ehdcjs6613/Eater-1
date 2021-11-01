#include "MainHeader.h"
#include "inGame.h"
#include "intro.h";
#include "GameObject.h"
#include "MeshFilter.h"
#include "Transform.h"
#include "KeyInput.h"
#include "Camera.h"

void InGame::Awake()
{
	//�ҷ����� �Ž��� ��� �ľ�
	///ī�޶�
	GameObject* testobj = Instance("ī�޶� ������Ʈ");
	testobj->AddComponent<Keyinput>();
	testobj->AddComponent<Camera>();


	testobj = Instance();
	testobj->AddComponent<MeshFilter>()->SetMeshName("Table");
	testobj->transform->Position = { 2, 0, 0 };
	
}

void InGame::Start()
{
}

void InGame::Update()
{
	
}

void InGame::End()
{
}
