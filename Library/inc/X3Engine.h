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

class SharedRenderData;

class Grahpics2D;

//�׸��⸦ ���� ��������  Ŭ����
class Vertexbuffer;
class Indexbuffer;
class TextureBuffer;
class MeshData;
class GlobalData;






#include <d3d11.h>
#include <d3dcommon.h>
#include <DirectXMath.h>

#include <queue>
#include <string>

#include "WJDefine.h"
#include "GraphicsEngine.h"
#include "XShader.h"

class X3Engine : public  GraphicEngine 
{
private:
	//
///-----------[������ ���ϴ� ������]------------///
	HWND					m_hWnd;				///
///------------------------------------------------	
	DirectXDevice*			m_pDevice;			///
	DirectXDeviceContext*	m_pDeviceContext;	///
	//D3D11_VIEWPORT*			m_ViewPort;			///
///---------------------------------------------///
	DirectXRasterizerState* m_pRasterizerState; ///
	DirectXRasterizerState* m_pRasterizerSolid; ///
	DirectXRasterizerState* m_pRasterizerWire;  ///
///---------------------------------------------///
	DirectXAdapter*			m_pAdapter;			///
///---------------------------------------------///
	
	D3D_FEATURE_LEVEL	    m_FeatureLevel;


	ID3D11Device*			m_pNewDevice;
	ID3D11DeviceContext*	m_pNewDeviceContext;
	 D3D11_VIEWPORT*		m_pNewViewPort;


private:
	//������ ���
	XRenderer*				m_pRenderer;
	

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
	virtual void SetViewPort(void* VPT); //����Ÿ�ٺ�, �������ٽ�,����Ʈ
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
	//Microsoft::WRL::ComPtr<ID3D10Blob> m_pVertexShaderBuffer;
	IDXGISwapChain* m_pSwapChain;
	XVertexShader m_XVertexShader;
	XPixelShader  m_XPexelShader;
public:
	//test
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pVertexBuffer2;
	bool TestScene();
private:
	
	//-----------------------------------

public:
	ID3D11SamplerState* m_pSamplerState;
	ID3D11SamplerState* CreateDXSamplerState();


};

