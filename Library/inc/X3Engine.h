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

#if _DEBUG

#ifdef _DEBUG
#define X3Engine_DLL __declspec(dllexport)
#else 
#define X3Engine_DLL __declspec(dllimport)
#endif // X3Engine_DLL __declspec(dllimport)

#else
#ifdef 1
#define X3Engine_DLL __declspec(dllexport)
#else 
#define X3Engine_DLL __declspec(dllimport)
#endif // X3Engine_DLL __declspec(dllimport)

#endif

//class __declspec(dllimport) GraphicEngine;

#include <d3dcommon.h>
#include <string>
#include <queue>

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
	//DirectXSwapChain*		m_pSwapChain;		///
///---------------------------------------------///
	DirectXRasterizerState* m_pRasterizerState; ///
	DirectXRasterizerState* m_pRasterizerSolid; ///
	DirectXRasterizerState* m_pRasterizerWire;  ///
///---------------------------------------------///
	DirectXAdapter*			m_pAdapter;			///
///---------------------------------------------///
	
	D3D_FEATURE_LEVEL	    m_FeatureLevel;


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
	virtual Indexbuffer*   CreateIndexBuffer(ParserData::Model* mModel) override;	//�ε��� ���۸� ������ش�
	virtual Vertexbuffer*  CreateVertexBuffer(ParserData::Model* mModel) override;	//���ؽ� ���۸� ������ش�
	virtual TextureBuffer* CreateTextureBuffer(std::string path) override;									//�ؽ��ĸ� ������ش�
	virtual void		   OnReSize(int Change_Width, int Change_Height) override;			//��������
	virtual void		   Delete() override;

	/// �������� �Ѵ� �Ž� ���������� ����Ʈ, �۷ι� ������
	virtual void		  Render(std::queue<MeshData*>* meshList, GlobalData* global) override;

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
	bool TestScene();
private:
	// ��Ʈ������ �������Ľ� ������Ʈ�� ����.
	ID3D11DepthStencilState* NormalDSS = nullptr;

	ID3D11RasterizerState* mWireframeRS = nullptr;
	ID3D11RasterizerState* mSolidRS = nullptr;
	//-----------------------------------

public:

};

