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
	//�ҷ����� �Ž��� ��� �ľ�
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

	///ī�޶�
	testobj = Instance("Cam");
	testobj->AddComponent<Camera>();
	testobj->AddComponent<TKeyInput>();
	testobj->GetTransform()->Position = { 0,0,-25 };

	///����Ʈ
	testobj = Instance("DirectionLight");
	testobj->AddComponent<DirectionLight>();



	///ĳ����
	testobj = Instance("Player");
	MeshFilter* Mf = testobj->AddComponent<MeshFilter>();
	AnimationController* ac = testobj->AddComponent<AnimationController>();
	Transform* tr = testobj->GetTransform();
	////���۳�Ʈ �ʱ�ȭ
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
	///����
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
