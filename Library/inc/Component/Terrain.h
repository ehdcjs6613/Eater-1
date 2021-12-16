#pragma once
#include "EaterEngineDLL.h"
#include "Component.h"
#include <vector>
#include <string>

struct TerrainLayer
{

};

class Terrain : public Component
{
public:
	EATER_ENGINEDLL Terrain();
	EATER_ENGINEDLL ~Terrain();

public:
	EATER_ENGINEDLL void AddLayer(std::string diffuseName, std::string normalName);

private:
	std::vector<Material*> m_MaterialLayer;
};

