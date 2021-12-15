#include "Material.h"
#include "EngineData.h"
#include "MaterialManager.h"

MaterialManager* Material::MAT_Manager = nullptr;

Material::Material()
{
	// Material Buffer ����..
	MaterialBuffers = new MaterialBuffer();

	// Material Data ����..
	MaterialBuffers->Material_Data = new MaterialData();

	// Material ���..
	MAT_Manager->AddMaterial(this);
}

Material::~Material()
{

}

void Material::SetManager(MaterialManager* mat)
{
	MAT_Manager = mat;
}

void Material::SetMaterialIndex(UINT index)
{
	// �ش� Material Index ����..
	MaterialBuffers->Material_Index = index;
}

void Material::PushMaterialData(LoadMeshData* mesh)
{
	// Load�� Material Data�� �������..
	if (mesh->Material == nullptr) return;

	// Material Data ����..
	MaterialData* matData = MaterialBuffers->Material_Data;

	// Material Data ����..
	matData->Ambient = mesh->Material->m_Material_Ambient;
	matData->Diffuse = mesh->Material->m_Material_Diffuse;
	matData->Specular = mesh->Material->m_Material_Specular;
	matData->Ambient = mesh->Material->m_Material_Ambient;

	// Texture Map ����..
	MaterialBuffers->Albedo = mesh->Albedo;
	MaterialBuffers->Normal = mesh->Normal;
}

void Material::SetDiffuseMap(TextureBuffer* diffuse)
{
	MaterialBuffers->Albedo = diffuse;
}

void Material::SetNormalMap(TextureBuffer* noraml)
{
	MaterialBuffers->Albedo = noraml;
}

void Material::SetBaseColor(DirectX::SimpleMath::Vector4 color)
{
	MaterialBuffers->Color_Base = color;
}

void Material::SetAddColor(DirectX::SimpleMath::Vector4 color)
{
	MaterialBuffers->Color_Add = color;
}

MaterialBuffer* Material::GetMaterialData()
{
	return MaterialBuffers;
}

UINT Material::GetMaterialIndex()
{
	return MaterialBuffers->Material_Index;
}