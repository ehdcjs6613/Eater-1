#pragma once
/// <summary>
/// 스왑체인. winapi의 성능좋은 백버퍼같은 역할을한다.
/// </summary>
class DirectXSwapChain
{
private:
	UINT					 m_4xMsaaQuality;
	bool					 m_Enable4xMsaa;

public:
	IDXGISwapChain*			 m_pSwapChain;
	//insert Device initialize 
	DirectXSwapChain(ID3D11Device* _pDevice);
	~DirectXSwapChain();
public:
	//스왑체인을 만들자
	bool MakeASwapChain(ID3D11Device* _pDevice, HWND _hWnd, int _iWidth, int _iHeight);
	//리메이크된 스왑체인을 만들자
	bool ReMakedASwapChain(int _iWidth, int _iHeight);

public:
	IDXGISwapChain* GetSwapChain();
};

