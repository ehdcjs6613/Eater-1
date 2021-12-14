#include "Material.h"
#include "GameObject.h"
#include "Transform.h"
#include "EngineData.h"

Material::Material()
{
	// Material Buffer »ý¼º..
	m_MaterialBuffer = new MaterialBuffer();

	// Material Data »ý¼º..
	m_MaterialBuffer->Material_Data = new MaterialData();
}

Material::~Material()
{

}

void Material::Awake()
{
	// Material Ãß°¡..
	gameobject->OneMeshData->Material_List.push_back(m_MaterialBuffer);
}

void Material::SetMaterialIndex(UINT index)
{
	// ÇØ´ç Material Index »ðÀÔ..
	m_MaterialBuffer->Material_Index = index;
}

UINT Material::GetMaterialIndex()
{
	return m_MaterialBuffer->Material_Index;
}

void Material::SetMaterialData(LoadMeshData* mesh)
{
	// Material Data ÃßÃâ..
	MaterialData* matData = m_MaterialBuffer->Material_Data;

	// Material Data »ðÀÔ..
	matData->Ambient = mesh->Material->m_Material_Ambient;
	matData->Diffuse = mesh->Material->m_Material_Diffuse;
	matData->Specular = mesh->Material->m_Material_Specular;
	matData->Ambient = mesh->Material->m_Material_Ambient;

	// Texture Map »ðÀÔ..
	m_MaterialBuffer->Albedo = mesh->Albedo;
	m_MaterialBuffer->Normal = mesh->Normal;

}

MaterialBuffer* Material::GetMaterialData()
{
	return m_MaterialBuffer;
}
