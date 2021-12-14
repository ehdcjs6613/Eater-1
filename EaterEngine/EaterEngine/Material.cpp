#include "Material.h"
#include "GameObject.h"
#include "Transform.h"
#include "EngineData.h"

Material::Material()
{
	// Material Buffer ����..
	m_MaterialBuffer = new MaterialBuffer();

	// Material Data ����..
	m_MaterialBuffer->Material_Data = new MaterialData();
}

Material::~Material()
{

}

void Material::SetMaterialIndex(UINT index)
{
	// �ش� Material Index ����..
	m_Material_Index = index;

	// Object ����..
	gameobject->OneMeshData->Material_Index = index;
}

UINT Material::GetMaterialIndex()
{
	return m_Material_Index;
}

void Material::SetMaterialData(LoadMeshData* mesh)
{
	// Material Data ����..
	MaterialData* matData = m_MaterialBuffer->Material_Data;

	// Material Data ����..
	matData->Ambient = mesh->Material->m_Material_Ambient;
	matData->Diffuse = mesh->Material->m_Material_Diffuse;
	matData->Specular = mesh->Material->m_Material_Specular;
	matData->Ambient = mesh->Material->m_Material_Ambient;

	// Texture Map ����..
	m_MaterialBuffer->Albedo = mesh->Albedo;
	m_MaterialBuffer->Normal = mesh->Normal;

	// Material �߰�..
	gameobject->OneMeshData->Material_List.push_back(m_MaterialBuffer);
}

MaterialBuffer* Material::GetMaterialData()
{
	return m_MaterialBuffer;
}
