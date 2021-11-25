#include "framework.h"
#include "MainHeader.h"
#include "MeshFilter.h"
#include "Transform.h"
#include "TKeyInput.h"
#include "Camera.h"
#include "GameObject.h"
#include "Light.h"
#include "AnimationController.h"
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
	//LoadMesh("box");
	//LoadMesh("1s_table_long_lower");
	//LoadMesh("MOdNA09_highpoly_1123");
	//LoadMesh("Enemy_Run",false, true);
	//LoadMesh("Player_Attack");
	//LoadMesh("Skinning");
	LoadMesh("Enemy_Run", false, false);
	LoadMesh("Inside_dome");
	LoadMesh("Dome_v03");
	//LoadMesh("Enemy_Roll",false,true);
	//LoadMesh("Anim_Run",false,false);
	//LoadMesh("Anim_Idle",false,true);
	//LoadMesh("Anim_Idle",false,true);
	//LoadMesh("box");
	//LoadMesh("AnimeBox");
	//LoadTesture("body_normal_tangent_Base_color.png");
	LoadTesture("Dump.png");
	LoadTesture("Player.dds");
	LoadTesture("MainTexture.png");
	//LoadTesture("body_normal_tangent_Base_color.png");

	///카메라
	testobj = Instance("Cam");
	testobj->AddComponent<Camera>();
	testobj->AddComponent<TKeyInput>();
	testobj->GetTransform()->Position = { 0,0,-25 };

	///라이트
	testobj = Instance("DirectionLight");
	testobj->AddComponent<DirectionLight>();



	///캐릭터
	testobj = Instance("Player");
	MeshFilter* Mf = testobj->AddComponent<MeshFilter>();
	AnimationController* ac = testobj->AddComponent<AnimationController>();
	Transform* tr = testobj->GetTransform();
	////컨퍼넌트 초기화
	Mf->SetMeshName("Enemy_Run");
	Mf->SetTextureName("Player");
	Mf->SetAnimationName("Enemy");
	tr->Rotation = { 90 ,0,0 };


	/// MAP
	testobj = Instance("obj1");
	Mf = testobj->AddComponent<MeshFilter>();
	ac = nullptr;
	tr = testobj->GetTransform();
	Mf->SetMeshName("Inside_dome");
	Mf->SetTextureName("MainTexture");
	tr->Rotation = { 90 ,0,0 };

	//
	///원형
	testobj = Instance("Inside_dome");
	Mf = testobj->AddComponent<MeshFilter>();
	ac = nullptr;
	tr = testobj->GetTransform();
	Mf->SetMeshName("Dome_v03");
	Mf->SetTextureName("MainTexture");
	tr->Rotation = { 90 ,0,0 };
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
