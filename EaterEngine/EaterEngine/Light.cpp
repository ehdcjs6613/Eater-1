#include "GameObject.h"
#include "Transform.h"
#include "LightManager.h"
#include "Light.h"

using namespace DirectX::SimpleMath;

LightManager* Light::g_LightManager = nullptr;

Light::Light(eLightType lightType)
	:m_LightType(lightType), m_Transform(nullptr)
{
}

void Light::SetManager(LightManager* light)
{
	g_LightManager = light;
}

void Light::Reset()
{
	g_LightManager = nullptr;
}

DirectionLight::DirectionLight()
	:Light(eLightType::DIRECTION)
{
	m_DirLight = new DirectionalLightData();

	// DirectionLight 기본값..
	m_DirLight->Ambient = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_DirLight->Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_DirLight->Specular = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	m_DirLight->Direction = Vector3(-0.57735f, -0.57735f, 0.57735f);

	// Light Object 등록..
	g_LightManager->AddLight(this);
}

DirectionLight::~DirectionLight()
{
	delete m_DirLight;
}

void DirectionLight::Awake()
{
	m_Transform = gameobject->GetTransform();
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

DirectionalLightData* DirectionLight::GetLightData()
{
	return m_DirLight;
}

SpotLight::SpotLight()
	:Light(eLightType::SPOT)
{
	m_SpotLight = new SpotLightData();

	// SpotLight 기본값..
	m_SpotLight->Ambient = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
	m_SpotLight->Diffuse = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
	m_SpotLight->Specular = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_SpotLight->Direction = Vector3(0.0f, -1.0f, 0.0f);
	m_SpotLight->Att = Vector3(0.9f, 0.9f, 0.0f);
	m_SpotLight->Range = 10000.0f;
	m_SpotLight->Spot = 96.0f;

	// Light Object 등록..
	g_LightManager->AddLight(this);
}

SpotLight::~SpotLight()
{
	delete m_SpotLight;
}

void SpotLight::Awake()
{
	m_Transform = gameobject->GetTransform();

	// Transform Position 연동..
	m_SpotLight->Position = m_Transform->Position;
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

SpotLightData* SpotLight::GetLightData()
{
	return m_SpotLight;
}

PointLight::PointLight()
	:Light(eLightType::POINT)
{
	m_PointLight = new PointLightData();

	// PointLight 기본값..
	m_PointLight->Ambient = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
	m_PointLight->Diffuse = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
	m_PointLight->Specular = Vector4(0.7f, 0.7f, 0.7f, 1.0f);
	m_PointLight->Att = Vector3(0.0f, 0.2f, 0.0f);
	m_PointLight->Range = 1000.0f;
	m_PointLight->Pad = 1.0f;

	// Light Object 등록..
	g_LightManager->AddLight(this);
}

PointLight::~PointLight()
{
	delete m_PointLight;
}

void PointLight::Awake()
{
	m_Transform = gameobject->GetTransform();

	// Transform Position 연동..
	m_PointLight->Position = m_Transform->Position;
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

PointLightData* PointLight::GetLightData()
{
	return m_PointLight;
}
