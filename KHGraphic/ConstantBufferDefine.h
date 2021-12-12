#pragma once
#include "SimpleMath.h"
#include "LightHelper.h"
#include "HashBase.h"

#define CONSTANT_BUFFER(ClassName) CREATE_HASH_CLASS(ClassName, eResourceType::CB) RESOURCE_PUSH(ClassName, eResourceType::CB)

/// <summary>
/// ConstantBuffer Resource Struct
/// </summary>
/// 
/// - Shader ������ ConstantBuffer Resource�� 1:1 �����ϴ� Struct
/// - Shader���� ������ �������� ��ȣ�� ���۰� ��ġ�ϴ� �Ѱ��� Constant Buffer
/// - D3DCompiler���� ���� Shader���� ConstantBuffer�� ������ �ξ ������� ������
///   Register Slot�� �ø��� �ʴ´�..
/// 
/// - ������
///  1) ���� struct�� �̸��� ���� ������ Shader ������ ConstantBuffer�� ��ġ�ؾ��Ѵ� (Struct Name�� ���� Constant Buffer�� ã�� ����)

///////////////////////////////////////////////////////////////////////////////////////////
// Deferred Constant Buffer
///////////////////////////////////////////////////////////////////////////////////////////

CONSTANT_BUFFER(cbMeshObject)
struct CB_MeshObject : public cbMeshObject
{
	DirectX::SimpleMath::Matrix gWorld;
	DirectX::SimpleMath::Matrix gWorldView;
	DirectX::SimpleMath::Matrix gWorldViewProj;
	DirectX::SimpleMath::Matrix gTexTransform;
	DirectX::SimpleMath::Matrix gShadowTransform;
};

CONSTANT_BUFFER(cbShadowMeshObject)
struct CB_ShadowMeshObject : public cbShadowMeshObject
{
	DirectX::SimpleMath::Matrix gWorldViewProj;
};

CONSTANT_BUFFER(cbSkinObject)
struct CB_SkinObject : public cbSkinObject
{
	DirectX::SimpleMath::Matrix gWorld;
	DirectX::SimpleMath::Matrix gWorldView;
	DirectX::SimpleMath::Matrix gWorldViewProj;
	DirectX::SimpleMath::Matrix gTexTransform;
	DirectX::SimpleMath::Matrix gShadowTransform;
	DirectX::SimpleMath::Matrix gBoneTransforms[96];
};

CONSTANT_BUFFER(cbShadowSkinObject)
struct CB_ShadowSkinObject : public cbShadowSkinObject
{
	DirectX::SimpleMath::Matrix gWorldViewProj;
	DirectX::SimpleMath::Matrix gBoneTransforms[96];
};

CONSTANT_BUFFER(cbLightSub)
struct CB_LightSub : public cbLightSub
{
	DirectX::SimpleMath::Matrix gViewProjTex;
	DirectX::SimpleMath::Vector3 gEyePosW;
};

CONSTANT_BUFFER(cbLight)
struct CB_Light : public cbLight
{
	DirectionalLightData gDirLights;
	PointLightData gPointLights[5];
	SpotLightData gSpotLights[5];
	MaterialData gMaterials[5];

	UINT gPointLightCount;
	UINT gSpotLightCount;
};

CONSTANT_BUFFER(cbMaterial)
struct CB_Material : public cbMaterial
{
	DirectX::SimpleMath::Vector4 gColor = DirectX::SimpleMath::Vector4(0.5f, 0.5f, 0.5f, 1.0f);
	
	UINT gMatID = 0;
	UINT gTexID = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////////
//// SSAO Constant Buffer
/////////////////////////////////////////////////////////////////////////////////////////////

CONSTANT_BUFFER(cbBlurOption)
struct CB_BlurOption : public cbBlurOption
{
	DirectX::SimpleMath::Vector2 gTexelSize;
	bool gHorizon;
};

CONSTANT_BUFFER(cbSsaoObject)
struct CB_SsaoObject : public cbSsaoObject
{
	DirectX::SimpleMath::Matrix  gViewToTexSpace;
};

CONSTANT_BUFFER(cbSsaoFrustum)
struct CB_SsaoFrustum : public cbSsaoFrustum
{
	DirectX::SimpleMath::Vector4 gFrustumCorners[4];
};

CONSTANT_BUFFER(cbSsaoOption)
struct CB_SsaoOption : public cbSsaoOption
{
	DirectX::SimpleMath::Vector4 gOffsetVectors[14];

	float    gOcclusionRadius = 0.5f;
	float    gOcclusionFadeStart = 0.2f;
	float    gOcclusionFadeEnd = 2.0f;
	float    gSurfaceEpsilon = 0.05f;
};

/// Resource Hash ���� ���� Define
RESOURCE_DEFINE(DEFINE_CB)