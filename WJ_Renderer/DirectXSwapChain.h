#pragma once
/// <summary>
/// ����ü��. winapi�� �������� ����۰��� �������Ѵ�.
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
	//����ü���� ������ 1
	bool MakeASwapChain(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext , DXGI_SWAP_CHAIN_DESC _swDesc); 
	//����ü���� ������ 2
	bool MakeASwapChain(ID3D11Device* _pDevice, HWND _hWnd, int _iWidth, int _iHeight);
	//������ũ�� ����ü���� ������
	bool ReMakedASwapChain(int _iWidth, int _iHeight);

public:
	IDXGISwapChain* GetSwapChain();
};

