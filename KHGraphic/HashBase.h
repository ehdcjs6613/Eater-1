#pragma once
#include <string>
#include <typeinfo>
#include "ResourceBufferHashTable.h"

#define CREATE_EMPTY_CLASS(ClassName) struct ClassName : public HashClass<ClassName> {};
#define RESOURCE_DEFINE(ResourceMask) static bool check_##ResourceMask = ShaderResourceHashTable::Get()->DefineCheck((int)ResourceMask);

/// <summary>
/// BufferName Struct
/// </summary>
/// 
/// - ��� Shader Resource�� ����� �Ǵ� Base Class
/// - Shader Reflection�� ���� Resource�� �̸��� ���ؾ� �ϱ� ������ Struct �̸��� �������� �Լ� ����
///

template <typename T>
struct HashClass
{
	static std::string GetName()
	{
		std::string name = typeid(T).name();
		size_t spacePosition = name.find_first_of(" ");
		if (spacePosition != std::string::npos)
			return name.substr(spacePosition + 1, name.length());
		else
			return name;
	}
	
	static size_t GetHashCode()
	{
		return typeid(T).hash_code();
	}
};