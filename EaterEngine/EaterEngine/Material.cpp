#include "Material.h"
#include "EngineData.h"

Material::Material()
{
	// Material Buffer »ý¼º..
	MaterialBuffers = new MaterialBuffer();

	// Material Data »ý¼º..
	MaterialBuffers->Material_Data = new MaterialData();
}

Material::~Material()
{

}

void Material::SetMaterialIndex(UINT index)
{
	// ÇØ´ç Material Index »ðÀÔ..
	MaterialBuffers->Material_Index = index;
}

UINT Material::GetMaterialIndex()
{
	return MaterialBuffers->Material_Index;
}

void Material::SetMaterialData(LoadMeshData* mesh)
{
	// Material Data ÃßÃâ..
	MaterialData* matData = MaterialBuffers->Material_Data;

	// Material Data »ðÀÔ..
	matData->Ambient = mesh->Material->m_Material_Ambient;
	matData->Diffuse = mesh->Material->m_Material_Diffuse;
	matData->Specular = mesh->Material->m_Material_Specular;
	matData->Ambient = mesh->Material->m_Material_Ambient;

	// Texture Map »ðÀÔ..
	MaterialBuffers->Albedo = mesh->Albedo;
	MaterialBuffers->Normal = mesh->Normal;

}

MaterialBuffer* Material::GetMaterialData()
{
	return MaterialBuffers;
}
