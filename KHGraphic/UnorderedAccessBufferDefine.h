#pragma once
#include "ClassType.h"

#define ADD_UNORDERED_ACCESS_VIEW(ClassName) static bool uav_##ClassName = ShaderResourceHashTable::GetInstance()->Push<ClassName>(BufferType::UAV, #ClassName, ClassName::GetHashCode());
#define UNORDERED_ACCESS_VIEW(ClassName) CREATE_EMPTY_CLASS(ClassName) ADD_UNORDERED_ACCESS_VIEW(ClassName)

/// <summary>
/// UnorderedAccessView Resource Struct
/// </summary>
/// 
/// - Shader 내부의 UnorderedAccessView Resource와 1:1 대응하는 Struct
/// - Shader에서 설정한 레지스터 번호와 버퍼가 일치하는 한개의 UnorderedAccessView
/// - D3DCompiler에서 현재 Shader에서 UnorderedAccessView을 선언해 두어도 사용하지 않으면
///   Register Slot에 올리지 않는다..
/// 
/// - 주의점
///  1) 현재 struct의 이름과 변수 순서는 Shader 내부의 UnorderedAccessView와 일치해야한다 (Struct Name을 통해 UnorderedAccessView를 찾기 때문)

///////////////////////////////////////////////////////////////////////////////////////////
// Blur UnorderedAccessView Resource
///////////////////////////////////////////////////////////////////////////////////////////

UNORDERED_ACCESS_VIEW(gOutput)
