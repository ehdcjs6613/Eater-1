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

	Global->mMatData.push_back(mat);

	// Material List �߰�..
	m_MaterialList.insert(std::make_pair(m_MaterialCount++, mat));
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
		MaterialData* material = matData.second;

		// �ش� Material Data�� List�� �ö��ִ��� üũ..
		if (*material == *mat->MaterialBuffers->Material_Data)
		{
			mat->SetMaterialIndex(matData.first);
			return;
		}
	}

	// Material �߰� �ɶ����� Global Data ����..
	MaterialBuffer* matBuf = mat->MaterialBuffers;

	// ���� Material Index ����..
	matBuf->Material_Index = m_MaterialCount;
	
	// ���� Material Data ����..
	Global->mMatData.push_back(matBuf->Material_Data);

	// Material List �߰�..
	m_MaterialList.insert(std::make_pair(m_MaterialCount++, matBuf->Material_Data));
}
