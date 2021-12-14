#include "GameObject.h"
#include "Transform.h"
#include "Material.h"
#include "MaterialManager.h"
#include "EngineData.h"



MaterialManager::MaterialManager()
	:m_MaterialCount(0)
{

}

MaterialManager::~MaterialManager()
{

}

void MaterialManager::Initialize()
{
	// Basic Material..
	MaterialData* mat = new MaterialData();
	mat->Ambient = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	mat->Diffuse = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	mat->Specular = Vector4(0.4f, 0.4f, 0.4f, 1.0f);
	mat->Reflect = Vector4(0.4f, 0.4f, 0.4f, 1.0f);

	Global->mMatData.push_back(mat);
	m_MaterialCount++;
}

void MaterialManager::Release()
{
	m_MaterialList.clear();
}

void MaterialManager::AddMaterial(Material* mat)
{
	// 동일한 Material 체크
	for (auto& matData : m_MaterialList)
	{
		Material* material = matData.second;

		// 해당 Material Data가 List에 올라가있는지 체크..
		if (material->m_MaterialBuffer->Material_Data == mat->m_MaterialBuffer->Material_Data)
		{
			mat->SetMaterialIndex(material->GetMaterialIndex());
			return;
		}
	}

	// Material 추가 될때마다 Global Data 설정..
	MaterialBuffer* matBuf = mat->m_MaterialBuffer;

	// 현재 Material Index 설정..
	matBuf->Material_Index = m_MaterialCount;
	
	// 현재 Material Data 삽입..
	Global->mMatData.push_back(matBuf->Material_Data);

	// Material List 추가..
	m_MaterialList.insert(std::make_pair(m_MaterialCount++, mat));
}
