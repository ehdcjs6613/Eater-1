#pragma once
/// <summary>
/// 렌더러의 기능을 지닌 인터페이스이다.
/// </summary>
__interface IRenderableFunc
{
	bool Render_Begin (ID3D11DeviceContext* _pD3DeviceContext) = 0;
	bool Render_Update(ID3D11DeviceContext* _pD3DeviceContext) = 0;
	bool Render_End	  (ID3D11DeviceContext* _pD3DeviceContext) = 0;
};
/// <summary>
/// 이제 어떻게 그릴것인가..
/// </summary>

class XRenderer : public IRenderableFunc
{
private:
	ID3D11RenderTargetView*  m_pRenderTarget[5];
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
	bool Render_Begin (ID3D11DeviceContext* _pD3DeviceContext);
	bool Render_Update(ID3D11DeviceContext* _pD3DeviceContext);
	bool Render_End   (ID3D11DeviceContext* _pD3DeviceContext);
	
public:
	void Render_State();
public:
	ID3D11DepthStencilState* GetDepthStencil_State();
	ID3D11Texture2D*		 GetDepthStencil_Buffer();
	ID3D11DepthStencilView*  GetDepthStencil_View();
	D3D11_VIEWPORT			 GetD3D11ViewPort();
	ID3D11RenderTargetView*	 GetRenderTargetView();
};

