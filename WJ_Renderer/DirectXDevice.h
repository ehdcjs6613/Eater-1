#pragma once

//Device, DeviceContext �� 
//�������� �׷��� ��ġ �ϵ��� ���� 
//����Ʈ���� ������� �����ϸ� �ȴ�.


//ID3D11Device �������̽��� ��� ���� ���˰� �ڿ� �Ҵ翡 ���δ�.

//ID3D11DeviceContext �������̽��� ���� ����� �����ϰ�, 
//�ڿ��� �׷��� ������ ���ο� ����, GPU�� ������ ��ɵ��� �����ϴ� �� ���δ�.



class DirectXDevice
{
public:
	DirectXDevice();
	~DirectXDevice();
private:
	//��ġ ������ �������̽�
	ID3D11Device* m_pDX11Device;

public:
	void SetDevice(ID3D11Device* _v);
	ID3D11Device* GetDevice();
};


