#pragma once
#include "OneCompile.h"

//����Ÿ�� Ŭ����

class DirectXRenderTargeter
{
public:
	//L-value������ �ۺ�����
	ID3D11RenderTargetView* m_pRenderTarget;
public:
	DirectXRenderTargeter();
	~DirectXRenderTargeter();
private:
public:
	ID3D11RenderTargetView* GetRenderTarget();
	void Create(ID3D11Device* _pDevice, IDXGISwapChain* m_pSwapChain);
};

