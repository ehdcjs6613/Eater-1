#pragma once

//Device, DeviceContext 는 
//물리적인 그래픽 장치 하드웨어에 대한 
//소프트웨어 제어기라고 생각하면 된다.

//ID3D11Device 인터페이스는 기능 지원 점검과 자원 할당에 쓰인다.

//ID3D11DeviceContext 인터페이스는 렌더 대상을 설정하고, 
//자원을 그래픽 파이프 라인에 묶고, GPU가 렌더링 명령들을 지시하는 데 쓰인다.

/// <summary>
/// 디바이스와 디바이스 컨텍스트도 제역할이 다르기때문에
/// 따로 분류를해주었다.
/// 관리 | 그리기
///  
/// </summary>

class DirectXDevice
{
public:
	DirectXDevice();
	~DirectXDevice();
	ID3D11Device* m_pDX11Device;
private:
	//장치 관리할 인터페이스


	

public:
	//디바이스의 GetSet
	void SetDevice(ID3D11Device* _v);


	ID3D11Device* GetDevice();
};


