#pragma once


/// <summary>
/// ����Ÿ�ٰ� �������ٽ� ���̴� ���ҽ��並 �����ϱ����� �������̽� Ŭ����
/// </summary>


struct ID3D11DepthStencilView;
struct ID3D11RenderTargetView;
struct ID3D11ShaderResourceView;

class TextureBase
{
public:
	TextureBase();
	~TextureBase();
	void Reset(int TextureSizeX = 256,int TextureSizeY= 256);

	void Create();
	void Create(D3D11_TEXTURE2D_DESC& RTV, D3D11_TEXTURE2D_DESC& DSV , D3D11_SHADER_RESOURCE_VIEW_DESC& SRV);
	void Delete();

	///Get
	const ID3D11DepthStencilView*	 GetDSV();
	const ID3D11RenderTargetView*	 GetRTV();
	const ID3D11ShaderResourceView*	 GetSRV();
protected:
	//����̽� �� ���ؽ�Ʈ
	ID3D11Device*			Device;
	ID3D11DeviceContext*	mContext;

	//���� ���ٽ�
	ID3D11DepthStencilView*		mDSV;
	//���� Ÿ�ٺ�
	ID3D11RenderTargetView*		mRTV;
	//���̴� ���ҽ�
	ID3D11ShaderResourceView*	mSRV;
	
	//������
	int SizeX;
	int SizeY;
private:
	ID3D11Texture2D* CreateBasic_RenderTarget_Texture2D();
	ID3D11Texture2D* CreateBasic_DepthStencil_Texture2D();
	void Create_ShaderResourceView(ID3D11Texture2D* Tex);
};