#pragma once
#include "OneCompile.h"

class DirectXRenderTargeter
{
public:
	DirectXRenderTargeter();
	~DirectXRenderTargeter();
public:
	ID3D11RenderTargetView* m_pRenderTarget;
public:
	void Create(ID3D11Device* _pDevice, IDXGISwapChain* m_pSwapChain);
};

