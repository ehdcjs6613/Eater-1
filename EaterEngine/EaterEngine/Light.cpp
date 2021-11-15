#include "GameObject.h"
#include "Transform.h"
#include "Light.h"

DirectionLight::DirectionLight()
	:Light(eLightType::DIRECTION), m_DirLight(nullptr)
{

}

DirectionLight::~DirectionLight()
{

}

void DirectionLight::Awake()
{
	m_Transform = gameobject->GetTransform();
}

void DirectionLight::Update()
{

}

void DirectionLight::SetAmbient(float r, float g, float b, float a /*= 1.0f*/)
{
	m_DirLight->Ambient = { r, g, b, a };
}

void DirectionLight::SetDiffuse(float r, float g, float b, float a /*= 1.0f*/)
{
	m_DirLight->Diffuse = { r, g, b, a };
}

void DirectionLight::SetSpecular(float r, float g, float b, float a /*= 1.0f*/)
{
	m_DirLight->Specular = { r, g, b, a };
}

void DirectionLight::SetDirection(float x, float y, float z)
{
	m_DirLight->Direction = { x, y, z };
}

void DirectionLight::SetLight(DirectionalLightData& lightData)
{
	m_DirLight = &lightData;
}

SpotLight::SpotLight()
	:Light(eLightType::SPOT), m_SpotLight(nullptr)
{

}

SpotLight::~SpotLight()
{

}

void SpotLight::Awake()
{
	m_Transform = gameobject->GetTransform();
}

void SpotLight::Update()
{
	// 매 프레임 Light Position 연동..
	m_SpotLight->Position = m_Transform->Position;
}

void SpotLight::SetAmbient(float r, float g, float b, float a /*= 1.0f*/)
{
	m_SpotLight->Ambient = { r, g, b, a };
}

void SpotLight::SetDiffuse(float r, float g, float b, float a /*= 1.0f*/)
{
	m_SpotLight->Diffuse = { r, g, b, a };
}

void SpotLight::SetSpecular(float r, float g, float b, float a /*= 1.0f*/)
{
	m_SpotLight->Specular = { r, g, b, a };
}

void SpotLight::SetDirection(float x, float y, float z)
{
	m_SpotLight->Direction = { x, y, z };
}

void SpotLight::SetPosition(float x, float y, float z)
{
	// Position 변경..
	m_SpotLight->Position = { x, y, z };

	// Transform 연동..
	m_Transform->Position = m_SpotLight->Position;
}

void SpotLight::SetAtt(float x, float y, float z)
{
	m_SpotLight->Att = { x, y, z };
}

void SpotLight::SetRange(float range)
{
	m_SpotLight->Range = range;
}

void SpotLight::SetSpot(float spot)
{
	m_SpotLight->Spot = spot;
}

void SpotLight::SetLight(SpotLightData& lightData)
{
	m_SpotLight = &lightData;
}

PointLight::PointLight()
	:Light(eLightType::POINT), m_PointLight(nullptr)
{

}
PointLight::~PointLight()
{

}

void PointLight::Awake()
{
	m_Transform = gameobject->GetTransform();
}

void PointLight::Update()
{
	// 매 프레임 Light Position 연동..
	m_PointLight->Position = m_Transform->Position;
}

void PointLight::SetAmbient(float r, float g, float b, float a /*= 1.0f*/)
{
	m_PointLight->Ambient = { r, g, b, a };
}

void PointLight::SetDiffuse(float r, float g, float b, float a /*= 1.0f*/)
{
	m_PointLight->Diffuse = { r, g, b, a };
}

void PointLight::SetSpecular(float r, float g, float b, float a /*= 1.0f*/)
{
	m_PointLight->Specular = { r, g, b, a };
}

void PointLight::SetPosition(float x, float y, float z)
{
	// Position 변경..
	m_PointLight->Position = { x, y, z };

	// Transform 연동..
	m_Transform->Position = m_PointLight->Position;
}

void PointLight::SetAtt(float x, float y, float z)
{
	m_PointLight->Att = { x, y, z };
}

void PointLight::SetRange(float range)
{
	m_PointLight->Range = range;
}

void PointLight::SetLight(PointLightData& lightData)
{
	m_PointLight = &lightData;
}
