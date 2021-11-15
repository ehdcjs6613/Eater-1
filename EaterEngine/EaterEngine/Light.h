#pragma once
#include "Component.h"
#include "EaterEngineDLL.h"
#include "LightHelper.h"

enum class eLightType
{
	DIRECTION,
	SPOT,
	POINT
};

/// <summary>
/// Light Base Class
/// </summary>

class Transform;

class Light : public Component
{
public:
	Light(eLightType lightType) : m_LightType(lightType), m_Transform(nullptr) {}
	virtual ~Light() = default;

public:
	eLightType GetType() { return m_LightType; }

protected:
	Transform* m_Transform;

	eLightType m_LightType;
};

/// <summary>
/// DirectionLight Class
/// </summary>

class DirectionLight : public Light
{
public:
	DirectionLight();
	~DirectionLight();

public:
	void Awake() override;
	void Update() override;

public:
	void SetAmbient(float r, float g, float b, float a = 1.0f);
	void SetDiffuse(float r, float g, float b, float a = 1.0f);
	void SetSpecular(float r, float g, float b, float a = 1.0f);
	void SetDirection(float x, float y, float z);

public:
	void SetLight(DirectionalLightData& lightData);

private:
	DirectionalLightData* m_DirLight;
};

/// <summary>
/// SpotLight Class
/// </summary>

class SpotLight : public Light
{
public:
	SpotLight();
	~SpotLight();

public:
	void Awake() override;
	void Update() override;

public:
	void SetAmbient(float r, float g, float b, float a = 1.0f);
	void SetDiffuse(float r, float g, float b, float a = 1.0f);
	void SetSpecular(float r, float g, float b, float a = 1.0f);
	void SetDirection(float x, float y, float z);

	void SetPosition(float x, float y, float z);
	void SetAtt(float x, float y, float z);

	void SetRange(float range);
	void SetSpot(float spot);

public:
	void SetLight(SpotLightData& lightData);

private:
	SpotLightData* m_SpotLight;
};

/// <summary>
/// PointLight Class
/// </summary>

class PointLight : public Light
{
public:
	PointLight();
	~PointLight();

public:
	void Awake() override;
	void Update() override;

public:
	void SetAmbient(float r, float g, float b, float a = 1.0f);
	void SetDiffuse(float r, float g, float b, float a = 1.0f);
	void SetSpecular(float r, float g, float b, float a = 1.0f);

	void SetPosition(float x, float y, float z);
	void SetAtt(float x, float y, float z);

	void SetRange(float range);
	
public:
	void SetLight(PointLightData& lightData);

private:
	PointLightData* m_PointLight;
};