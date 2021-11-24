#pragma once
#include <unordered_map>

#define DEFINE_CBUFFER			0x00000001
#define DEFINE_SAMPLER			0x00000010
#define DEFINE_SRV				0x00000100
#define DEFINE_UAV				0x00001000

typedef unsigned int	Define_Mask;
typedef size_t			Hash_Code;

/// 
/// ConstantBufferHashTable Class
/// 
/// - ConstantBuffer Struct ���� Hash Code Ű������ �����ϱ� ���� Class
/// - Shader Reflect Load �� Description�� ���ϱ� ���� �ʿ��ϹǷ� Shader Load ���� �ʱ�ȭ �ʼ�
/// - �������� �ش� Resource Class ����� ���ÿ� Hash Table�� �ø�������� ������ ����� �������� �ʴ´�..
///   �ϴ� Initalize�κп� �������� �ش� Resource Class�� �÷�����..

enum class eResourceType
{
	CBUFFER,
	SAMPLER,
	SRV,
	UAV,
	DSV,
	DSS,
	RS,
	BS
};

class ShaderResourceHashTable
{
public:
	static ShaderResourceHashTable* Get();

	static ShaderResourceHashTable* instance;

public:
	// ConstantBuffer Hash Table..
	std::unordered_map<std::string, Hash_Code> g_CBuffer_HashTable;
	// Sampler Hash Table..
	std::unordered_map<std::string, Hash_Code> g_Sampler_HashTable;
	// ShaderResourceView Hash Table..
	std::unordered_map<std::string, Hash_Code> g_SRV_HashTable;
	// UnorderedAccessView Hash Table..
	std::unordered_map<std::string, Hash_Code> g_UAV_HashTable;

public:
	// Hash Code Push �Լ�..
	bool Push(eResourceType type, std::string name, Hash_Code hash_code);

	// �ش� Hash Code ��ȯ �Լ�..
	size_t FindHashCode(eResourceType type, std::string cBufName);

	bool DefineCheck(Define_Mask nowDefine);

	// Hash Table Reset �Լ�..
	void Destroy();

private:
	// Hash Code Push Check �Լ�..
	bool CheckHashCode(std::unordered_map<std::string, Hash_Code>& table, std::string name, Hash_Code hash_code);

	Define_Mask DEFINE_MASK = 0x00000000;
};

inline bool ShaderResourceHashTable::Push(eResourceType type, std::string name, Hash_Code hash_code)
{
	switch (type)
	{
	case eResourceType::CBUFFER:
	{
		if (DEFINE_MASK & DEFINE_CBUFFER)	
			return false;
		else
			return CheckHashCode(g_CBuffer_HashTable, name, hash_code);
	}
	case eResourceType::SAMPLER:
	{
		if (DEFINE_MASK & DEFINE_SAMPLER)
			return false;
		else
		return CheckHashCode(g_Sampler_HashTable, name, hash_code);
	}
	case eResourceType::SRV:
	{
		if (DEFINE_MASK & DEFINE_SRV)
			return false;
		else
			return CheckHashCode(g_SRV_HashTable, name, hash_code);
	}
	case eResourceType::UAV:
	{
		if (DEFINE_MASK & DEFINE_UAV)
			return false;
		else
			return CheckHashCode(g_UAV_HashTable, name, hash_code);
	}
	default:
		break;
	}

	return true;
}