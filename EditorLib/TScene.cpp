#include "LibDefine.h"
#include "framework.h"
#include "MainHeader.h"
#include "MeshFilter.h"
#include "Transform.h"
#include "TKeyInput.h"
#include "Camera.h"
#include "GameObject.h"
#include "Light.h"
#include "../Physics/BoxCollider.h"
#include "../Library/inc/Component/AnimationController.h"
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
	//LoadMesh("1s_table_long_lower");
	//LoadMesh("MOdNA09_highpoly_1123");
	//LoadMesh("Enemy_Run",false, true);
	//LoadMesh("Player_Attack");
	//LoadMesh("Skinning");
	//LoadMesh("Enemy_Run", false, false);
	//LoadMesh("Inside_dome");
	//LoadMesh("Dome_v03");
	//LoadMesh("Enemy_Roll",false,true);
	//LoadMesh("Anim_Run",false,false);
	//LoadMesh("Anim_Idle",false,true);
	//LoadMesh("Anim_Idle",false,true);
	//LoadMesh("box");
	//LoadMesh("AnimeBox");
	//LoadTesture("body_normal_tangent_Base_color.png");
	LoadTesture("Dump.png");
	//LoadTesture("Player.dds");
	//LoadTesture("MainTexture.png");
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
	testobj->GetTransform()->Scale = { 1.f, 1.0f, 1.0f };
	testobj->GetTransform()->Position = { +10,0,0 };
	testobj->GetTransform()->Rotation = { 0,0,0 };
	MeshFilter* Mf = testobj->AddComponent<MeshFilter>();
	BoxCollider* Bc = testobj->AddComponent<BoxCollider>();
	//Camera* cam = testobj->AddComponent<Camera>();
	//Camera* cam = testobj->AddComponent<Camera>();
	//AnimationController* ac = testobj->AddComponent<AnimationController>();
	Transform* tr = testobj->GetTransform();
	////컨퍼넌트 초기화
	Mf->SetMeshName("box");
	Mf->SetTextureName("Dump.png");
	//Mf->SetAnimationName("Enemy");
	//tr->Rotation = { 90 ,0,0 };

	//testobj2 = Instance("Player2");
	//testobj2->GetTransform()->Scale = { 1.0f, 1.0f, 1.0f };
	//testobj2->GetTransform()->Position = { 1,0,0 };
	//MeshFilter* Mf2 = testobj2->AddComponent<MeshFilter>();
	////AnimationController* ac = testobj->AddComponent<AnimationController>();
	//Transform* tr2 = testobj2->GetTransform();
	//////컨퍼넌트 초기화
	//Mf2->SetMeshName("box");
	//Mf2->SetTextureName("Dump.png");
	//Mf->SetAnimationName("Enemy");
	//tr->Rotation = { 90 ,0,0 };

	
}

void TScene::Start()
{
}

void TScene::Update()
{
	//testobj->GetComponent<BoxCollider>()->Translasion(testobj->GetTransform()->GetWorld());
	
	//DirectX::XMFLOAT4X4 view;
	//DirectX::XMFLOAT4X4 proj;
	//
	//if (nullptr != testobj->GetComponent<BoxCollider>()->md3dDevice)
	//{
	//
	//}
	//if (nullptr != testobj->GetComponent<BoxCollider>()->md3dImmediateContext)
	//{
	//	DirectX::XMStoreFloat4x4(&view, *testobj->GetComponent<Camera>()->GetView());
	//	DirectX::XMStoreFloat4x4(&proj, *testobj->GetComponent<Camera>()->GetProj());
	//	testobj->GetComponent<BoxCollider>()->Draw(view, proj);
	//}

		

}

void TScene::End()
{
}
