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
	
	// Light ���� Global Data ���..
	Global->mLightData = m_LightData;
	Global->mLightViewMX = DirectionLight::g_DirLight->GetView();
	Global->mLightProj = DirectionLight::g_DirLight->GetProj();
	Global->mShadowTrans = DirectionLight::g_DirLight->GetShadowTranspose();
}

void LightManager::AddLight(Light* light)
{
	// Light Type�� ���� Global Data ����..
	switch (light->GetType())
	{
	case eLightType::DIRECTION:
	{
		DirectionLight* dirLight = reinterpret_cast<DirectionLight*>(light);
		m_LightData->DirLights[m_DirectionCount++] = dirLight->GetLightData();
	}
	break;
	case eLightType::SPOT:
	{
		SpotLight* spotLight = reinterpret_cast<SpotLight*>(light);
		m_LightData->SpotLights[m_SpotCount++] = spotLight->GetLightData();
	}
	break;
	case eLightType::POINT:
	{
		PointLight* pointLight = reinterpret_cast<PointLight*>(light);
		m_LightData->PointLights[m_PointCount++] = pointLight->GetLightData();
	}
	break;
	default:
		break;
	}

	// ���ο� Light �߰�..
	m_LightList.push_back(light);
}
