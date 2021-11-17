#include "MainHeader.h"
#include "intro.h"
#include "GameObject.h"
#include "MeshFilter.h"
#include "SkinningFilter.h"
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
	
	//LoadMesh("Player");
	//LoadMesh("box");
	LoadMesh("Dome_v03");
	//LoadMesh("1s_table_long_lower");
	//LoadMesh("EnemyB");
	//LoadMesh("Player");
	//LoadMesh("Skinning");
	//LoadMesh("Enemy");
	//LoadMesh("box");
	//LoadTesture("body_normal_tangent_Base_color.png");
	LoadTesture("WoodCrate01.dds");

	///카메라
	testobj = Instance();
	testobj->AddComponent<Keyinput>();
	testobj->AddComponent<Camera>();
	testobj->GetTransform()->Position = { 0,0,-100 };

	testobj = Instance("obj");
	MeshFilter* Filter = testobj->AddComponent<MeshFilter>();
	Filter->SetMeshName("Dome_v03");
	Filter->SetTextureName("WoodCrate01");


	testobj->GetTransform()->Position	= { 0 ,0, 0 };
	testobj->GetTransform()->Scale		= { 1 , 1, 1 };
	testobj->GetTransform()->Rotation	= { 90 ,0,0 };
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
