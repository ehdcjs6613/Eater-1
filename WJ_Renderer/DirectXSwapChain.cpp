#include "OneCompile.h"
#include "DirectXDefine.h"
#include "DirectXSwapChain.h"

DirectXSwapChain::DirectXSwapChain(ID3D11Device* _pDevice) :  m_pSwapChain(nullptr),m_4xMsaaQuality(0),m_Enable4xMsaa(false)
{
	if (nullptr == _pDevice)
	{
		return;
	}
	/// 멀티샘플링 몇단계까지 되는지 체크
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
	/// 스왑체인 구조체를 만들어준다
	/// </summary>
	/// <param name="_pDevice"></param> 디바이스 넣고
	/// <param name="_hWnd"></param>    핸들을 넣고
	/// <param name="_iWidth"></param>  사이즈w
	/// <param name="_iHeight"></param> 사이즈h 를 넣으면 끝!
	/// <returns></returns>
	DXGI_SWAP_CHAIN_DESC swapChain_Description;
	swapChain_Description.BufferDesc.Width = _iWidth;
	swapChain_Description.BufferDesc.Height = _iHeight;
	//// Vsync 지원
	//swapChain_Description.BufferDesc.RefreshRate.Numerator = numerator;
	//swapChain_Description.BufferDesc.RefreshRate.Denominator = denominator;

	// Vsync 미지원
	swapChain_Description.BufferDesc.RefreshRate.Numerator = 0;
	swapChain_Description.BufferDesc.RefreshRate.Denominator = 1;
	swapChain_Description.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChain_Description.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChain_Description.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// Use 4X MSAA? 
	//멀티샘플링 안티앨리어싱을 사용할것인가요?
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
	//추가 설정
	swapChain_Description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChain_Description.BufferCount = 1;
	swapChain_Description.OutputWindow = _hWnd;
	swapChain_Description.Windowed = true;
	swapChain_Description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChain_Description.Flags = 0;
	

	// 스왑 체인을 올바르게 만들기 위해, 우리는 다음과 같은 IDXGIFactory를 사용해야 한다.
	// 장치를 만드는 데 사용됩니다. 다른 IDXGIFactory 인스턴스를 사용하려는 경우
	// (CreateDX 호출)GIFactory), 오류가 발생합니다: "IDXGIFactory::CreateSwapChain:
	// 이 함수는 다른 IDXGIFactory의 장치로 호출됩니다."

	// D3디바이스로부터 dxgi디바이스를 얻어온다.
	IDXGIDevice* dxgiDevice = 0;
	HR(dxgiDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));

	// dxgi디바이스로부터 dxgi어댑터를 얻어온다.
	IDXGIAdapter* dxgiAdapter = 0;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	// dxgi어댑터로부터 dxgi팩토리를 얻어온다.
	IDXGIFactory* dxgiFactory = 0;
	HR(dxgiFactory->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	// 드디어 스왑체인을 생성한다.
	HR(dxgiFactory->CreateSwapChain(_pDevice, &swapChain_Description, &m_pSwapChain));

	//안전하게 초기화
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


