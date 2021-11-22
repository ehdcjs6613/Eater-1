#include "framework.h"
#include "MainHeader.h"
#include "MeshFilter.h"
#include "Transform.h"
#include "TKeyInput.h"
#include "Camera.h"
#include "GameObject.h"
#include "TScene.h"

TScene::TScene()
{
}

TScene::~TScene()
{
}

void TScene::Awake()
{
	LoadMeshPath("../Resources/Mesh/");
	LoadTesturePath("../Resources/Texture/");

	//LoadMesh("Player");
	LoadMesh("Table");
	//LoadMesh("Dome_v03");
	//LoadMesh("1s_table_long_lower");
	//LoadMesh("EnemyB");
	//LoadMesh("Player");
	//LoadMesh("Skinning");
	//LoadMesh("Enemy");
	//LoadMesh("box");
	//LoadTesture("WoodCrate01");

	///Ä«¸Þ¶ó
	testobj = Instance();
	testobj->AddComponent<TKeyInput>();
	testobj->AddComponent<Camera>();

	testobj = Instance("obj");
	testobj->AddComponent<MeshFilter>()->SetMeshName("Table");
	//testobj->AddComponent<AI>();
	testobj->GetTransform()->Position = { 0 ,0, 0 };
	testobj->GetTransform()->Scale = { 1 , 1, 1 };
	testobj->GetTransform()->Rotation = { 0 ,0,0 };
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
