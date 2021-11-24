#include "MainHeader.h"
#include "intro.h"
#include "GameObject.h"
#include "MeshFilter.h"
#include "SkinningFilter.h"
#include "AnimationController.h"
#include "Transform.h"
#include "KeyInput.h"
#include "Player.h"
#include "Camera.h"
#include "Light.h"

void intro::Awake()
{
	//불러오는 매쉬의 경로 파악
	LoadMeshPath("../Resources/Mesh/");
	LoadTesturePath("../Resources/Texture/");
	
	LoadTesture("Dump.png");
	//LoadMesh("Player_Idle");
	//LoadMesh("EnemyB");
	//LoadMesh("Field");
	//LoadMesh("Table");
	//LoadMesh("box");
	//LoadMesh("Dome_v03");
	//LoadMesh("1s_table_long_lower");
	//LoadMesh("MOdNA09_highpoly_1123");
	//LoadMesh("Enemy_Run",false, true);
	//LoadMesh("Player_Attack");
	//LoadMesh("Skinning");
	LoadMesh("Enemy_Run",false,false);
	LoadMesh("Enemy_Roll",false,true);
	//LoadMesh("Anim_Run",	true,false);
	//LoadMesh("Anim_Idle",	false,true);
	//LoadMesh("Anim_Idle",false,true);
	//LoadMesh("box");
	//LoadMesh("AnimeBox");
	//LoadTesture("body_normal_tangent_Base_color.png");
	LoadTesture("Player.dds");
	//LoadTesture("body_normal_tangent_Base_color.png");

	///카메라
	testobj = Instance("Cam");
	testobj->AddComponent<Camera>();
	testobj->AddComponent<Keyinput>();
	testobj->GetTransform()->Position = { 0,0,-25 };
	
	///라이트
	testobj = Instance("DirectionLight");
	testobj->AddComponent<DirectionLight>();

	CreateObject();
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

void intro::CreateObject()
{
	testobj = Instance("obj1");

	testobj->AddComponent<Player>();
	testobj->AddComponent<AnimationController>();
	testobj->AddComponent<MeshFilter>();

	
}
