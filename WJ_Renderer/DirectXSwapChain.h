#pragma once
/// <summary>
/// 스왑체인. winapi의 성능좋은 백버퍼같은 역할을한다.
/// </summary>
class DirectXSwapChain
{
private:
	UINT					 m_4xMsaaQuality;
	bool					 m_Enable4xMsaa;
	D3D_FEATURE_LEVEL		 m_FeatureLevel;
	IDXGISwapChain*			 m_pSwapChain;
public:
	//insert Device initialize 
	DirectXSwapChain(ID3D11Device* _pDevice);
	~DirectXSwapChain();
public:
	//스왑체인을 만들자 1
	bool MakeASwapChain(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext , DXGI_SWAP_CHAIN_DESC _swDesc); 
	//스왑체인을 만들자 2
	bool MakeASwapChain(ID3D11Device* _pDevice, HWND _hWnd, int _iWidth, int _iHeight);
	//리메이크된 스왑체인을 만들자
	bool ReMakedASwapChain(int _iWidth, int _iHeight);

public:
	IDXGISwapChain* GetSwapChain();
};

