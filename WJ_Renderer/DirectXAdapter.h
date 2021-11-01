#pragma once
/// <summary>
/// 어뎁터의 정보를 지닌 클래스이다.
/// </summary>
class DirectXAdapter
{
public:
	DirectXAdapter();
	~DirectXAdapter();
private:
	//어뎁터의 정보를 지닌 구조체
	DXGI_ADAPTER_DESC1 m_AdapterDesc;
public:
	//정보를 만들어줄 함수
	HRESULT GetAdapterInfo();
	//정보를 가져오 올 함수
	DXGI_ADAPTER_DESC1 GetAdapter();
};

