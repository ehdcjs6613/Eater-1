#pragma once
class DirectXRenderTargeter
{
public:
	DirectXRenderTargeter();
	~DirectXRenderTargeter();
public:
	ID3D11RenderTargetView* m_pRenderTarget;
};

