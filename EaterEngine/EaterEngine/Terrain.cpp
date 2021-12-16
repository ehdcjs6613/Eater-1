#include "Material.h"
#include "Terrain.h"
#include "LoadManager.h"
#include "EngineData.h"
#include "GameObject.h"

Terrain::Terrain()
{

}

Terrain::~Terrain()
{

}

void Terrain::AddLayer(std::string diffuseName, std::string normalName)
{
	// ���ο� Material ����..
	Material* newMaterial = new Material();

	// �ش� Material Buffer ����..
	MaterialBuffer* materialBuffer = newMaterial->GetMaterialData();

	// Material Layer Texture ����..
	materialBuffer->Albedo = LoadManager::GetTexture(diffuseName);
	materialBuffer->Normal = LoadManager::GetTexture(normalName);

	// �ش� Material Layer ����..
	gameobject->OneMeshData->Material_List.push_back(materialBuffer);
	m_MaterialLayer.push_back(newMaterial);
}
