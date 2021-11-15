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
	///�̰� ���߿�
	//�ؽ��ĸ� �����ϰ� ũ�������� �ٽû���
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

	//����Ÿ�ٰ� �������ٽ��� �⺻ �ؽ��� 2D�� �������ش�
	ID3D11Texture2D* RenderTarget_Texture2D = CreateBasic_RenderTarget_Texture2D(TextureSizeX, TextureSizeY);
	ID3D11Texture2D* DepthStencil_Texture2D = CreateBasic_DepthStencil_Texture2D(TextureSizeX, TextureSizeY);
	

	///����
	m_Device->CreateRenderTargetView(RenderTarget_Texture2D, 0, &m_RTV);	//����Ÿ��
	m_Device->CreateDepthStencilView(DepthStencil_Texture2D, 0, &m_DSV);	//���� ���ٽ�
	Create_ShaderResourceView(RenderTarget_Texture2D);					//���̴� ���ҽ���

	//����Ʈ ����
	CreateViewPort(startX, StartY, Width, Height);


	//Texture2D�� ����
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
	//����Ʈ�� �����Ѵ�
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
	//���� ���ٽ� ����
	if (m_DSV != nullptr)
	{
		m_DSV->Release();
	}

	//����Ÿ�� ���ҽ��� ����
	if (m_RTV != nullptr)
	{
		m_RTV->Release();
	}

	//���̴� ���ҽ��� ����
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
	texDesc.Width = SizeX;	//�ؽ��İ��� 
	texDesc.Height = SizeY;	//�ؽ��ļ���
	texDesc.MipLevels	= 1;							//�Ӹʼ��� (���� ���ٽ� ���۸� �����ؽ��Ŀ����� �ϳ���������ȴ�)
	texDesc.ArraySize	= 1;							//�ý��� �迭���ý��� ���� (���� ���ٽ� ���۸� �����ؽ��Ŀ����� �ϳ���������ȴ�)
	texDesc.Format		= DXGI_FORMAT_R8G8B8A8_UNORM;	//�ȼ��� ������ ����
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.CPUAccessFlags = 0;
	texDesc.MiscFlags = 0;

	//����Ÿ�ٿ� ���� �ؽ��� 2D�� ������
	ID3D11Texture2D* Tex;
	m_Device->CreateTexture2D(&texDesc, 0,&Tex);

	return Tex;
}

ID3D11Texture2D* TextureBase::CreateBasic_DepthStencil_Texture2D(int SizeX, int SizeY)
{
	D3D11_TEXTURE2D_DESC depthDesc;
	depthDesc.Width		= SizeX;				//�ؽ��İ��� 
	depthDesc.Height	= SizeY;				//�ؽ��ļ���
	depthDesc.MipLevels = 1;					//�Ӹʼ��� (���� ���ٽ� ���۸� �����ؽ��Ŀ����� �ϳ���������ȴ�)
	depthDesc.ArraySize = 1;					//�ý��� �迭���ý��� ���� (���� ���ٽ� ���۸� �����ؽ��Ŀ����� �ϳ���������ȴ�)
	depthDesc.Format = DXGI_FORMAT_D32_FLOAT;	//�ȼ��� ������ ����
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthDesc.CPUAccessFlags = 0;
	depthDesc.MiscFlags = 0;

	//����Ÿ�ٿ� ���� �ؽ��� 2D�� ������
	ID3D11Texture2D* Tex2D;
	m_Device->CreateTexture2D(&depthDesc, 0, &Tex2D);

	return Tex2D;
}

void TextureBase::Create_ShaderResourceView(ID3D11Texture2D* Tex)
{
	//���̴� ���ҽ��並 ����
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.TextureCube.MostDetailedMip = 0;
	srvDesc.TextureCube.MipLevels = -1;

	m_Device->CreateShaderResourceView(Tex, &srvDesc, &m_SRV);
}
