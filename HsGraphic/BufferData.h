#pragma once

#include "DirectXMath.h"

//카메라 버퍼 
struct CameraBuffer
{
	DirectX::XMMATRIX viewproj;
	DirectX::XMMATRIX ViewMatrix;
	DirectX::XMFLOAT3 CamPos;
};

//오브젝트 버퍼
struct ObjectBuffer
{
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX TexMatrix;
};