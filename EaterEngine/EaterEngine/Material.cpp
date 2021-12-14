#include "Material.h"
#include "GameObject.h"
#include "Transform.h"
#include "EngineData.h"

Material::Material()
{
	// Material Buffer 생성..
	m_MaterialBuffer = new MaterialBuffer();

	// Material Data 생성..
	m_MaterialBuffer->Material_Data = new MaterialData();
}

Material::~Material()
{

}

void Material::SetMaterialIndex(UINT index)
{
	// 해당 Material Index 삽입..
	m_Material_Index = index;

	// Object 연동..
	gameobject->OneMeshData->Material_Index = index;
}

UINT Material::GetMaterialIndex()
{
	return m_Material_Index;
}

void Material::SetMaterialData(LoadMeshData* mesh)
{
	// Material Data 추출..
	MaterialData* matData = m_MaterialBuffer->Material_Data;

	// Material Data 삽입..
	matData->Ambient = mesh->Material->m_Material_Ambient;
	matData->Diffuse = mesh->Material->m_Material_Diffuse;
	matData->Specular = mesh->Material->m_Material_Specular;
	matData->Ambient = mesh->Material->m_Material_Ambient;

	// Texture Map 삽입..
	m_MaterialBuffer->Albedo = mesh->Albedo;
	m_MaterialBuffer->Normal = mesh->Normal;

	// Material 추가..
	gameobject->OneMeshData->Material_List.push_back(m_MaterialBuffer);
}

MaterialBuffer* Material::GetMaterialData()
{
	return m_MaterialBuffer;
}
