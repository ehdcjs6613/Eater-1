#pragma once
/// <summary>
/// ����ü��. winapi�� �������� ����۰��� �������Ѵ�.
/// </summary>
class DirectXSwapChain
{
private:
	UINT					 m_4xMsaaQuality;
	bool					 m_Enable4xMsaa;
	IDXGISwapChain*			 m_pSwapChain;

public:
	//insert Device initialize 
	DirectXSwapChain(ID3D11Device* _pDevice);
	~DirectXSwapChain();
public:
	//Make  SwapChain 
	bool MakeASwapChain(ID3D11Device* _pDevice, HWND _hWnd, int _iWidth, int _iHeight);

public:
	IDXGISwapChain* GetSwapChain();
};

