//***************************************************************************************
// Effects.cpp by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************
#include <Windows.h>
#include <windef.h>
#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include <string.h>
#include <vector>
#include <fstream>
#include "DirectXDefine.h"
#include "Effects.h"

#pragma region Effect
Effect::Effect(ID3D11Device* device, const std::wstring& filename)
	: m_FX(0)
{
	std::ifstream fin(filename, std::ios::binary);

	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();
	
	HR(D3DX11CreateEffectFromMemory(&compiledShader[0], size, 
		0, device, &m_FX));
}

Effect::~Effect()
{
	ReleaseCOM(m_FX);
}
#pragma endregion

#pragma region BasicEffect
BasicEffect::BasicEffect(ID3D11Device* device, const std::wstring& filename)
	: Effect(device, filename)
{
	Light1Tech = m_FX->GetTechniqueByName("Light1");
	Light2Tech = m_FX->GetTechniqueByName("Light2");
	Light3Tech = m_FX->GetTechniqueByName("Light3");

	Light0TexTech =		m_FX->GetTechniqueByName("Light0Tex");
	Light1TexTech =		m_FX->GetTechniqueByName("Light1Tex");
	Light2TexTech =		m_FX->GetTechniqueByName("Light2Tex");
	Light3TexTech =		m_FX->GetTechniqueByName("Light3Tex");

	WorldViewProj =		m_FX->GetVariableByName("gWorldViewProj")->AsMatrix();
	World =				m_FX->GetVariableByName("gWorld")->AsMatrix();
	WorldInvTranspose = m_FX->GetVariableByName("gWorldInvTranspose")->AsMatrix();
	TexTransform =		m_FX->GetVariableByName("gTexTransform")->AsMatrix();
	EyePosW =			m_FX->GetVariableByName("gEyePosW")->AsVector();
	DirLights =			m_FX->GetVariableByName("gDirLights");
	Mat =				m_FX->GetVariableByName("gMaterial");
	DiffuseMap =		m_FX->GetVariableByName("gDiffuseMap")->AsShaderResource();
}

BasicEffect::~BasicEffect()
{
}
#pragma endregion

#pragma region Effects

BasicEffect* Effects::BasicFX = nullptr;
BasicEffect* Effects::BasicTextureFX = nullptr;

void Effects::InitAll(ID3D11Device* device)
{
#ifdef _DEBUG
	BasicFX = new BasicEffect(device, L"../x64/Debug/Basic.cso");
	BasicTextureFX = new BasicEffect(device, L"../x64/Debug/BasicTexture.cso");
#else
	BasicFX = new BasicEffect(device, L"../x64/Release/Basic.cso");
	BasicTextureFX = new BasicEffect(device, L"../x64/Release/BasicTexture.cso");
#endif // DEBUG

}

void Effects::DestroyAll()
{

	SafeDelete(BasicFX);
	SafeDelete(BasicTextureFX);
}
#pragma endregion