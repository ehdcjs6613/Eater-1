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

private:
	ID3D11DeviceContext* m_pDX11DeviceContext;
	//��ġ���� �׷��� �������̽�
public:
	//����̽��� �����͸� �޾Ƽ� ������Ų��.
	HRESULT CreateDeviceContext(ID3D11Device* _pDevice);

	//void	CreateViewPort()
public:
	ID3D11DeviceContext* GetDeviceContext();
	void SetDeviceContext(ID3D11DeviceContext* _pDevice);
};