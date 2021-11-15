#include "d3d11.h"
#include "TextureBase.h"


TextureBase::TextureBase()
{
	m_DSV	= nullptr;
	m_RTV	= nullptr;
	m_SRV	= nullptr;
	m_View	= nullptr;

	m_Device	= nullptr;
	m_Context	= nullptr;

	m_StartX	= 0;
	m_StartY	= 0;
	m_Width		= 0;
	m_Height	= 0;

	m_TextureSizeX = 256;
	m_TextureSizeY = 256;
}

TextureBase::~TextureBase()
{
	m_DSV = nullptr;
	m_RTV = nullptr;
	m_SRV = nullptr;

	m_Device	= nullptr;
	m_Context	= nullptr;
	Delete();
}

void TextureBase::Initialize(ID3D11Device* Divice, ID3D11DeviceContext* Context)
{
	m_Device	= Divice;
	m_Context	= Context;
}

void TextureBase::Reset(int TextureSizeX, int TextureSizeY)
{
	///이건 나중에
	//텍스쳐를 삭제하고 크기조절후 다시생성
	//SizeX = TextureSizeX;
	//SizeY = TextureSizeY;
	//
	//Delete();
	//Create();
}

void TextureBase::Create(int startX, int StartY, int Width, int Height,int TextureSizeX, int TextureSizeY)
{
	m_StartX	= startX;
	m_StartY	= StartY;
	m_Width		= Width;
	m_Height	= Height;

	//랜더타겟과 뎁스스텐실의 기본 텍스쳐 2D를 생성해준다
	ID3D11Texture2D* RenderTarget_Texture2D = CreateBasic_RenderTarget_Texture2D(TextureSizeX, TextureSizeY);
	ID3D11Texture2D* DepthStencil_Texture2D = CreateBasic_DepthStencil_Texture2D(TextureSizeX, TextureSizeY);
	

	///생성
	m_Device->CreateRenderTargetView(RenderTarget_Texture2D, 0, &m_RTV);	//랜더타겟
	m_Device->CreateDepthStencilView(DepthStencil_Texture2D, 0, &m_DSV);	//뎁스 스텐실
	Create_ShaderResourceView(RenderTarget_Texture2D);					//쉐이더 리소스뷰

	//뷰포트 생성
	CreateViewPort(startX, StartY, Width, Height);


	//Texture2D는 삭제
	if (RenderTarget_Texture2D != nullptr)
	{
		RenderTarget_Texture2D->Release();
	}

	if (DepthStencil_Texture2D != nullptr)
	{
		DepthStencil_Texture2D->Release();
	}
}

void TextureBase::CreateViewPort(int startX, int StartY, int Width, int Height)
{
	//뷰포트를 생성한다
	m_View = new D3D11_VIEWPORT();
	m_View->TopLeftX = startX;
	m_View->TopLeftY = startX;
	m_View->Width = static_cast<float>(Width);
	m_View->Height = static_cast<float>(Height);
	m_View->MinDepth = 0.0f;
	m_View->MaxDepth = 1.0f;
}

void TextureBase::Delete()
{
	//뎁스 스텐실 삭제
	if (m_DSV != nullptr)
	{
		m_DSV->Release();
	}

	//랜더타겟 리소스뷰 삭제
	if (m_RTV != nullptr)
	{
		m_RTV->Release();
	}

	//쉐이더 리소스뷰 삭제
	if (m_SRV != nullptr)
	{
		m_SRV->Release();
	}

	if (m_View != nullptr)
	{
		delete m_View;
	}
}

ID3D11DepthStencilView* TextureBase::GetDSV()
{
	return m_DSV;
}

ID3D11RenderTargetView* TextureBase::GetRTV()
{
	return m_RTV;
}

ID3D11ShaderResourceView* TextureBase::GetSRV()
{
	return m_SRV;
}

D3D11_VIEWPORT* TextureBase::GetView()
{
	return m_View;
}

ID3D11Texture2D* TextureBase::CreateBasic_RenderTarget_Texture2D(int SizeX, int SizeY)
{
	D3D11_TEXTURE2D_DESC texDesc;
	texDesc.Width = SizeX;	//텍스쳐가로 
	texDesc.Height = SizeY;	//텍스쳐세로
	texDesc.MipLevels	= 1;							//밉맵수준 (깊이 스텐실 버퍼를 위한텍스쳐에서는 하나만있으면된다)
	texDesc.ArraySize	= 1;							//택스쳐 배열의택스쳐 개수 (깊이 스텐실 버퍼를 위한텍스쳐에서는 하나만있으면된다)
	texDesc.Format		= DXGI_FORMAT_R8G8B8A8_UNORM;	//픽셀의 형식을 뜻함
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;

	//랜더타겟에 사용될 텍스쳐 2D를 생성함
	ID3D11Texture2D* Tex;
	m_Device->CreateTexture2D(&texDesc, 0,&Tex);

	return Tex;
}

ID3D11Texture2D* TextureBase::CreateBasic_DepthStencil_Texture2D(int SizeX, int SizeY)
{
	D3D11_TEXTURE2D_DESC depthDesc;
	depthDesc.Width		= SizeX;				//텍스쳐가로 
	depthDesc.Height	= SizeY;				//텍스쳐세로
	depthDesc.MipLevels = 1;					//밉맵수준 (깊이 스텐실 버퍼를 위한텍스쳐에서는 하나만있으면된다)
	depthDesc.ArraySize = 1;					//택스쳐 배열의택스쳐 개수 (깊이 스텐실 버퍼를 위한텍스쳐에서는 하나만있으면된다)
	depthDesc.Format = DXGI_FORMAT_D32_FLOAT;	//픽셀의 형식을 뜻함
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthDesc.CPUAccessFlags = 0;
	depthDesc.MiscFlags = 0;

	//랜더타겟에 사용될 텍스쳐 2D를 생성함
	ID3D11Texture2D* Tex2D;
	m_Device->CreateTexture2D(&depthDesc, 0, &Tex2D);

	return Tex2D;
}

void TextureBase::Create_ShaderResourceView(ID3D11Texture2D* Tex)
{
	//쉐이더 리소스뷰를 생성
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.TextureCube.MostDetailedMip = 0;
	srvDesc.TextureCube.MipLevels = -1;

	m_Device->CreateShaderResourceView(Tex, &srvDesc, &m_SRV);
}
