#include "OneCompile.h"
#include "DirectXDefine.h"
#include "DirectXSwapChain.h"

DirectXSwapChain::DirectXSwapChain(ID3D11Device* _pDevice) :  m_pSwapChain(nullptr),m_4xMsaaQuality(0),m_Enable4xMsaa(false)
{
	if (nullptr == _pDevice)
	{
		return;
	}
	/// ��Ƽ���ø� ��ܰ���� �Ǵ��� üũ
	// Check 4X MSAA quality support for our back buffer format.
	// All Direct3D 11 capable devices support 4X MSAA for all render 
	// target formats, so we only need to check quality support
	

	HR(_pDevice->CheckMultisampleQualityLevels
	(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_4xMsaaQuality)
	);
	assert(m_4xMsaaQuality > 0);

}

DirectXSwapChain::~DirectXSwapChain()
{
	//ReleaseCOM(m_pSwapChain);
	m_pSwapChain->Release();
}

bool DirectXSwapChain::MakeASwapChain(ID3D11Device* _pDevice, HWND _hWnd, int _iWidth, int _iHeight)
{

	/// <summary>
	/// ����ü�� ����ü�� ������ش�
	/// </summary>
	/// <param name="_pDevice"></param> ����̽� �ְ�
	/// <param name="_hWnd"></param>    �ڵ��� �ְ�
	/// <param name="_iWidth"></param>  ������w
	/// <param name="_iHeight"></param> ������h �� ������ ��!
	/// <returns></returns>
	DXGI_SWAP_CHAIN_DESC swapChain_Description;
	swapChain_Description.BufferDesc.Width = _iWidth;
	swapChain_Description.BufferDesc.Height = _iHeight;
	//// Vsync ����
	//swapChain_Description.BufferDesc.RefreshRate.Numerator = numerator;
	//swapChain_Description.BufferDesc.RefreshRate.Denominator = denominator;

	// Vsync ������
	swapChain_Description.BufferDesc.RefreshRate.Numerator = 0;
	swapChain_Description.BufferDesc.RefreshRate.Denominator = 1;
	swapChain_Description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChain_Description.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChain_Description.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Use 4X MSAA? 
	//��Ƽ���ø� ��Ƽ�ٸ������ ����Ұ��ΰ���?
	if (m_Enable4xMsaa)
	{
		swapChain_Description.SampleDesc.Count = 4;
		swapChain_Description.SampleDesc.Quality = m_4xMsaaQuality - 1;
	}
	// No MSAA
	else
	{
		swapChain_Description.SampleDesc.Count = 1;
		swapChain_Description.SampleDesc.Quality = 0;
	}
	//�߰� ����
	swapChain_Description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChain_Description.BufferCount = 1;
	swapChain_Description.OutputWindow = _hWnd;
	swapChain_Description.Windowed = true;
	swapChain_Description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChain_Description.Flags = 0;
	

	// ���� ü���� �ùٸ��� ����� ����, �츮�� ������ ���� IDXGIFactory�� ����ؾ� �Ѵ�.
	// ��ġ�� ����� �� ���˴ϴ�. �ٸ� IDXGIFactory �ν��Ͻ��� ����Ϸ��� ���
	// (CreateDX ȣ��)GIFactory), ������ �߻��մϴ�: "IDXGIFactory::CreateSwapChain:
	// �� �Լ��� �ٸ� IDXGIFactory�� ��ġ�� ȣ��˴ϴ�."

	// D3����̽��κ��� dxgi����̽��� ���´�.
	IDXGIDevice* dxgiDevice = 0;
	HR(dxgiDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	// dxgi����̽��κ��� dxgi����͸� ���´�.
	IDXGIAdapter* dxgiAdapter = 0;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	// dxgi����ͷκ��� dxgi���丮�� ���´�.
	IDXGIFactory* dxgiFactory = 0;
	HR(dxgiFactory->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	// ���� ����ü���� �����Ѵ�.
	HR(dxgiFactory->CreateSwapChain(_pDevice, &swapChain_Description, &m_pSwapChain));

	//�����ϰ� �ʱ�ȭ
	ReleaseCOM(dxgiDevice);
	ReleaseCOM(dxgiAdapter);
	ReleaseCOM(dxgiFactory);

	return 0;
}

bool DirectXSwapChain::ReMakedASwapChain(int _iWidth, int _iHeight)
{
	HR(this->m_pSwapChain->ResizeBuffers
	(
		1,										//BufferCount
		_iWidth,
		_iHeight,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		0										//SwapChainFLAG
	));
	


	return 0;
}

IDXGISwapChain* DirectXSwapChain::GetSwapChain()
{
	return m_pSwapChain;
}


