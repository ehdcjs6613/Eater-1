#pragma once
#include "DxDefine.h"
namespace VertexStruct
{
	struct VertexType
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT2 Texture;
	};

	struct Basic32
	{
		DirectX::XMFLOAT3 Pos;
		DirectX::XMFLOAT3 Normal;
		DirectX::XMFLOAT2 Tex;
	};
}


class VertexPositionColor
{
public:
	VertexPositionColor() = default;

	VertexPositionColor(const VertexPositionColor&) = default;
	VertexPositionColor& operator=(const VertexPositionColor&) = default;

	VertexPositionColor(VertexPositionColor&&) = default;
	VertexPositionColor& operator=(VertexPositionColor&&) = default;

	VertexPositionColor(DirectX::XMFLOAT3 const& iposition, DirectX::XMFLOAT4 const& icolor) noexcept
		: position(iposition),
		color(icolor)
	{ }

	VertexPositionColor(DirectX::FXMVECTOR iposition, DirectX::FXMVECTOR icolor) noexcept
	{
		XMStoreFloat3(&this->position, iposition);
		XMStoreFloat4(&this->color, icolor);
	}

	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT4 color;

	static constexpr unsigned int InputElementCount = 2;
	static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
};