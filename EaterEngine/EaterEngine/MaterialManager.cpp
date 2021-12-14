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
	// ������ Material üũ
	for (auto& matData : m_MaterialList)
	{
		Material* material = matData.second;

		// �ش� Material Data�� List�� �ö��ִ��� üũ..
		if (material->m_MaterialBuffer->Material_Data == mat->m_MaterialBuffer->Material_Data)
		{
			mat->SetMaterialIndex(material->GetMaterialIndex());
			return;
		}
	}

	// Material �߰� �ɶ����� Global Data ����..
	MaterialBuffer* matBuf = mat->m_MaterialBuffer;

	// ���� Material Index ����..
	matBuf->Material_Index = m_MaterialCount;
	
	// ���� Material Data ����..
	Global->mMatData.push_back(matBuf->Material_Data);

	// Material List �߰�..
	m_MaterialList.insert(std::make_pair(m_MaterialCount++, mat));
}
