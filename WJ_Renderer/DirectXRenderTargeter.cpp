
#include "DirectXDefine.h"
#include "DirectXRenderTargeter.h"

DirectXRenderTargeter::DirectXRenderTargeter()
{

	
	
}

DirectXRenderTargeter::~DirectXRenderTargeter()
{
}

void DirectXRenderTargeter::Create(ID3D11Device* _pDevice, IDXGISwapChain* m_pSwapChain)
{
	if (nullptr == _pDevice)	 { return; }
	if (nullptr == m_pSwapChain) { return; }
	
	ID3D11Texture2D* backBuffer = nullptr;

	HR(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&backBuffer)));

	if (backBuffer != nullptr)
	{
		HR(_pDevice->CreateRenderTargetView(backBuffer, 0, &m_pRenderTarget));
	}
	// Release pointer to the back buffer as we no longer need it.
	// �� �̻� �ʿ����� �����Ƿ� �ĸ� ���ۿ� ���� ���� �Լ��Դϴ�.

	backBuffer->Release();
	
}
