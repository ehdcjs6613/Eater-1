#include "MainHeader.h"
#include "intro.h"
#include "GameObject.h"
#include "MeshFilter.h"
#include "SkinningFilter.h"
#include "AnimationController.h"
#include "Transform.h"
#include "AI.h"
#include "KeyInput.h"
#include "Camera.h"
#include "Light.h"

void intro::Awake()
{
	//불러오는 매쉬의 경로 파악
	LoadMeshPath("../Resources/Mesh/");
	LoadTesturePath("../Resources/Texture/");
	
	//LoadMesh("EnemyB");
	//LoadMesh("Field");
	//LoadMesh("Table");
	//LoadMesh("box");
	LoadMesh("Dome_v03");
	//LoadMesh("1s_table_long_lower");
	LoadMesh("Enemy_Run",false);
	//LoadMesh("Player_Idle");
	LoadMesh("Player_Attack");
	//LoadMesh("Skinning");
	//LoadMesh("Enemy_Run",false,false);
	//LoadMesh("box");
	//LoadMesh("AnimeBox");
	//LoadTesture("body_normal_tangent_Base_color.png");
	LoadTesture("body_normal_tangent_Base_color.png");
	LoadTesture("Grass_Ivy_Diffuse.png");
	LoadTesture("Player.dds");


	///카메라
	testobj = Instance();
	//testobj->AddComponent<Keyinput>();
	testobj->AddComponent<Camera>();
	testobj->AddComponent<Keyinput>();
	testobj->GetTransform()->Position = { 0,0,-25 };

	///라이트
	testobj = Instance();
	testobj->AddComponent<DirectionLight>();

	testobj = Instance("obj");
	MeshFilter* Filter		= testobj->AddComponent<MeshFilter>();
	AnimationController* AC = testobj->AddComponent<AnimationController>();
	Filter->SetMeshName("Enemy_Run");	
	Filter->SetTextureName("Player");
	testobj->GetTransform()->Position	= { -5 ,0, 0 };
	testobj->GetTransform()->Scale		= { 5 ,5, 5 };
	testobj->GetTransform()->Rotation	= {90 ,0,0 };



	testobj = Instance("obj");
	Filter = testobj->AddComponent<MeshFilter>();
	AC = testobj->AddComponent<AnimationController>();
	Filter->SetMeshName("Player_Attack");
	testobj->GetTransform()->Position = { 0 ,0, 0 };
	testobj->GetTransform()->Scale = { 1 ,1, 1 };
	testobj->GetTransform()->Rotation = { 0 ,0,0 };
	
	
	testobj = Instance("obj");
	Filter = testobj->AddComponent<MeshFilter>();
	AC = testobj->AddComponent<AnimationController>();
	Filter->SetMeshName("Dome_v03");
	Filter->SetTextureName("Grass_Ivy_Diffuse");
	testobj->GetTransform()->Position = { 5 ,0, 0 };
	testobj->GetTransform()->Scale = { 0.05f ,0.05f, 0.05f };
	testobj->GetTransform()->Rotation = { 90 ,0,0 };

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
