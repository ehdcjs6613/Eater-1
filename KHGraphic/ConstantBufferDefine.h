#pragma once
#include "SimpleMath.h"
#include "LightHelper.h"
#include "HashBase.h"

#define ADD_CONSTANT_BUFFER(ClassName) static bool cbuffer_##ClassName = ShaderResourceHashTable::Get()->Push(eResourceType::CBUFFER, #ClassName, typeid(ClassName).hash_code());
#define CONSTANT_BUFFER(ClassName) CREATE_EMPTY_CLASS(ClassName) ADD_CONSTANT_BUFFER(ClassName)

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
// Forward Constant Buffer
///////////////////////////////////////////////////////////////////////////////////////////

CONSTANT_BUFFER(cbObject)
struct CB_Object : public cbObject
{
	DirectX::SimpleMath::Matrix gWorld;
	//DirectX::SimpleMath::Matrix gWorldInvTranspose;
	DirectX::SimpleMath::Matrix gWorldViewProj;
	DirectX::SimpleMath::Matrix gTexTransform;
	//DirectX::SimpleMath::Matrix gWorldView;
	//DirectX::SimpleMath::Matrix gWorldInvTransposeView;
};

CONSTANT_BUFFER(cbShadowObject)
struct CB_ShadowObject : public cbShadowObject
{
	DirectX::SimpleMath::Matrix gWorldViewProj;
};

CONSTANT_BUFFER(cbLights)
struct CB_Lights : public cbLights
{
	DirectionalLightData gDirLights[3];
	PointLightData gPointLights[5];
	SpotLightData gSpotLights[5];

	UINT gPointLightCount;
	UINT gSpotLightCount;
};

CONSTANT_BUFFER(cbMaterials)
struct CB_Materials : public cbMaterials
{
	MaterialData gMaterials[5];
};

CONSTANT_BUFFER(cbCamera)
struct CB_Camera : public cbCamera
{
	DirectX::SimpleMath::Vector3 gEyePosW;
};

CONSTANT_BUFFER(cbShadow)
struct CB_Shadow : public cbShadow
{
	DirectX::SimpleMath::Matrix gShadowTransform;
};

CONSTANT_BUFFER(cbSkinned)
struct CB_Skinned : public cbSkinned
{
	DirectX::SimpleMath::Matrix gBoneTransforms[96];
};

//CONSTANT_BUFFER(cbID)
//{
//	int gMatID = 0;
//};

///////////////////////////////////////////////////////////////////////////////////////////
// Deferred Constant Buffer
///////////////////////////////////////////////////////////////////////////////////////////

//CONSTANT_BUFFER(cbLightList)
//{
//	DirectionalLightData gDirLights[3];
//	PointLightData gPointLights[16];
//	SpotLightData gSpotLights[16];
//
//	UINT gPointLightCount;
//	UINT gSpotLightCount;
//};
//
//CONSTANT_BUFFER(cbMaterialList)
//{
//	MaterialData gMaterials[20];
//};
//
//CONSTANT_BUFFER(cbTexViewProj)
//{
//	DirectX::SimpleMath::Matrix gViewProjTex;
//};
//
/////////////////////////////////////////////////////////////////////////////////////////////
//// SSAO Constant Buffer
/////////////////////////////////////////////////////////////////////////////////////////////
//
//CONSTANT_BUFFER(cbTexel)
//{
//	float gTexelSize;
//};
//
//CONSTANT_BUFFER(cbSsaoFrame)
//{
//	DirectX::SimpleMath::Matrix  gViewToTexSpace;
//	DirectX::SimpleMath::Vector4 gOffsetVectors[14];
//	DirectX::SimpleMath::Vector4 gFrustumCorners[4];
//
//	float    gOcclusionRadius = 0.5f;
//	float    gOcclusionFadeStart = 0.2f;
//	float    gOcclusionFadeEnd = 2.0f;
//	float    gSurfaceEpsilon = 0.05f;
//};
//
/////////////////////////////////////////////////////////////////////////////////////////////
//// Full Screen Constant Buffer
/////////////////////////////////////////////////////////////////////////////////////////////
//
//CONSTANT_BUFFER(cbFullScreen)
//{
//	DirectX::SimpleMath::Matrix gNowViewProj;
//	DirectX::SimpleMath::Matrix gPrevViewProj;
//	float gDeltaTime;
//};
//
/////////////////////////////////////////////////////////////////////////////////////////////
//// UI Constant Buffer
/////////////////////////////////////////////////////////////////////////////////////////////
//
//CONSTANT_BUFFER(cbPerUI)
//{
//	DirectX::SimpleMath::Matrix gWorldViewProj;
//};
//
//CONSTANT_BUFFER(cbAlpha)
//{
//	float alpha = 0.0f;
//};



/// Resource Hash ���� ���� Define
RESOURCE_DEFINE(DEFINE_CBUFFER)