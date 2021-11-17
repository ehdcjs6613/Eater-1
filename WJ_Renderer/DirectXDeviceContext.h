#pragma once

/// <summary>
/// ��ġ�� �׸��� ����ϴ� DC
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
	//��ġ���� �׷��� �������̽�
public:
	//����̽��� �����͸� �޾Ƽ� ������Ų��.
	HRESULT CreateDeviceContext(ID3D11Device* _pDevice);

	void SetDeviceContext(ID3D11DeviceContext* Context)
	{
		m_pDX11DeviceContext = Context;
	};
public:
	ID3D11DeviceContext* GetDeviceContext();
};