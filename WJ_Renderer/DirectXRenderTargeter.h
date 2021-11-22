#pragma once
#include "OneCompile.h"

//렌더타겟 클래스

class DirectXRenderTargeter
{
public:
	//L-value문제로 퍼블릭선언
	ID3D11RenderTargetView* m_pRenderTarget;
public:
	DirectXRenderTargeter();
	~DirectXRenderTargeter();
private:
public:
	ID3D11RenderTargetView* GetRenderTarget();
	void Create(ID3D11Device* _pDevice, IDXGISwapChain* m_pSwapChain);
};

