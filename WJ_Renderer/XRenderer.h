#pragma once
/// <summary>
/// �������� ����� ���� �������̽��̴�.
/// </summary>
#include "OneCompile.h"

class DirectXRenderTargeter;
class Grahpics2D;
class DirectXSwapChain;
class DirectXAdapter;

__interface IRenderableFunc
{
	bool Render_Initialize	(ID3D11Device* _pDevice) =0;
	bool Render_Begin		(ID3D11DeviceContext* _pD3DeviceContext) = 0;
	
	bool Render_Update		(
		ID3D11Device* m_pDevice,  ID3D11DeviceContext* _pD3DeviceContext, 
		ID3D11VertexShader* _vs, ID3D11PixelShader* _ps, 
		ID3D11InputLayout* _il, ID3D11Buffer* _vb, 
		ID3D11Buffer* _vb2 , ID3D11SamplerState* _pSampler
	) = 0;
	
	
	bool Render_LateUpdate	(ID3D11DeviceContext* _pD3DeviceContext , ID3D11RasterizerState* _pRasterizerState) = 0;
	bool Render_2D			(Grahpics2D* _pGrahpics2D, DirectXAdapter* _pAdapter) = 0;
	bool Render_End			(Grahpics2D* _pGrahpics2D, IDXGISwapChain* _pSwapChain) = 0;
};
/// <summary>
/// ���� ��� �׸����ΰ�..
/// </summary>


class XRenderer : public IRenderableFunc
{
public:
	DirectXSwapChain*		 m_pDirectXSwapChain;

	
	//ID3D11RenderTargetView*  m_pRenderTarget[5];
	DirectXRenderTargeter*   m_pRenderTargeter;

	ID3D11Texture2D*		 m_pDepthStencil_Buffer;
	ID3D11DepthStencilState* m_pDepthStencil_State;
	ID3D11DepthStencilView*  m_pDepthStencil_View;
	D3D11_VIEWPORT			 m_D3D11_ViewPort[5];
	
private:
	FLOAT					 m_ArrColor[4];

	

public:
	XRenderer();
	virtual ~XRenderer() final;

public:
	bool Render_Initialize   (ID3D11Device* _pDevice) override;
	bool Render_Begin		 (ID3D11DeviceContext* _pD3DeviceContext)override;
	bool Render_Update		 
	(
		ID3D11Device* m_pDevice, ID3D11DeviceContext* _pD3DeviceContext 
		, ID3D11VertexShader* _vs, ID3D11PixelShader* _ps, ID3D11InputLayout* _il, 
		ID3D11Buffer* _vb, ID3D11Buffer* _vb2,
		ID3D11SamplerState* _pSampler
	)override;
	
	
	bool Render_LateUpdate   (ID3D11DeviceContext* _pD3DeviceContext,  ID3D11RasterizerState* _pRasterizerState)override;
	bool Render_2D			 (Grahpics2D* _pGrahpics2D, DirectXAdapter* _pAdapter)override;
	bool Render_End			 (Grahpics2D* _pGrahpics2D, IDXGISwapChain* _pSwapChain)override;
	
public:
	void DrawState();
	
public:
	ID3D11DepthStencilState* GetDepthStencil_State();
	ID3D11Texture2D*		 GetDepthStencil_Buffer();
	ID3D11DepthStencilView*  GetDepthStencil_View();
	D3D11_VIEWPORT			 GetD3D11ViewPort();
	ID3D11RenderTargetView*	 GetRenderTargetView();



};

