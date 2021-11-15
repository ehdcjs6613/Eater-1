#pragma once


/// <summary>
/// 랜더타겟과 뎁스스텐실 쉐이더 리소스뷰를 관리하기위한 인터페이스 클래스
/// 일단 4개의 그래픽엔진을 붙이기 위해 만들어놓은것이기 때문에 나중에 누군가 바꿀것(서규황)
/// </summary>


struct ID3D11DepthStencilView;
struct ID3D11RenderTargetView;
struct ID3D11ShaderResourceView;
struct D3D11_VIEWPORT;
struct ID3D11Texture2D;

class TextureBase
{
public:
	TextureBase();
	~TextureBase();

	void Initialize(ID3D11Device* Divice, ID3D11DeviceContext* Context);
	void Reset(int TextureSizeX = 256,int TextureSizeY= 256);

	//기본값을 랜더타겟과 뎁스스텐실 쉐이데리소스뷰를 만든다
	void Create(int ViewstartX, int ViewStartY, int ViewWidth, int ViewHeight,int TextureSizeX = 256,int TextureSizeY=256);

	void CreateViewPort(int startX, int StartY,int Width, int Height);

	void Delete();

	///Get
	ID3D11DepthStencilView*		GetDSV();
	ID3D11RenderTargetView*		GetRTV();
	ID3D11ShaderResourceView*	GetSRV();
	D3D11_VIEWPORT*				GetView();
protected:
	//디바이스 와 컨텍스트
	ID3D11Device*			m_Device;
	ID3D11DeviceContext*	m_Context;

	//뎁스 스텐실
	ID3D11DepthStencilView*		m_DSV;
	//랜더 타겟뷰
	ID3D11RenderTargetView*		m_RTV;
	//쉐이더 리소스
	ID3D11ShaderResourceView*	m_SRV;
	//뷰포트
	D3D11_VIEWPORT*				m_View;

	//뷰포트 사이즈
	int m_StartX;
	int m_StartY;
	int m_Width;
	int m_Height;

	//텍스쳐 사이즈 저장
	int m_TextureSizeX;
	int m_TextureSizeY;
protected:
	ID3D11Texture2D* CreateBasic_RenderTarget_Texture2D(int SizeX,int SizeY);
	ID3D11Texture2D* CreateBasic_DepthStencil_Texture2D(int SizeX, int SizeY);
	void Create_ShaderResourceView(ID3D11Texture2D* Tex);
};