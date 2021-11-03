#include "OneCompile.h"
#include "DirectXDevice.h"
#include "DirectXDeviceContext.h"

DirectXDeviceContext::DirectXDeviceContext() : m_pDX11DeviceContext(nullptr)
{

}

DirectXDeviceContext::~DirectXDeviceContext()
{
	m_pDX11DeviceContext->Release();
}

HRESULT DirectXDeviceContext::CreateDeviceContext(ID3D11Device* _pDevice)
{
	
	//디버그 모드에 따라 dx11의 모드를 설정한다.
	UINT CreateDeviceFlag = false;
	CreateDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;

	D3D_DRIVER_TYPE    DriverType = D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN;

	D3D_FEATURE_LEVEL  D3DFeatureLevel = D3D_FEATURE_LEVEL_11_0;

	UINT			   D3D4xMsaaQuality  = 0;//false

#ifdef DEBUG
	CreateDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	HRESULT HR = D3D11CreateDevice
	(
		NULL,			//NULL = Default apdater
		DriverType,
		NULL,			//소프트웨어 구동기를 지정한다. NULL인경우 지정하지않는다.
		CreateDeviceFlag,
		0,				//생성을 시도할 기능 수준의 순서를 결정하는 D3D_FEATURE_LEVEL 배열에 대한 포인터 입니다.
		0,
		D3D11_SDK_VERSION,
		&_pDevice,		//DeviceContext
		&D3DFeatureLevel,
		&this->m_pDX11DeviceContext
	);

	//포인터가 널인지 검사.
	

	
	//FeatureLevel이 d3d11이 안된(지원하지 않는)경우.
	if (D3DFeatureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		//일단 지금은 .. 패스
		return E_NOTIMPL;
	}

	//당사의 백 버퍼 포맷에 대한 4배 MSAA 품질 지원을 확인하십시오.
	// 모든 Direct3D 11 지원 장치는 모든 렌더에 대해 4배 MSAA 지원
	// 대상 포맷이므로 품질 지원만 확인하면 됩니다.
	_pDevice->CheckMultisampleQualityLevels
	(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		4,
		&D3D4xMsaaQuality
	);
	assert(D3D4xMsaaQuality > 0);

	//DXGI_SWAP_CHAIN_DESC를 작성하여 스왑 체인을 설명합니다.


	return S_OK;
}

ID3D11DeviceContext* DirectXDeviceContext::GetDeviceContext()
{
	//만약 디바이스 컨텍스트가없다면 반환
	if (nullptr == m_pDX11DeviceContext) { return nullptr; }
	return m_pDX11DeviceContext;
}

/*
4. Flags: 추가적인 장치 플래그들을 지정한다.

(흔히 쓰이는 2개)

ⓐ D3D_CREATE_DEVICE_DEBUG : 디버그 모드 빌드에서 디버그 계층을 활성화 하려면 이 플래그를 설정 해야한다.

( 이 플래그를 지정하면 VC++출력창에 디버그 메세지를 보낸다. )



ⓑ D3D_CREATE_DEVICE_SINGLETHREADED : Direct3D가 여러 개의 스레드에서 호출되지 않는다는 보장이 있을 때, 이 플래그를 지정하면 성능이 향상된다.

( 이 플래그가 활성화 되면 ID3D11Device::CreateDeferredContext의 호출은 실패한다.)

5. pFeatureLevels : D3D_FEATURE_LEVEL 형식의 배열 (널 값이면 최고수준)



*/