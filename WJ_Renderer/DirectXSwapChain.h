#pragma once
class DirectXSwapChain
{
private:
	UINT					 m_4xMsaaQuality;
	bool					 m_Enable4xMsaa;
	IDXGISwapChain*			 m_pSwapChain;

public:
	DirectXSwapChain(ID3D11Device* _pDevice);
	~DirectXSwapChain();
public:
	
	bool MakeASwapChain(ID3D11Device* _pDevice, HWND _hWnd, int _iWidth, int _iHeight);
};

