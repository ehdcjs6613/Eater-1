#include "LightManager.h"
#include "EngineData.h"

LightManager::LightManager()
	:m_DirectionCount(0), m_PointCount(0), m_SpotCount(0)
{

}

LightManager::~LightManager()
{

}

void LightManager::Initialize()
{
	m_LightData = new LightData();

	Global->mLightData = m_LightData;
}

void LightManager::AddLight(Light* light)
{
	// Light Type에 따른 Global Data 삽입..
	switch (light->GetType())
	{
	case eLightType::DIRECTION:
	{
		DirectionLight* dirLight = reinterpret_cast<DirectionLight*>(light);
		m_LightData->DirLights.push_back(dirLight->GetLightData());
		m_LightData->gDirLightCount = ++m_DirectionCount;
	}
	break;
	case eLightType::SPOT:
	{
		SpotLight* spotLight = reinterpret_cast<SpotLight*>(light);
		m_LightData->SpotLights.push_back(spotLight->GetLightData());
		m_LightData->gSpotLightCount = ++m_SpotCount;
	}
	break;
	case eLightType::POINT:
	{
		PointLight* pointLight = reinterpret_cast<PointLight*>(light);
		m_LightData->PointLights.push_back(pointLight->GetLightData());
		m_LightData->gPointLightCount = ++m_PointCount;
	}
	break;
	default:
		break;
	}

	// 새로운 Light 추가..
	m_LightList.push_back(light);
}
