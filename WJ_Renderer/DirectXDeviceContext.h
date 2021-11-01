#pragma once


class DirectXDeviceContext
{
public:
	DirectXDeviceContext();
	~DirectXDeviceContext();

private:
	//��ġ���� �׷��� �������̽�
	ID3D11DeviceContext* m_pDX11DeviceContext;

public:

	HRESULT CreateDeviceContext(ID3D11Device* _pDevice);
};