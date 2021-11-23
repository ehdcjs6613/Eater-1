#pragma once

//Device, DeviceContext �� 
//�������� �׷��� ��ġ �ϵ��� ���� 
//����Ʈ���� ������� �����ϸ� �ȴ�.

//ID3D11Device �������̽��� ���� �� ��� ���� ���˰� �ڿ� �Ҵ翡 ���δ�.
//

//ID3D11DeviceContext �������̽��� ���� ����� �����ϰ�, 
//�ڿ��� �׷��� ������ ���ο� ����, GPU�� ������ ��ɵ��� �����ϴ� �� ���δ�.

/// <summary>
/// ����̽��� ����̽� ���ؽ�Ʈ�� �������� �ٸ��⶧����
/// ���� �з������־���.
/// ���� | �׸���
///  
/// </summary>



class DirectXDevice
{
public:
	DirectXDevice();
	~DirectXDevice();
private:
	//��ġ ������ �������̽�
	ID3D11Device*	    m_pDX11Device;
	int					m_iWidth;
	int					m_iHeight;

	

public:
	//					 ����̽��� GetSet
	void				 SetDevice(ID3D11Device* _v);
	ID3D11Device*		 GetDevice();
	int					 GetWidth();
	int					 GetHeight();
public:
	void				 CreateSize(int, int);
	void				 CreateDepthBuffer(ID3D11Texture2D*);
	void				 CreateDepthStencilState(ID3D11DeviceContext*, ID3D11DepthStencilState*);
	void				 CreateDepthStencilView(ID3D11DeviceContext* _pDeviceContext, ID3D11DepthStencilView* _pDepthStencilView, ID3D11Texture2D* _pDepthStencilBuffer, ID3D11RenderTargetView* _pRenderTarget);
	void				 CreateResterize(ID3D11DeviceContext* _pDeviceContext, ID3D11RasterizerState* _pRasterizerState);
	D3D11_VIEWPORT		 CreateViewPort(ID3D11DeviceContext* _pDeviceContext);

	ID3D11Texture2D*     CreateInitFactory(int& _vedioCard);
	DXGI_SWAP_CHAIN_DESC CreateInitSwapChain(HWND _hWnd);

};


