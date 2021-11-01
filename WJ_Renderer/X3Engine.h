#pragma once
#include "GraphicsEngine.h"

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


class X3Engine : public GraphicEngine
{
private:
	//
///-----------[������ ���ϴ� ������]------------///
	HWND					m_hWnd;				///
///------------------------------------------------	
	DirectXDevice*			m_pDevice;			///
	DirectXDeviceContext*	m_pDeviceContext;	///
	DirectXSwapChain*		m_pSwapChain;		///
///---------------------------------------------///
	DirectXRasterizerState* m_pRasterizerState; ///
	DirectXRasterizerState* m_pRasterizerSolid; ///
	DirectXRasterizerState* m_pRasterizerWire;  ///
///---------------------------------------------///
	DirectXAdapter*			m_pAdapter;			///
///---------------------------------------------///
	
	D3D_FEATURE_LEVEL	    featureLevel;
private:
	//������ ���
	XRenderer*				m_pRenderer;



private:
	int					  m_iWidth;
	int					  m_iHeight;
	int					  m_videoCardMemory;
public:

public:
	//�⺻���� ������
	X3Engine();
	//�� ������ �Ʒ��� ����
	virtual ~X3Engine() final;
public:
#pragma region Parents Overriding Function List

	///GraphicEngine class�κ��� ��ӵ� �Լ���
	
	///���� �����ʿ��� ������ �ڵ��� �Ѱ��ٰ���
	virtual void Initialize(HWND _hWnd, int screenWidth, int screenHeight) override;


	///�׷��� ������ ���ӿ������� �ְ�޾ƾ��� �Լ���
	virtual Indexbuffer*  CreateIndexBuffer(ParserData::Model* mModel) override;	//�ε��� ���۸� ������ش�
	virtual Vertexbuffer* CreateVertexBuffer(ParserData::Model* mModel) override;	//���ؽ� ���۸� ������ش�
	virtual void		  CreateTextureBuffer() override;									//�ؽ��ĸ� ������ش�
	virtual void		  OnReSize(float Change_Width, float Change_Height) override;			//��������


	/// �������� �Ѵ� �Ž� ���������� ����Ʈ, �۷ι� ������
	virtual void		  Render(std::queue<MeshData*>* meshList, GlobalData* global) override;

#pragma endregion Parents Overriding Function List
public:
	//���� ������ �Լ�
	void CreateRenderState();
};

