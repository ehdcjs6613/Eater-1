#pragma once
#include "Component.h"
#include "EaterEngineDLL.h"

class MaterialBuffer;
class LoadMeshData;
class TextureBuffer;
class MaterialManager;

class Material
{
public:
	Material();
	~Material();

public:
	friend class MaterialManager;

public:
	static void SetManager(MaterialManager* mat);

public:
	void SetMaterialIndex(UINT index);

	void PushMaterialData(LoadMeshData* mesh);

	void SetDiffuseMap(TextureBuffer* diffuse);
	void SetNormalMap(TextureBuffer* noraml);

	void SetBaseColor(DirectX::SimpleMath::Vector4 color);
	void SetAddColor(DirectX::SimpleMath::Vector4 color);

public:
	UINT GetMaterialIndex();
	MaterialBuffer* GetMaterialData();

private:
	static MaterialManager* MAT_Manager;

	MaterialBuffer* MaterialBuffers;
};

