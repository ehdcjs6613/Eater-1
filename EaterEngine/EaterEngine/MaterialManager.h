#pragma once
#include <unordered_map>
#include "BaseManager.h"
#include "LightHelper.h"

class MaterialManager : public BaseManager
{
public:
	MaterialManager();
	~MaterialManager();

public:
	void Update();
	void Release();

	void AddMaterial(MaterialData* mat);

private:
	std::unordered_map<int, MaterialData*> m_MaterialList;
	
	UINT m_CountID;
};

