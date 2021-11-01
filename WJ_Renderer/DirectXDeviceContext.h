#pragma once

/// <summary>
/// ��ġ�� �׸��� ����ϴ� DC
/// </summary>
class DirectXDeviceContext
{
public:
	DirectXDeviceContext();
	~DirectXDeviceContext();

private:
	//��ġ���� �׷��� �������̽�
	ID3D11DeviceContext* m_pDX11DeviceContext;
public:
	//����̽��� �����͸� �޾Ƽ� ������Ų��.
	HRESULT CreateDeviceContext(ID3D11Device* _pDevice);
public:
	ID3D11DeviceContext* GetDeviceContext();
};