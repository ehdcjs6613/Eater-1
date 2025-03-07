#pragma once
#include "ClassType.h"

#define ADD_SHADER_RESOURCE_VIEW(ClassName) static bool srv_##ClassName = ShaderResourceHashTable::GetInstance()->Push<ClassName>(BufferType::SRV, #ClassName, ClassName::GetHashCode());
#define SHADER_RESOURCE_VIEW(ClassName) CREATE_EMPTY_CLASS(ClassName) ADD_SHADER_RESOURCE_VIEW(ClassName)

/// <summary>
/// ShaderResourceView Resource Struct
/// </summary>
/// 
/// - Shader 내부의 ShaderResourceView Resource와 1:1 대응하는 Struct
/// - Shader에서 설정한 레지스터 번호와 버퍼가 일치하는 한개의 ShaderResourceView
/// - D3DCompiler에서 현재 Shader에서 ShaderResourceView을 선언해 두어도 사용하지 않으면
///   Register Slot에 올리지 않는다..
/// 
/// - 주의점
///  1) 현재 struct의 이름과 변수 순서는 Shader 내부의 UnorderedAccessView와 일치해야한다 (Struct Name을 통해 UnorderedAccessView를 찾기 때문)

///////////////////////////////////////////////////////////////////////////////////////////
// Global ShaderResourceView Resource
///////////////////////////////////////////////////////////////////////////////////////////

SHADER_RESOURCE_VIEW(gDiffuseMap)
SHADER_RESOURCE_VIEW(gNormalMap)
SHADER_RESOURCE_VIEW(gCubeMap)
SHADER_RESOURCE_VIEW(gShadowMap)
SHADER_RESOURCE_VIEW(gSSAOMap)

///////////////////////////////////////////////////////////////////////////////////////////
// SSAO ShaderResourceView Resource
///////////////////////////////////////////////////////////////////////////////////////////

SHADER_RESOURCE_VIEW(gNormalDepthMap)
SHADER_RESOURCE_VIEW(gRandomVecMap)
SHADER_RESOURCE_VIEW(gInputMap)

///////////////////////////////////////////////////////////////////////////////////////////
// Deferred ShaderResourceView Resource
///////////////////////////////////////////////////////////////////////////////////////////

SHADER_RESOURCE_VIEW(AlbedoSRV)
SHADER_RESOURCE_VIEW(NormalSRV)
SHADER_RESOURCE_VIEW(PositionSRV)
SHADER_RESOURCE_VIEW(ShadowSRV)
SHADER_RESOURCE_VIEW(SsaoSRV)

///////////////////////////////////////////////////////////////////////////////////////////
// Blur ShaderResourceView Resource
///////////////////////////////////////////////////////////////////////////////////////////

SHADER_RESOURCE_VIEW(gInput)

///////////////////////////////////////////////////////////////////////////////////////////
// MotionBlur ShaderResourceView Resource
///////////////////////////////////////////////////////////////////////////////////////////

SHADER_RESOURCE_VIEW(gDepthMap)
SHADER_RESOURCE_VIEW(gOrigin)
SHADER_RESOURCE_VIEW(gVelocity)
