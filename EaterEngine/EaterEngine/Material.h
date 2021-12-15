#pragma once
#include "Component.h"
#include "EaterEngineDLL.h"

class MaterialBuffer;
class LoadMeshData;

class Material
{
public:
	Material();
	~Material();

public:
	friend class MaterialManager;

public:
	void SetMaterialIndex(UINT index);
	UINT GetMaterialIndex();

	void SetMaterialData(LoadMeshData* mesh);
	MaterialBuffer* GetMaterialData();

private:
	MaterialBuffer* MaterialBuffers;
};

