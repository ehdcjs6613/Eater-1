#include "d3d11.h"
#include "TextureBase.h"

TextureBase::TextureBase()
{
	mDSV = nullptr;
	mRTV = nullptr;
	mSRV = nullptr;

	Device		= nullptr;
	mContext	= nullptr;
}

TextureBase::~TextureBase()
{
	mDSV = nullptr;
	mRTV = nullptr;
	mSRV = nullptr;

	Device	 = nullptr;
	mContext = nullptr;
}

void TextureBase::Reset(int TextureSizeX, int TextureSizeY)
{
	//�ؽ��ĸ� �����ϰ� ũ�������� �ٽû���
	SizeX = TextureSizeX;
	SizeY = TextureSizeY;

	Delete();
	Create();
}

void TextureBase::Create()
{
	//����Ÿ�ٰ� �������ٽ��� �⺻ �ؽ��� 2D�� �������ش�
	ID3D11Texture2D* RenderTarget_Texture2D = CreateBasic_RenderTarget_Texture2D();
	ID3D11Texture2D* DepthStencil_Texture2D = CreateBasic_DepthStencil_Texture2D();
	

	///����
	Device->CreateRenderTargetView(RenderTarget_Texture2D, 0, &mRTV);	//����Ÿ��
	Device->CreateDepthStencilView(DepthStencil_Texture2D, 0, &mDSV);	//���� ���ٽ�
	Create_ShaderResourceView(RenderTarget_Texture2D);					//���̴� ���ҽ���


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

void TextureBase::Create(D3D11_TEXTURE2D_DESC& RTV, D3D11_TEXTURE2D_DESC& DSV, D3D11_SHADER_RESOURCE_VIEW_DESC& SRV)
{
	ID3D11Texture2D* R = nullptr;
	ID3D11Texture2D* D = nullptr;

	Device->CreateTexture2D(&RTV, 0, &R);
	Device->CreateTexture2D(&DSV, 0, &D);
	Device->CreateShaderResourceView(R, &SRV, &mSRV);


	if (R != nullptr)
	{
		R->Release();
	}
	
	if(D != nullptr)
	{
		D->Release();
	}
}

void TextureBase::Delete()
{
	//���� ���ٽ� ����
	if (mDSV != nullptr)
	{
		mDSV->Release();
	}

	//����Ÿ�� ���ҽ��� ����
	if (mRTV != nullptr)
	{
		mRTV->Release();
	}

	//���̴� ���ҽ��� ����
	if (mSRV != nullptr)
	{
		mSRV->Release();
	}
}

const ID3D11DepthStencilView* TextureBase::GetDSV()
{
	return mDSV;
}

const ID3D11RenderTargetView* TextureBase::GetRTV()
{
	return mRTV;
}

const ID3D11ShaderResourceView* TextureBase::GetSRV()
{
	return mSRV;
}

ID3D11Texture2D* TextureBase::CreateBasic_RenderTarget_Texture2D()
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
	Device->CreateTexture2D(&texDesc, 0,&Tex);

	return Tex;
}

ID3D11Texture2D* TextureBase::CreateBasic_DepthStencil_Texture2D()
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
	Device->CreateTexture2D(&depthDesc, 0, &Tex2D);

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

	Device->CreateShaderResourceView(Tex, &srvDesc, &mSRV); 
}
