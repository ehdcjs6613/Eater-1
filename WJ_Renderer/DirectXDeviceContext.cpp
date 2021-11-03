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
	
	//����� ��忡 ���� dx11�� ��带 �����Ѵ�.
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
		NULL,			//����Ʈ���� �����⸦ �����Ѵ�. NULL�ΰ�� ���������ʴ´�.
		CreateDeviceFlag,
		0,				//������ �õ��� ��� ������ ������ �����ϴ� D3D_FEATURE_LEVEL �迭�� ���� ������ �Դϴ�.
		0,
		D3D11_SDK_VERSION,
		&_pDevice,		//DeviceContext
		&D3DFeatureLevel,
		&this->m_pDX11DeviceContext
	);

	//�����Ͱ� ������ �˻�.
	

	
	//FeatureLevel�� d3d11�� �ȵ�(�������� �ʴ�)���.
	if (D3DFeatureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		//�ϴ� ������ .. �н�
		return E_NOTIMPL;
	}

	//����� �� ���� ���˿� ���� 4�� MSAA ǰ�� ������ Ȯ���Ͻʽÿ�.
	// ��� Direct3D 11 ���� ��ġ�� ��� ������ ���� 4�� MSAA ����
	// ��� �����̹Ƿ� ǰ�� ������ Ȯ���ϸ� �˴ϴ�.
	_pDevice->CheckMultisampleQualityLevels
	(
		DXGI_FORMAT_R8G8B8A8_UNORM,
		4,
		&D3D4xMsaaQuality
	);
	assert(D3D4xMsaaQuality > 0);

	//DXGI_SWAP_CHAIN_DESC�� �ۼ��Ͽ� ���� ü���� �����մϴ�.


	return S_OK;
}

ID3D11DeviceContext* DirectXDeviceContext::GetDeviceContext()
{
	//���� ����̽� ���ؽ�Ʈ�����ٸ� ��ȯ
	if (nullptr == m_pDX11DeviceContext) { return nullptr; }
	return m_pDX11DeviceContext;
}

/*
4. Flags: �߰����� ��ġ �÷��׵��� �����Ѵ�.

(���� ���̴� 2��)

�� D3D_CREATE_DEVICE_DEBUG : ����� ��� ���忡�� ����� ������ Ȱ��ȭ �Ϸ��� �� �÷��׸� ���� �ؾ��Ѵ�.

( �� �÷��׸� �����ϸ� VC++���â�� ����� �޼����� ������. )



�� D3D_CREATE_DEVICE_SINGLETHREADED : Direct3D�� ���� ���� �����忡�� ȣ����� �ʴ´ٴ� ������ ���� ��, �� �÷��׸� �����ϸ� ������ ���ȴ�.

( �� �÷��װ� Ȱ��ȭ �Ǹ� ID3D11Device::CreateDeferredContext�� ȣ���� �����Ѵ�.)

5. pFeatureLevels : D3D_FEATURE_LEVEL ������ �迭 (�� ���̸� �ְ����)



*/