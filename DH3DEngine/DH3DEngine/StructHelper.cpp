#include "StructHelper.h"

#pragma region InputLayoutDesc

const D3D11_INPUT_ELEMENT_DESC InputLayoutDesc::Pos[1] =
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

const D3D11_INPUT_ELEMENT_DESC InputLayoutDesc::PosNormal[2] =
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"NORMAL",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

const D3D11_INPUT_ELEMENT_DESC InputLayoutDesc::PosNormalTexBiNormalTangent[4] =
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"NORMAL",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TANGENT",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},
};

#pragma endregion

#pragma region InputLayouts

ID3D11InputLayout* InputLayouts::Pos = 0;
ID3D11InputLayout* InputLayouts::PosNormal = 0;
ID3D11InputLayout* InputLayouts::PosNormalTexBiNormalTangent = 0;

void InputLayouts::InitAll(ID3D11Device* device)
{

	D3DX11_PASS_DESC passDesc;
	Effects::BasicFX->Light1Tech->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(device->CreateInputLayout(InputLayoutDesc::PosNormalTexBiNormalTangent, 4, passDesc.pIAInputSignature,
		passDesc.IAInputSignatureSize, &PosNormalTexBiNormalTangent));

	//Effects::BasicFX->Light1Tech->GetPassByIndex(0)->GetDesc(&passDesc);
	//HR(device->CreateInputLayout(InputLayoutDesc::PosNormal, 2, passDesc.pIAInputSignature,
	//	passDesc.IAInputSignatureSize, &PosNormal));

	//Effects::SkyFx->SkyTech->GetPassByIndex(0)->GetDesc(&passDesc);
	//HR(device->CreateInputLayout(InputLayoutDesc::Pos, 1, passDesc.pIAInputSignature,
	//	passDesc.IAInputSignatureSize, &Pos));
}

void InputLayouts::DestroyAll()
{
	ReleaseCOM(Pos);
	ReleaseCOM(PosNormal);
	ReleaseCOM(PosNormalTexBiNormalTangent);
}

#pragma endregion
