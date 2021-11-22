#pragma once
#include <unordered_map>
#include "SingleTon.h"

typedef size_t Hash_Code;

/// 
/// ConstantBufferHashTable Class
/// 
/// - ConstantBuffer Struct ���� Hash Code Ű������ �����ϱ� ���� Class
/// - Shader Reflect Load �� Description�� ���ϱ� ���� �ʿ��ϹǷ� Shader Load ���� �ʱ�ȭ �ʼ�
/// - �������� �ش� Resource Class ����� ���ÿ� Hash Table�� �ø�������� ������ ����� �������� �ʴ´�..
///   �ϴ� Initalize�κп� �������� �ش� Resource Class�� �÷�����..

class ShaderResourceHashTable : public Singleton<ShaderResourceHashTable>
{
public:
	enum class BufferType
	{
		CBUFFER,
		SAMPLER,
		SRV,
		UAV
	};

public:
	// ConstantBuffer Hash Table..
	std::unordered_map<std::string, Hash_Code> g_CBuffer_HashTable;
	// Sampler Hash Table..
	std::unordered_map<std::string, Hash_Code> g_Sampler_HashTable;
	// ShaderResourceView Hash Table..
	std::unordered_map<std::string, Hash_Code> g_SRV_HashTable;
	// UnorderedAccessView Hash Table..
	std::unordered_map<std::string, Hash_Code> g_UAV_HashTable;

	// Hash Table Reset �Լ�..
	void Reset();

	// Hash Code Push �Լ�..
	template<typename T> bool Push(BufferType type, std::string name, Hash_Code hash_code);

	// �ش� Hash Code ��ȯ �Լ�..
	size_t FindHashCode(BufferType type, std::string cBufName);

private:
	// Hash Code Push Check �Լ�..
	bool CheckHashCode(std::unordered_map<std::string, Hash_Code>& table, std::string name, Hash_Code hash_code);
};

template<typename T>
bool ShaderResourceHashTable::Push(BufferType type, std::string name, Hash_Code hash_code)
{
	switch (type)
	{
	case ShaderResourceHashTable::BufferType::CBUFFER:
		return CheckHashCode(g_CBuffer_HashTable, name, hash_code);
	case ShaderResourceHashTable::BufferType::SAMPLER:
		return CheckHashCode(g_Sampler_HashTable, name, hash_code);
	case ShaderResourceHashTable::BufferType::SRV:
		return CheckHashCode(g_SRV_HashTable, name, hash_code);
	case ShaderResourceHashTable::BufferType::UAV:
		return CheckHashCode(g_UAV_HashTable, name, hash_code);
	default:
		break;
	}

	return false;
}