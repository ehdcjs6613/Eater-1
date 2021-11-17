#pragma once

/// <summary>
/// 장치의 그림을 담당하는 DC
/// </summary>
/// 
/// 
class DirectXDeviceContext
{
public:
	DirectXDeviceContext();
	~DirectXDeviceContext();

	ID3D11DeviceContext* m_pDX11DeviceContext;
private:
	//장치들을 그려줄 인터페이스
public:
	//디바이스의 포인터를 받아서 생성시킨다.
	HRESULT CreateDeviceContext(ID3D11Device* _pDevice);

	void SetDeviceContext(ID3D11DeviceContext* Context)
	{
		m_pDX11DeviceContext = Context;
	};
public:
	ID3D11DeviceContext* GetDeviceContext();
};