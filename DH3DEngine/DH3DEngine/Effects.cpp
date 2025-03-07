//***************************************************************************************
// Effects.cpp by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#include "Effects.h"
#include <vector>

#pragma region Effect
Effect::Effect(ID3D11Device* device, const std::wstring& filename)
	: mFX(0)
{
	std::ifstream fin(filename, std::ios::binary);

	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();
	
	HR(D3DX11CreateEffectFromMemory(&compiledShader[0], size, 
		0, device, &mFX));
}

Effect::~Effect()
{
	ReleaseCOM(mFX);
}
#pragma endregion

#pragma region BasicEffect
BasicEffect::BasicEffect(ID3D11Device* device, const std::wstring& filename)
	: Effect(device, filename)
{
	Light1Tech        = mFX->GetTechniqueByName("Light1");
	Light2Tech        = mFX->GetTechniqueByName("Light2");
	Light3Tech        = mFX->GetTechniqueByName("Light3");
	WorldViewProj     = mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
	World             = mFX->GetVariableByName("gWorld")->AsMatrix();
	WorldInvTranspose = mFX->GetVariableByName("gWorldInvTranspose")->AsMatrix();
	EyePosW           = mFX->GetVariableByName("gEyePosW")->AsVector();
	DirLights         = mFX->GetVariableByName("gDirLights");
	Mat               = mFX->GetVariableByName("gMaterial");
	DiffuseMap = mFX->GetVariableByName("gDiffuseMap")->AsShaderResource();
	TexTransform = mFX->GetVariableByName("gTexTransform")->AsMatrix();
}

BasicEffect::~BasicEffect()
{
}
#pragma endregion

//#pragma region SkyEffect
//SkyEffect::SkyEffect(ID3D11Device* device, const std::wstring& filename)
//	: Effect(device, filename)
//{
//	SkyTech = mFX->GetTechniqueByName("SkyTech");
//	WorldViewProj = mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
//	CubeMap = mFX->GetVariableByName("gCubeMap")->AsShaderResource();
//}
//
//SkyEffect::~SkyEffect()
//{
//}
//#pragma endregion

#pragma region Effects

BasicEffect* Effects::BasicFX = 0;
//SkyEffect* Effects::SkyFx = 0;

void Effects::InitAll(ID3D11Device* device)
{
	BasicFX = new BasicEffect(device, L"../Resources/Shader/CDH/Basic.cso");
	//SkyFx = new SkyEffect(device, L"../FX/Sky.cso");
}

void Effects::DestroyAll()
{
	SafeDelete(BasicFX);
	//SafeDelete(SkyFx);
}
#pragma endregion