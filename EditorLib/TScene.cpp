#include "framework.h"
#include "MainHeader.h"
#include "MeshFilter.h"
#include "Transform.h"
#include "TKeyInput.h"
#include "Camera.h"
#include "GameObject.h"
#include "Light.h"
#include "../Physics/BoxCollider.h"
#include "TScene.h"

TScene::TScene()
{
}

TScene::~TScene()
{
}

void TScene::Awake()
{
	//불러오는 매쉬의 경로 파악
	LoadMeshPath("../Resources/Mesh/");
	LoadTesturePath("../Resources/Texture/");

	//LoadMesh("Player_Idle");
	//LoadMesh("EnemyB");
	//LoadMesh("Field");
	//LoadMesh("Table");
	LoadMesh("box");
	//LoadMesh("Dome_v03");
	//LoadMesh("1s_table_long_lower");
	//LoadMesh("MOdNA09_highpoly_1123");
	//LoadMesh("Enemy_Run",false, true);
	//LoadMesh("Player_Attack");
	//LoadMesh("Skinning");
	//LoadMesh("Enemy_Run",false,false);
	//LoadMesh("box");
	//LoadMesh("AnimeBox");
	//LoadTesture("body_normal_tangent_Base_color.png");
	LoadTesture("Dump.png");
	LoadTesture("Player.dds");
	LoadTesture("body_normal_tangent_Base_color.png");

	///카메라
	testobj = Instance("Cam");
	testobj->AddComponent<Camera>();
	testobj->AddComponent<TKeyInput>();
	testobj->GetTransform()->Position = { 0,0,-25 };

	///라이트
	testobj = Instance("DirectionLight");
	testobj->AddComponent<DirectionLight>();

	//testobj = Instance("obj");
	//MeshFilter* Filter		= testobj->AddComponent<MeshFilter>();
	//AnimationController* AC = testobj->AddComponent<AnimationController>();
	//Filter->SetMeshName("MOdNA09_highpoly_1123");

	testobj = Instance("obj1");
	MeshFilter* Filter = testobj->AddComponent<MeshFilter>();
	//AnimationController* AC = testobj->AddComponent<AnimationController>();
	Filter->SetMeshName("box");
	//Filter->SetTextureName("Player");
	//testobj->SetActive(false);
	testobj->AddComponent<BoxCollider>();
	//테스트용 박스 콜 라이다


	testobj->GetTransform()->Position = { 0 ,0, 0 };
	testobj->GetTransform()->Scale = { 1 ,1, 1 };
	testobj->GetTransform()->Rotation = { 90 ,0,0 };
}

void TScene::Start()
{
}

void TScene::Update()
{
}

void TScene::End()
{
}
