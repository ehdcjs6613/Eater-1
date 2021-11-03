#pragma once
#include "d3d11.h"
#include <SimpleMath.h>
#include <DirectXMath.h>
struct Deferred32
{
	//위치
	DirectX::SimpleMath::Vector3 Pos;
	//텍스쳐
	DirectX::SimpleMath::Vector2 Tex;
	//노말
	DirectX::SimpleMath::Vector3 Nomal;
	//탄젠트
	DirectX::SimpleMath::Vector3 Tangent;
};

//코레일 번호 2173406236
//쉐이더들을 보관할 데이터
struct ShaderData
{
	ID3D11VertexShader* VertexShader	= nullptr;
	ID3D11PixelShader* PixelShader		= nullptr;
	ID3D11InputLayout* Layout			= nullptr;
};