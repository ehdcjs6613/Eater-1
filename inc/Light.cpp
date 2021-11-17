#include "GameObject.h"
#include "Transform.h"
#include "LightManager.h"
#include "Light.h"

using namespace DirectX;
using namespace SimpleMath;

LightManager* Light::g_LightManager = nullptr;
DirectionLight* DirectionLight::g_DirLight = nullptr;

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

	// DirectionLight �⺻��..
	m_DirLight->Ambient = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_DirLight->Diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_DirLight->Specular = Vector4(0.8f, 0.8f, 0.8f, 1.0f);
	m_DirLight->Direction = Vector3(-0.57735f, -0.57735f, 0.57735f);

	m_CenterPos = Vector3(0, 0, 0);
	m_ShadowRadius = sqrtf(10.0f * 10.0f + 15.0f * 15.0f);

	// Light Direction �� ������ View Proj �缳��..
	SetLightViewProj();

	// Main Directional Light ����..
	if (g_DirLight == nullptr)
		g_DirLight = this;

	// Light Object ���..
	g_LightManager->AddLight(this);
}

DirectionLight::~DirectionLight()
{
	delete m_DirLight;
}

void DirectionLight::SetLightViewProj()
{
	static XMMATRIX g_TexSpace = Matrix(0.5f, 0.0f, 0.0f, 0.0f,
										0.0f, -0.5f, 0.0f, 0.0f,
										0.0f, 0.0f, 1.0f, 0.0f,
										0.5f, 0.5f, 0.0f, 1.0f);

	/// Light Direction �� ������ ���� �������־�� ��..
	// Light View, Proj ����..
	Vector3 lightPos = m_DirLight->Direction * -2.0f * m_ShadowRadius;

	// Ligh View
	m_LightView = XMMatrixLookAtLH(lightPos, m_CenterPos, Vector4(0.0f, 1.0f, 0.0f, 0.0f));

	Vector3 lightSpace = XMVector3TransformCoord(m_CenterPos, m_LightView);

	// ����� ���δ� ���� ���� ���� ���� ����..
	float l = lightSpace.x - m_ShadowRadius;
	float b = lightSpace.y - m_ShadowRadius;
	float n = lightSpace.z - m_ShadowRadius;
	float r = lightSpace.x + m_ShadowRadius;
	float t = lightSpace.y + m_ShadowRadius;
	float f = lightSpace.z + m_ShadowRadius;

	// Light Proj
	m_LightProj = XMMatrixOrthographicOffCenterLH(l, r, b, t, n, f);

	// Shadow Transpose
	m_ShadowTrans = m_LightView * m_LightProj * g_TexSpace;
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

	// Light Direction �� ������ View Proj �缳��..
	SetLightViewProj();
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

	// SpotLight �⺻��..
	m_SpotLight->Ambient = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
	m_SpotLight->Diffuse = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
	m_SpotLight->Specular = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	m_SpotLight->Direction = Vector3(0.0f, -1.0f, 0.0f);
	m_SpotLight->Att = Vector3(0.9f, 0.9f, 0.0f);
	m_SpotLight->Range = 10000.0f;
	m_SpotLight->Spot = 96.0f;

	// Light Object ���..
	g_LightManager->AddLight(this);
}

SpotLight::~SpotLight()
{
	delete m_SpotLight;
}

void SpotLight::Awake()
{
	m_Transform = gameobject->GetTransform();

	// Transform Position ����..
	m_SpotLight->Position = m_Transform->Position;
}

void SpotLight::Update()
{
	// �� ������ Light Position ����..
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
	// Position ����..
	m_SpotLight->Position = { x, y, z };

	// Transform ����..
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

	// PointLight �⺻��..
	m_PointLight->Ambient = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
	m_PointLight->Diffuse = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
	m_PointLight->Specular = Vector4(0.7f, 0.7f, 0.7f, 1.0f);
	m_PointLight->Att = Vector3(0.0f, 0.2f, 0.0f);
	m_PointLight->Range = 1000.0f;
	m_PointLight->Pad = 1.0f;

	// Light Object ���..
	g_LightManager->AddLight(this);
}

PointLight::~PointLight()
{
	delete m_PointLight;
}

void PointLight::Awake()
{
	m_Transform = gameobject->GetTransform();

	// Transform Position ����..
	m_PointLight->Position = m_Transform->Position;
}

void PointLight::Update()
{
	// �� ������ Light Position ����..
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
	// Position ����..
	m_PointLight->Position = { x, y, z };

	// Transform ����..
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
