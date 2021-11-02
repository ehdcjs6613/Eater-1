#pragma once

#include "DirectXMath.h"

//ī�޶� ���� 
struct CameraBuffer
{
	DirectX::XMMATRIX viewproj;
	DirectX::XMMATRIX ViewMatrix;
	DirectX::XMFLOAT3 CamPos;
};

//������Ʈ ����
struct ObjectBuffer
{
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX TexMatrix;
};