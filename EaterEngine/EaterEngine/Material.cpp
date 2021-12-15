#include "Material.h"
#include "EngineData.h"

Material::Material()
{
	// Material Buffer ����..
	MaterialBuffers = new MaterialBuffer();

	// Material Data ����..
	MaterialBuffers->Material_Data = new MaterialData();
}

Material::~Material()
{

}

void Material::SetMaterialIndex(UINT index)
{
	// �ش� Material Index ����..
	MaterialBuffers->Material_Index = index;
}

UINT Material::GetMaterialIndex()
{
	return MaterialBuffers->Material_Index;
}

void Material::SetMaterialData(LoadMeshData* mesh)
{
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

MaterialBuffer* Material::GetMaterialData()
{
	return MaterialBuffers;
}
