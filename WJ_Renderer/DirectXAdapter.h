#pragma once
/// <summary>
/// ����� ������ ���� Ŭ�����̴�.
/// </summary>
class DirectXAdapter
{
public:
	DirectXAdapter();
	~DirectXAdapter();
private:
	//����� ������ ���� ����ü
	DXGI_ADAPTER_DESC1 m_AdapterDesc;
public:
	//������ ������� �Լ�
	HRESULT GetAdapterInfo();
	//������ ������ �� �Լ�
	DXGI_ADAPTER_DESC1 GetAdapter();
};

