#pragma once
#include "OneCompile.h"

__interface XGeometry
{

public:
	virtual BOOL Initialize(ID3D11Device*, ID3D11DeviceContext* , ID3D11RasterizerState*) = 0;
	virtual BOOL BuildGeometry() = 0;
	virtual BOOL BuildFX() = 0;
	virtual BOOL BuildLayout() = 0;
	virtual BOOL Update(const  DirectX::SimpleMath::Matrix* view, const DirectX::SimpleMath::Matrix* proj) = 0;
	virtual BOOL Destroy() = 0;

public:
	virtual void Render() = 0;
};

