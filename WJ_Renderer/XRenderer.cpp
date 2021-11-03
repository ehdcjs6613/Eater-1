#include "Grahpics2D.h"
#include "DirectXRenderTargeter.h"
#include "DirectXAdapter.h"
#include "DirectXSwapChain.h"
#include "XRenderer.h"

//기본생성자로 초기화	
XRenderer::XRenderer() :m_ArrColor{ 0.1f,0.1f ,0.1f ,1 }, m_pRenderTargeter{} , m_pDepthStencil_State(nullptr), m_pDepthStencil_View(nullptr)

{
	m_pRenderTargeter = new DirectXRenderTargeter();
	
	
}

XRenderer::~XRenderer()
{
	m_pRenderTargeter->m_pRenderTarget->Release();
	delete m_pRenderTargeter;
	m_pRenderTargeter = nullptr;
}

bool XRenderer::Render_Initialize(ID3D11Device* _pDevice)
{
	this->m_pDirectXSwapChain = new DirectXSwapChain(_pDevice);
	
	return false;
}

bool XRenderer::Render_Begin(ID3D11DeviceContext* _pD3DeviceContext)
{
	//렌더타겟 (백버퍼)를 초기화한다.
	_pD3DeviceContext->ClearRenderTargetView(m_pRenderTargeter->m_pRenderTarget, this->m_ArrColor);
	
	//뎁스, 스텐실 뷰초기화
	_pD3DeviceContext->ClearDepthStencilView
	(
		this->m_pDepthStencil_View, 
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 
		1.0f, 
		0
	);

	return 0;
}

bool XRenderer::Render_Update(ID3D11DeviceContext* _pD3DeviceContext)
{

	return 0;
}

bool XRenderer::Render_LateUpdate(ID3D11DeviceContext* _pD3DeviceContext)
{


	_pD3DeviceContext->RSSetState(0);

	return 0;
}

bool XRenderer::Render_2D(Grahpics2D* _pGrahpics2D, DirectXAdapter* _pAdapter)
{
	int _yPos = 50;
	int _Text_Offset = 21;
	//
	_pGrahpics2D->Push_DrawText({ 10, _yPos }, 500, 1, 0, 0, 1, 20, (TCHAR*)L"Description: %s", _pAdapter->GetAdapter().Description);
	_pGrahpics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 1, 0, 1, 20, (TCHAR*)L"VendorID: %u", _pAdapter->GetAdapter().VendorId);
	_pGrahpics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 1, 0, 1, 20, (TCHAR*)L"DeviceID: %u", _pAdapter->GetAdapter().DeviceId);
	_pGrahpics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 1, 0, 1, 20, (TCHAR*)L"SubSysID: %u", _pAdapter->GetAdapter().SubSysId);
	_pGrahpics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 1, 0, 1, 20, (TCHAR*)L"Revision: %u", _pAdapter->GetAdapter().Revision);
	_pGrahpics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 0, 1, 1, 20, (TCHAR*)L"VideoMemory: %lu MB", _pAdapter->GetAdapter().DedicatedVideoMemory / 1024 / 1024);
	_pGrahpics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 0, 1, 1, 20, (TCHAR*)L"SystemMemory: %lu MB", _pAdapter->GetAdapter().DedicatedSystemMemory / 1024 / 1024);
	_pGrahpics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 0, 1, 1, 20, (TCHAR*)L"SharedSysMemory: %lu MB", _pAdapter->GetAdapter().SharedSystemMemory / 1024 / 1024);
	_pGrahpics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 1, 1, 0, 1, 20, (TCHAR*)L"AdpaterLuid: %u.%d", _pAdapter->GetAdapter().AdapterLuid.HighPart, _pAdapter->GetAdapter().AdapterLuid.LowPart);

	

	return false;
}

bool XRenderer::Render_End(IDXGISwapChain* _pSwapChain)
{
	_pSwapChain->Present(0, false);

	


	return 0;
}

void XRenderer::DrawState()
{

}  
ID3D11DepthStencilState* XRenderer::GetDepthStencil_State()
{
	return this->m_pDepthStencil_State;
}

ID3D11DepthStencilView* XRenderer::GetDepthStencil_View()
{
	return this->m_pDepthStencil_View;
}

D3D11_VIEWPORT XRenderer::GetD3D11ViewPort()
{
	return this->m_D3D11_ViewPort[0];
}
ID3D11Texture2D* XRenderer::GetDepthStencil_Buffer()
{
	return this->m_pDepthStencil_Buffer;
}

ID3D11RenderTargetView* XRenderer::GetRenderTargetView()
{
	return this->m_pRenderTargeter->m_pRenderTarget;
}
