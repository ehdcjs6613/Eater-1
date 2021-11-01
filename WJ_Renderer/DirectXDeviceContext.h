#pragma once


class DirectXDeviceContext
{
public:
	DirectXDeviceContext();
	~DirectXDeviceContext();

private:
	//장치들을 그려줄 인터페이스
	ID3D11DeviceContext* m_pDX11DeviceContext;

public:

	HRESULT CreateDeviceContext(ID3D11Device* _pDevice);
};