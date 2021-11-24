#pragma once



//    DirectX���� Ŭ����
//	  ��ġ�� ������ D		eviceŬ����
class DirectXDevice;
//	  ��ġ�� �׸��⸦ ����� DeviceContextŬ����
class DirectXDeviceContext;
//	  ����ü���� Ŭ����
class DirectXSwapChain;
//	  �׷���ī��(���,����ī��) ���� Ŭ����
class DirectXAdapter;

//	  ��� �׸����� �����Ͷ����� Ŭ����
class DirectXRasterizerState;
//	  ������ Ŭ����
class XRenderer;
//	  ���÷� ������Ʈ Ŭ����
class DirectXSamplerState;

class SharedRenderData;

class Grahpics2D;

//�׸��⸦ ���� ��������  Ŭ����
class Vertexbuffer;
class Indexbuffer;
class TextureBuffer;
class MeshData;
class GlobalData;
//���α׸���
class ViewGrid;






#include <d3d11.h>
#include <d3dcommon.h>
#include <DirectXMath.h>

#include <queue>
#include <string>

#include "WJDefine.h"
#include "GraphicsEngine.h"
#include "XShader.h"

/// <summary>
/// ���� ������ ����?
/// </summary>
class X3Engine : public  GraphicEngine
{
private:
	FLOAT					 m_ArrColor[4];
	D3D11_VIEWPORT*			 m_ViewPort;
private:
	//
///-----------[������ ���ϴ� ������]------------///
	HWND					m_hWnd;				///
///------------------------------------------------	
	DirectXDevice* m_pDevice;					///
	DirectXDeviceContext* m_pDeviceContext;		///
///---------------------------------------------///
	DirectXRasterizerState* m_pRasterizerState; ///
	DirectXRasterizerState* m_pRasterizerSolid; ///
	DirectXRasterizerState* m_pRasterizerWire;  ///
///---------------------------------------------///
	DirectXAdapter*			m_pAdapter;			///
///---------------------------------------------///
private:
	D3D_FEATURE_LEVEL	    m_FeatureLevel;

	ID3D11Texture2D*		 m_pDepthStencil_Buffer;
	ID3D11DepthStencilState* m_pDepthStencil_State;
	ID3D11DepthStencilView*  m_pDepthStencil_View;
private:
	//����� �����Ƿ� �ٽ��ѹ� ���� ��? Ŭ��������
	DirectXSwapChain*		m_pDirectXSwapChain;
	DirectXRenderTargeter*	m_pRenderTargeter;
	DirectXSamplerState*	m_pSamplerState;

	Grahpics2D*	m_pGrahpics2D;

private:


	DirectX::XMMATRIX		m_ProjectionMatrix;
	DirectX::XMMATRIX		m_WorldMatrix;
	DirectX::XMMATRIX		m_OtherMatrix;
private:
	//int					  m_iWidth;
	//int					  m_iHeight;
	int						m_videoCardMemory;
public:

public:
	//�⺻���� ������
	X3Engine_DLL X3Engine();
	//�� ������ �Ʒ��� ����
	X3Engine_DLL virtual ~X3Engine() final;
public:
#pragma region Parents Overriding Function List

	///GraphicEngine class�κ��� ��ӵ� �Լ���

	///���� �����ʿ��� ������ �ڵ��� �Ѱ��ٰ���
	X3Engine_DLL virtual void Initialize(HWND _hWnd, int _iWidth, int _iHeight) override;


	///�׷��� ������ ���ӿ������� �ְ�޾ƾ��� �Լ���


	X3Engine_DLL virtual Indexbuffer* CreateIndexBuffer(ParserData::Mesh* mModel)	override;	//�ε��� ���۸� ������ش�
	X3Engine_DLL virtual Vertexbuffer* CreateVertexBuffer(ParserData::Mesh* mModel) override;	//���ؽ� ���۸� ������ش�
	X3Engine_DLL virtual TextureBuffer* CreateTextureBuffer(std::string path) override;									//�ؽ��ĸ� ������ش�
	X3Engine_DLL virtual void		   OnReSize(int Change_Width, int Change_Height) override;			//��������
	X3Engine_DLL virtual void		   Delete() override;

	/// �������� �Ѵ� �Ž� ���������� ����Ʈ, �۷ι� ������
	X3Engine_DLL virtual void		  Render(std::queue<MeshData*>* meshList, GlobalData* global) override;


	/// ����Ÿ�ٿ� �ش��ϴ� �����͸� �Ѱ��ٰ��� 
	/// (��� ����̽��� �Ѿ�� ��Ƽ�׷��ȿ��������� �Ѱ��൵�ɵ�)
	virtual void SetViewPort(void* VPT);//����Ÿ�ٺ�, �������ٽ�,����Ʈ
	virtual void SetDevice(void* Devie, void* DevieContext); //����̽�,���ؽ�Ʈ


#pragma endregion Parents Overriding Function List
public:
	//���� ������ �Լ�
	void CreateRenderState();
	void DrawSystemStatus();

	/// �ؽ��ĸ� ����� �κ�
	void SetTextureSRV(SharedRenderData* _SRD);

	void Release();

public:
	void InitializeShaders();


private:
	////�������̴��� �����ϱ� ���� ������ �߰�
	XVertexShader m_XVertexShader;
	XPixelShader  m_XPexelShader;
public:
	//test
	ID3D11Buffer* m_pVertexBuffer;

private:
	HRESULT BeginRender();
	HRESULT LoopRender();
	HRESULT EndRender();
	//-----------------------------------


	ViewGrid* m_pViewGrid;
private:
	ID3DX11Effect* m_FX;
	ID3DX11EffectTechnique* mTech;
	ID3DX11EffectMatrixVariable* mfxWorldViewProj;

	ID3D11InputLayout* mInputLayout;
	// ��Ʈ������ �������Ľ� ������Ʈ�� ������ �ƴ�.
	ID3D11DepthStencilState* NormalDSS;

	DirectX::SimpleMath::Matrix mWorld;	// Transform Matrix
	DirectX::SimpleMath::Matrix mView;
	DirectX::SimpleMath::Matrix mProj;

	ID3D11Buffer* Render_VB = nullptr;
	ID3D11Buffer* Render_IB = nullptr;
	// Buffer ����
	UINT Vertex_Buffer_Stride = 0;
	UINT Vertex_Buffer_Offset = 0;
	// WVP ����
	DirectX::SimpleMath::Matrix Mul_WVP;		// W * V * P
	DirectX::SimpleMath::Matrix World_Inverse;	// ���� �����
	DirectX::SimpleMath::Matrix World_Inverse_Transpose;
};

