#pragma once

#include "DirectXMath.h"

//ī�޶� ���� 
struct CameraBuffer
{
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX proj;
};

//������Ʈ ����
struct ObjectBuffer
{
	DirectX::XMMATRIX world;
};

//��Ű�� ����
struct SkinningBuffer
{
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX BoneOffset[96];
};