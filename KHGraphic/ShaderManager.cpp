#include "DirectDefine.h"
#include "D3D11Graphic.h"
#include "ShaderBase.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ComputeShader.h"
#include "ShaderManagerBase.h"
#include "ShaderManager.h"
#include "ShaderResourceHashTable.h"

using namespace Microsoft::WRL;

ShaderManager::ShaderManager(D3D11Graphic* graphic)
{
	// Shader Global Initialize..
	IShader::Initialize(graphic->GetDevice(), graphic->GetContext());
}

ShaderManager::~ShaderManager()
{

}

void ShaderManager::Initialize()
{
	// Shader File Route Setting..
	IShader::SetShaderRoute("../Resources/Shader/SKH/");

	// Global Shader Create..
	CreateShader();
}

void ShaderManager::Release()
{
	IShader::Reset();

	for (std::pair<std::string, ShaderBase*> shader : m_ShaderList)
	{
		RELEASE_COM(shader.second);
	}

	m_ShaderList.clear();
}

VertexShader* ShaderManager::GetVertexShader(std::string shaderName)
{
	std::unordered_map<std::string, ShaderBase*>::iterator shader = m_ShaderList.find(shaderName);

	// �ش� Shader�� ���� ���..
	if (shader == m_ShaderList.end()) return nullptr;

	switch (shader->second->GetType())
	{
	case eShaderType::VERTEX:
		return reinterpret_cast<VertexShader*>(shader->second);
	default:
		return nullptr;
	}
}

PixelShader* ShaderManager::GetPixelShader(std::string shaderName)
{
	std::unordered_map<std::string, ShaderBase*>::iterator shader = m_ShaderList.find(shaderName);

	// �ش� Shader�� ���� ���..
	if (shader == m_ShaderList.end()) return nullptr;

	switch (shader->second->GetType())
	{
	case eShaderType::PIXEL:
		return reinterpret_cast<PixelShader*>(shader->second);
	default:
		return nullptr;
	}
}

ComputeShader* ShaderManager::GetComputeShader(std::string shaderName)
{
	std::unordered_map<std::string, ShaderBase*>::iterator shader = m_ShaderList.find(shaderName);

	// �ش� Shader�� ���� ���..
	if (shader == m_ShaderList.end()) return nullptr;

	switch (shader->second->GetType())
	{
	case eShaderType::COMPUTE:
		return reinterpret_cast<ComputeShader*>(shader->second);
	default:
		return nullptr;
	}
}

void ShaderManager::CreateShader()
{
	// Object Shader
	LoadShader(eShaderType::VERTEX, "MeshVS.cso");
	LoadShader(eShaderType::VERTEX, "SkinVS.cso");

	// Forward Shader
	LoadShader(eShaderType::PIXEL, "ForwardPS.cso");

	// Deffered Shader
	LoadShader(eShaderType::PIXEL, "DeferredPS.cso");

	// Light Shader
	LoadShader(eShaderType::VERTEX, "LightVS.cso");
	LoadShader(eShaderType::PIXEL, "LightPS.cso");

	// Shadow Shader
	LoadShader(eShaderType::VERTEX, "ShadowMeshVS.cso");
	LoadShader(eShaderType::VERTEX, "ShadowSkinVS.cso");
}

void ShaderManager::AddSampler(Hash_Code hash_code, ID3D11SamplerState** sampler)
{
	for (std::pair<std::string, ShaderBase*> shader : m_ShaderList)
	{
		ShaderBase* pShader = shader.second;

		switch (pShader->GetType())
		{
		case eShaderType::VERTEX:
		case eShaderType::PIXEL:
		case eShaderType::COMPUTE:
		{
			pShader->SetSamplerState(hash_code, sampler);
		}
		break;
		default:
			break;
		}
	}
}

ShaderBase* ShaderManager::LoadShader(eShaderType shaderType, std::string shaderName)
{
	// Shader Type�� �´� Shader ����..
	ShaderBase* newShader = nullptr;

	switch (shaderType)
	{
	case eShaderType::VERTEX:
		newShader = new VertexShader(shaderName.c_str());
		break;
	case eShaderType::PIXEL:
		newShader = new PixelShader(shaderName.c_str());
		break;
	case eShaderType::COMPUTE:
		newShader = new ComputeShader(shaderName.c_str());
		break;
	default:
		throw std::exception("ERROR: None Shader Type.\n");
		return nullptr;
	}

	// ������ ����� ���� ���Ͽ� �������� ���Ѱ�� nullptr..
	if (newShader == nullptr)
		return nullptr;

	std::string shaderKey(shaderName);
	size_t pointPosition = shaderName.rfind(".");

	// Shader File Name ���� Key ����..
	if (pointPosition != std::string::npos)
		shaderKey = shaderName.substr(0, pointPosition);

	// ���� ������ Shader ����..
	m_ShaderList.insert(std::make_pair(shaderKey, newShader));

	return newShader;
}

OriginalShader ShaderManager::GetShader(std::string shaderName)
{
	return OriginalShader{ this, shaderName };
}