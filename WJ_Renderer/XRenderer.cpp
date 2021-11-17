//#include "Grahpics2D.h"
#include "DirectXRenderTargeter.h"
#include "DirectXAdapter.h"
#include "DirectXSwapChain.h"
#include "XVertex.h"
#include "XRenderer.h"
#include <tchar.h>

//
//기본생성자로 초기화	
XRenderer::XRenderer() :m_ArrColor{ 0.5f, 0.0f, 0.35f, 1.0f }, m_pRenderTargeter{} , m_pDepthStencil_State(nullptr), m_pDepthStencil_View(nullptr)

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
	_pD3DeviceContext->OMSetRenderTargets(1, &m_pRenderTargeter->m_pRenderTarget,m_pDepthStencil_View);
	
	



	return 0;
}

bool XRenderer::Render_Update(
	ID3D11Device* m_pDevice,
	ID3D11DeviceContext* _pD3DeviceContext , 
	ID3D11VertexShader* _vs, ID3D11PixelShader* _ps ,
	ID3D11InputLayout* _il, ID3D11Buffer* _vb, ID3D11Buffer* _vb2,
	ID3D11SamplerState* _pSampler
)
{
	HRESULT hr = S_OK;
	
	_pD3DeviceContext->IASetInputLayout(_il);
	_pD3DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_POINTLIST);
	
	_pD3DeviceContext->VSSetShader(_vs, nullptr, 0);
	_pD3DeviceContext->PSSetShader(_ps, nullptr, 0);
	
	UINT stride = sizeof(XVertexTex);
	UINT offset = 0;
	
	//=======================================================================
	///삼각형 그리기 3
	//=======================================================================
	//XVertexTex v2[] =
	//{
	//	XVertexTex(-0.5f,  -0.5f,    1.f, 0.0f,1.0f),//B L
	//	XVertexTex(0.0f,   +0.5f,	 1.f, 0.5f,0.0f),  //T M
	//	XVertexTex(+0.5f,  -0.5f,	 1.f, 1.0f,1.0f),  //B R
	//	//XVertex(0.0f,  +0.1f),	 //T
	//};
	//
	//
	//
	//
	//D3D11_BUFFER_DESC vertexBufferDESC2;
	//ZeroMemory(&vertexBufferDESC2, sizeof(D3D11_BUFFER_DESC));
	//
	//vertexBufferDESC2.Usage = D3D11_USAGE_DEFAULT;
	//vertexBufferDESC2.ByteWidth = sizeof(XVertexTex) * ARRAYSIZE(v2);//* ARRAYSIZE(v);
	//vertexBufferDESC2.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//vertexBufferDESC2.CPUAccessFlags = 0;
	//vertexBufferDESC2.MiscFlags = 0;
	//
	//D3D11_SUBRESOURCE_DATA vertexBufferData2;
	//ZeroMemory(&vertexBufferData2, sizeof(D3D11_SUBRESOURCE_DATA));
	//vertexBufferData2.pSysMem = v2;
	//vertexBufferData2.SysMemPitch = 0;
	//vertexBufferData2.SysMemSlicePitch = 0;
	
	//DirectX::CreateWICTextureFromFile
	
	//hr = m_pDevice->CreateBuffer(&vertexBufferDESC2, &vertexBufferData2, &_vb);
	
	_pD3DeviceContext->PSSetSamplers(1, 0, &_pSampler);
	
	
	_pD3DeviceContext->IASetVertexBuffers(0, 1, &_vb, &stride, &offset);
	_pD3DeviceContext->IASetIndexBuffer(_vb2, DXGI_FORMAT_R32_UINT, 0);

	_pD3DeviceContext->Draw(3, 0);
	
	
	return 0;
}

bool XRenderer::Render_FrmUpdate(ID3D11DeviceContext* _pD3DeviceContext, ID3D11RasterizerState* _pRasterizerState, ID3D11SamplerState* _pSamplerState)
{
	_pD3DeviceContext->RSSetState(_pRasterizerState);
	_pD3DeviceContext->OMSetDepthStencilState(m_pDepthStencil_State, 0);
	_pD3DeviceContext->PSSetSamplers(0, 1, &_pSamplerState);

	return 0;
}

bool XRenderer::Render_2D(Grahpics2D* _pGrahpics2D, DirectXAdapter* _pAdapter)
{
	int _yPos = 50;
	int _Text_Offset = 21;
	//
	//_pGrahpics2D->Push_DrawText({ 10, _yPos }, 500, 1, 0, 0, 1, 20, (TCHAR*)L"Description: %s", _pAdapter->GetAdapter().Description);
	//_pGrahpics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 1, 0, 1, 20, (TCHAR*) L"VendorID: %u", _pAdapter->GetAdapter().VendorId);
	//_pGrahpics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 1, 0, 1, 20, (TCHAR*) L"DeviceID: %u", _pAdapter->GetAdapter().DeviceId);
	//_pGrahpics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 1, 0, 1, 20, (TCHAR*) L"SubSysID: %u", _pAdapter->GetAdapter().SubSysId);
	//_pGrahpics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 1, 0, 1, 20, (TCHAR*) L"Revision: %u", _pAdapter->GetAdapter().Revision);
	//_pGrahpics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 0, 1, 1, 20, (TCHAR*) L"VideoMemory: %lu MB", _pAdapter->GetAdapter().DedicatedVideoMemory / 1024 / 1024);
	//_pGrahpics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 0, 1, 1, 20, (TCHAR*) L"SystemMemory: %lu MB", _pAdapter->GetAdapter().DedicatedSystemMemory / 1024 / 1024);
	//_pGrahpics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 0, 0, 1, 1, 20, (TCHAR*) L"SharedSysMemory: %lu MB", _pAdapter->GetAdapter().SharedSystemMemory / 1024 / 1024);
	//_pGrahpics2D->Push_DrawText({ 10, _yPos += _Text_Offset }, 500, 1, 1, 0, 1, 20, (TCHAR*) L"AdpaterLuid: %u.%d", _pAdapter->GetAdapter().AdapterLuid.HighPart, _pAdapter->GetAdapter().AdapterLuid.LowPart);
	//
	//_pGrahpics2D->Push_DrawImage
	//(
	//	L"../Image/apple_1.png", //name
	//	{ 1000,1 },				//Image Position
	//	{ 1,1 },				//Image Scale//
	//	0,
	//	1.0f,
	//	{ 0,0 }, //POS
	//	{ 0.1f, 0.1f }, //SCALE
	//	0,
	//	1.0f
	//);
	//
	//_pGrahpics2D->Push_DrawSprite
	//(
	//	L"../Image/atk_1.png", //name
	//	{ 1000,800 },				//Image Position
	//	{ 1,1 },				//Image Scale//
	//	0,
	//	1.0f,
	//	{ 0,0 }, //POS
	//	{ 1.0f, 1.0f }, //SCALE/
	//	0,
	//	1.0f,
	//	6,
	//	171,
	//	144
	//);


	return false;
}

bool XRenderer::Render_End(Grahpics2D* _pGrahpics2D, IDXGISwapChain* _pSwapChain)
{
	//_pGrahpics2D->Draw_AllImage();
	//_pGrahpics2D->Draw_AllSprite();
	//_pGrahpics2D->Draw_AllText();

	//_pSwapChain->Present(0, false);

	


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
