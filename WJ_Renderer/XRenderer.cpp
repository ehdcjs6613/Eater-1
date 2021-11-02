#include "Grahpics2D.h"
#include "XRenderer.h"
//기본생성자로 초기화	
XRenderer::XRenderer() :m_ArrColor{ 1.0f,0.1f ,0.1f ,1 }, m_pRenderTarget{} , m_pDepthStencil_State(nullptr), m_pDepthStencil_View(nullptr)
{
	
}

XRenderer::~XRenderer()
{
}

bool XRenderer::Render_Begin(ID3D11DeviceContext* _pD3DeviceContext)
{
	//렌더타겟 (백버퍼)를 초기화한다.
	_pD3DeviceContext->ClearRenderTargetView(m_pRenderTarget[0], this->m_ArrColor);
	
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

bool XRenderer::Render_End(ID3D11DeviceContext* _pD3DeviceContext)
{
	_pD3DeviceContext->RSSetState(0);

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
	return this->m_pRenderTarget[0];
}
