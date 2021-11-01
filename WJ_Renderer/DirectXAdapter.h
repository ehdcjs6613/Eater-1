#pragma once
class DirectXAdapter
{
public:
	DirectXAdapter();
	~DirectXAdapter();
private:
	DXGI_ADAPTER_DESC1 m_AdapterDesc;
public:
	HRESULT GetAdapterInfo();
	DXGI_ADAPTER_DESC1 GetAdapter();
};

