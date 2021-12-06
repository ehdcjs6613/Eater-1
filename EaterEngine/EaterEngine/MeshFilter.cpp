#include "MeshFilter.h"
#include "DebugManager.h"
#include "SkinningFilter.h"
#include "AnimationController.h"
#include "GameObject.h"
#include "LoadManager.h"
#include "Transform.h"
#include "EngineData.h"
#include "Animator.h"
#include "ObjectManager.h"
#include "Material.h"
#include "MaterialManager.h"


ObjectManager* MeshFilter::OBJ_Manager = nullptr;
MaterialManager* MeshFilter::MAT_Manager = nullptr;

MeshFilter::MeshFilter()
{
	MeshName = "";

	//��� ���۳�Ʈ�� Start�Լ����� ���߿� ����ɰ��̴�
	Start_Order = FUNCTION_ORDER_LAST;
}

MeshFilter::~MeshFilter()
{

}

void MeshFilter::Start()
{
	//Ŭ���̾�Ʈ�ʿ��� �ؽ����� �̸��� �ְ� �ִϸ��̼��� �ְ� ��� ��������
	if (isLoad_Texture == true) 
	{
		CheckTexture();
	}

	if (isLoad_Animation == true)
	{
		CheckAnimation();
	}
}

void MeshFilter::SetManager(ObjectManager* obj, MaterialManager* mat)
{
	OBJ_Manager = obj;
	MAT_Manager = mat;
}

void MeshFilter::SetMeshName(std::string mMeshName)
{
	isLoad_Mesh = true;
	MeshName = mMeshName;
	CreateMesh();
}

void MeshFilter::SetTextureName(std::string mTextureName)
{
	isLoad_Texture = true;
	TextureName = mTextureName;
}

void MeshFilter::SetNormalTextureName(std::string mTextureName)
{


}

void MeshFilter::SetAnimationName(std::string mAnimeName)
{
	isLoad_Animation = true;
	AnimationName = mAnimeName;
	CheckAnimation();
}

void MeshFilter::PushModelData(LoadMeshData* mModel)
{
	MeshData* data = gameobject->OneMeshData;

	data->IB = mModel->IB;
	data->VB = mModel->VB;

	data->Diffuse	= mModel->Diffuse;
	data->Normal	= mModel->Normal;

	data->mLocal = *(mModel->LocalTM);
	data->mWorld = *(mModel->WorldTM);

	// Diffuse Map�� ���°�� Dump Map���� �⺻ ���..
	if (data->Diffuse == nullptr)
	{
		data->Diffuse = LoadManager::GetTexture("Dump");
	}
}

void MeshFilter::CheckTexture()
{
	// ������ Texture�� ������� �ε��� Diffuse ��� �ش� Texture ����..
	if (TextureName.empty() == false)
	{
		// �ش� Object Mesh Data..

		for (int i = 0; i <(int)MeshList.size(); i++)
		{
			MeshData* data = MeshList[i]->OneMeshData;

			// ���� Texture Buffer..
			TextureBuffer* texBuffer = LoadManager::GetTexture(TextureName);
		

			// �ش� Texture�� Load���� ���� ��� ���� Texture ���..
			if (texBuffer == nullptr)
			{
				return;
			}

			// Texture ����..
			data->Diffuse = texBuffer;
		}
	}
}

void MeshFilter::CheckAnimation()
{
	if (isLoad_Animation == false) { return; }
	
	ModelAnimationData* data		= LoadManager::GetAnimation(AnimationName);
	AnimationController* Controller = gameobject->GetComponent<AnimationController>();
	
	//������ ���۳�Ʈ�� �� ������ �Ѱ��ش�
	if (Controller != nullptr)
	{	
		Controller->SetBoneList(&BoneList);
		Controller->SetAnimeList(data);
	}
}

void MeshFilter::CreateChild_Mesh(LoadMeshData* data, Transform* parent, ModelData* modeldata)
{
	DebugManager::Line("(Mesh)");

	///���� ������Ʈ ����
	GameObject* OBJ = new GameObject();

	///���۳�Ʈ ������ �ʱ�ȭ
	Transform* Tr		= OBJ->AddComponent<Transform>();
	MeshFilter* Filter	= OBJ->AddComponent<MeshFilter>();

	///��Ű�� ������Ʈ ����
	if (data->Skinning_Object == true)
	{
		SkinningFilter* SF = OBJ->AddComponent<SkinningFilter>();
		SF->PushBoneList(&BoneList);
		SF->PushBone_OffsetList(&BoneOffsetList);
		OBJ->OneMeshData->ObjType = OBJECT_TYPE::SKINNING;
		Tr->Rotation = { 180,0,0 };
	}
	else
	{
		LinkHierarchy(Tr, parent);
		OBJ->OneMeshData->ObjType = OBJECT_TYPE::BASE;
	}

	///���׸��� ���� ����
	if (data->Material)
	{
		Material* mat = OBJ->AddComponent<Material>();
		MaterialData matData;
		matData.Ambient		= data->Material->m_Material_Ambient;
		matData.Diffuse		= data->Material->m_Material_Diffuse;
		matData.Specular	= data->Material->m_Material_Specular;
		mat->SetMaterialData(matData);	// �ش� Material ����..
		MAT_Manager->AddMaterial(mat);	// Material ���..
	}

	///�⺻ ������ �ʱ�ȭ
	OBJ->Name = data->Name;
	OBJ->transform = Tr;
	Filter->PushModelData(data);
	Tr->Load_Local = *data->LocalTM;
	Tr->Load_World = *data->WorldTM;
	OBJ_Manager->PushCreateObject(OBJ);
	MeshList.push_back(OBJ);

	///��� �Լ�
	int ChildCount = (int)data->Child.size();
	for (int i = 0; i < ChildCount; i++)
	{
		Filter->CreateChild_Mesh(data->Child[i], Tr, modeldata);
	}
}

void MeshFilter::CreateChild_Bone(LoadMeshData* data, Transform* parent, std::vector<GameObject*>* mBoneList, std::vector<DirectX::SimpleMath::Matrix>* BoneOffsetList)
{
	DebugManager::Line("(Bone)");

	///������Ʈ�� ����
	GameObject* OBJ = new GameObject();

	///���۳�Ʈ ����
	Transform*	Tr	= OBJ->AddComponent<Transform>();
	MeshFilter* MF	= OBJ->AddComponent<MeshFilter>();
	Animator*	AN	= OBJ->AddComponent<Animator>();

	///�ʱ�ȭ ����
	if (data->Top_Object == true){Tr->Rotation = { -90,0,0 };}
	OBJ->OneMeshData->ObjType = OBJECT_TYPE::BONE;
	OBJ->transform	= Tr;
	OBJ->Name		=  data->Name;
	Tr->Load_Local	= *data->LocalTM;
	Tr->Load_World	= *data->WorldTM;
	gameobject->PushChildBoneObject(OBJ);
	OBJ_Manager->PushCreateObject(OBJ);
	LinkHierarchy(Tr, parent);
	//���� �ش��ϴ� Transform�� ���������־��ش�
	(*mBoneList)[data->BoneIndex] = OBJ;
	(*BoneOffsetList)[data->BoneIndex] = (*data->BoneOffset);


	///��� �Լ�
	int ChildCount = (int)data->Child.size();
	for (int i = 0; i < ChildCount; i++)
	{
		MF->CreateChild_Bone(data->Child[i], Tr, mBoneList, BoneOffsetList);
	}
}

void MeshFilter::LinkHierarchy(Transform* my, Transform* parent)
{
	my->SetParnet(parent);
	parent->SetChild(my);
}

void MeshFilter::CreateMesh()
{
	///�̸����� �ε��� �����͸� ã�Ƽ� ������
	ModelData* data = LoadManager::GetMesh(MeshName);
	Transform* Tr = gameobject->GetTransform();
	if (data == nullptr) { return; }

	///�� ������Ʈ ����
	int index = 0;
	index = (int)data->TopBoneList.size();
	if (data->BoneList != nullptr)
	{
		BoneList.resize((int)data->BoneList->size());
		BoneOffsetList.resize((int)data->BoneOffsetList->size());

		for (int i = 0; i < index; i++)
		{
			CreateChild_Bone(data->TopBoneList[i], Tr, &BoneList, &BoneOffsetList);
		}
	}

	///�޽� ������Ʈ ����
	index = (int)data->TopMeshList.size();
	for (int i = 0; i < index; i++)
	{
		CreateChild_Mesh(data->TopMeshList[i], Tr, data);
	}

	///������Ʈ �����Ϸ�
	isLoad_Mesh = true;
}




