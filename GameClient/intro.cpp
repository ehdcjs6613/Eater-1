#include "MainHeader.h"
#include "intro.h"
#include "GameObject.h"
#include "MeshFilter.h"
#include "SkinningFilter.h"
#include "AnimationController.h"
#include "Transform.h"
#include "Player.h"
#include "KeyInput.h"
#include "Camera.h"
#include "Light.h"

void intro::Awake()
{
	//�ҷ����� �Ž��� ��� �ľ�
	LoadMeshPath("../Resources/Mesh/");
	LoadTexturePath("../Resources/Texture/");
	
	LoadMesh("Player_Run", false,false);
	LoadMesh("Player_Roll",false,true);
	LoadMesh("Player_Idle",false,true);
	LoadMesh("Pistol",true,false);
	LoadMesh("Weapon",true,false);

	LoadTexture("Player.dds");
	LoadTexture("Dump.png");
	

	CreateCam();
	CreateLignt();
	CreatePlayer();
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

void intro::CreatePlayer()
{
	///ĳ����
	GameObject* temp = Instance("Player");
	temp->AddComponent<AnimationController>();
	temp->AddComponent<MeshFilter>();
	temp->AddComponent<Player>();
}

void intro::CreateLignt()
{
	///����Ʈ
	GameObject* temp = Instance("DirectionLight");
	temp->AddComponent<DirectionLight>();
}

void intro::CreateCam()
{
	///ī�޶�
	GameObject* temp = Instance("Cam");
	temp->AddComponent<Camera>();
	temp->AddComponent<Keyinput>();
	temp->GetTransform()->Position = { 0,0,-25 };
}
