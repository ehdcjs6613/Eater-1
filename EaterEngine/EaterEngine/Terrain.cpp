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
	// 새로운 Material 생성..
	Material* newMaterial = new Material();

	// 해당 Material Buffer 추출..
	MaterialBuffer* materialBuffer = newMaterial->GetMaterialData();

	// Material Layer Texture 삽입..
	materialBuffer->Albedo = LoadManager::GetTexture(diffuseName);
	materialBuffer->Normal = LoadManager::GetTexture(normalName);

	// 해당 Material Layer 삽입..
	gameobject->OneMeshData->Material_List.push_back(materialBuffer);
	m_MaterialLayer.push_back(newMaterial);
}
