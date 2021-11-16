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
	//�ҷ����� �Ž��� ��� �ľ�
	LoadMeshPath("../Resources/Mesh/");
	LoadTesturePath("../Resources/Texture/");
	
	//LoadMesh("Player");
	//LoadMesh("Table");
	//LoadMesh("Dome_v03");
	//LoadMesh("1s_table_long_lower");
	//LoadMesh("EnemyB");
	LoadMesh("Player");
	//LoadMesh("Skinning");
	//LoadMesh("Enemy");
	//LoadMesh("box");
	LoadTesture("WoodCrate01");

	///ī�޶�
	testobj = Instance();
	testobj->AddComponent<Keyinput>();
	testobj->AddComponent<Camera>();

	testobj = Instance("obj");
	testobj->AddComponent<MeshFilter>()->SetMeshName("Player");
	//testobj->AddComponent<AI>();
	testobj->GetTransform()->Position = { 0 ,0, 0 };
	testobj->GetTransform()->Scale = { 1 , 1, 1 };
	testobj->GetTransform()->Rotation = { 90 ,0,0 };
	//�Ž� ���ͷ� �Ž��� ������ ���� ������Ʈ
	
	//
	//
	////��Ű�����ͷ� ���� �Ž����� �Ѵ� ���� ������Ʈ
	//testobj = Instance("Table");
	//testobj->AddComponent<SkinningFilter>()->SetMeshName("EnemyB");
	//testobj->GetTransform()->Position = { 1 ,0,0 };
	//testobj->GetTransform()->Scale = { 100 ,100,100 };
	//testobj->GetTransform()->Rotation = { 90 ,0,0 };
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
