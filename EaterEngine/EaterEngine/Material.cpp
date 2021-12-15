#include "Material.h"
#include "EngineData.h"
#include "MaterialManager.h"

MaterialManager* Material::MAT_Manager = nullptr;

Material::Material()
{
	// Material Buffer 생성..
	MaterialBuffers = new MaterialBuffer();

	// Material Data 생성..
	MaterialBuffers->Material_Data = new MaterialData();

	// Material 등록..
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
	// 해당 Material Index 삽입..
	MaterialBuffers->Material_Index = index;
}

void Material::PushMaterialData(LoadMeshData* mesh)
{
	// Load한 Material Data가 없을경우..
	if (mesh->Material == nullptr) return;

	// Material Data 추출..
	MaterialData* matData = MaterialBuffers->Material_Data;

	// Material Data 삽입..
	matData->Ambient = mesh->Material->m_Material_Ambient;
	matData->Diffuse = mesh->Material->m_Material_Diffuse;
	matData->Specular = mesh->Material->m_Material_Specular;
	matData->Ambient = mesh->Material->m_Material_Ambient;

	// Texture Map 삽입..
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