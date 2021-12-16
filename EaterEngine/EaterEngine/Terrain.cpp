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

void Terrain::SetTextureTiling(float scale)
{
	gameobject->OneMeshData->mTexTM = DirectX::SimpleMath::Matrix::CreateScale(scale, scale, 1.0f);
}

void Terrain::SetTextureTiling(float scale_x, float scale_y)
{
	gameobject->OneMeshData->mTexTM = DirectX::SimpleMath::Matrix::CreateScale(scale_x, scale_y, 1.0f);
}
