#pragma once
#include "Component.h"
#include "EaterEngineDLL.h"

class MaterialData;
class LoadMeshData;

class Material : public Component
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
	UINT m_Material_Index;

	MaterialBuffer* m_MaterialBuffer;
};

