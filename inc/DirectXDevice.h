#pragma once

//Device, DeviceContext �� 
//�������� �׷��� ��ġ �ϵ��� ���� 
//����Ʈ���� ������� �����ϸ� �ȴ�.

//ID3D11Device �������̽��� ��� ���� ���˰� �ڿ� �Ҵ翡 ���δ�.

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
	ID3D11Device* m_pDX11Device;
private:
	//��ġ ������ �������̽�


	

public:
	//����̽��� GetSet
	void SetDevice(ID3D11Device* _v);


	ID3D11Device* GetDevice();
};


