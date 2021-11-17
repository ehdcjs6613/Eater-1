#pragma once


/// <summary>
/// ����Ÿ�ٰ� �������ٽ� ���̴� ���ҽ��並 �����ϱ����� �������̽� Ŭ����
/// �ϴ� 4���� �׷��ȿ����� ���̱� ���� �����������̱� ������ ���߿� ������ �ٲܰ�(����Ȳ)
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

	//�⺻���� ����Ÿ�ٰ� �������ٽ� ���̵����ҽ��並 �����
	void Create(int ViewstartX, int ViewStartY, int ViewWidth, int ViewHeight,int TextureSizeX = 256,int TextureSizeY=256);

	void CreateViewPort(int startX, int StartY,int Width, int Height);

	void Delete();

	///Get
	ID3D11DepthStencilView*		GetDSV();
	ID3D11RenderTargetView*		GetRTV();
	ID3D11ShaderResourceView*	GetSRV();
	D3D11_VIEWPORT*				GetView();
protected:
	//����̽� �� ���ؽ�Ʈ
	ID3D11Device*			m_Device;
	ID3D11DeviceContext*	m_Context;

	//���� ���ٽ�
	ID3D11DepthStencilView*		m_DSV;
	//���� Ÿ�ٺ�
	ID3D11RenderTargetView*		m_RTV;
	//���̴� ���ҽ�
	ID3D11ShaderResourceView*	m_SRV;
	//����Ʈ
	D3D11_VIEWPORT*				m_View;

	//����Ʈ ������
	int m_StartX;
	int m_StartY;
	int m_Width;
	int m_Height;

	//�ؽ��� ������ ����
	int m_TextureSizeX;
	int m_TextureSizeY;
protected:
	ID3D11Texture2D* CreateBasic_RenderTarget_Texture2D(int SizeX,int SizeY);
	ID3D11Texture2D* CreateBasic_DepthStencil_Texture2D(int SizeX, int SizeY);
	void Create_ShaderResourceView(ID3D11Texture2D* Tex);
};