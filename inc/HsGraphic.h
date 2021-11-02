#pragma once

#include "GraphicsEngine.h"
#include "HsEngineHelper.h"

#ifdef HSGRAPHIC_INTERFACE
#define HS_GRAPHICDLL __declspec(dllexport)
#else
#define HS_GRAPHICDLL __declspec(dllimport)
#endif


class HsGraphic : public GraphicEngine
{
public:
	HS_GRAPHICDLL HsGraphic();
	virtual ~HsGraphic();



	
	virtual HS_GRAPHICDLL void Initialize(HWND _hWnd, int screenWidth, int screenHeight) override;
	virtual HS_GRAPHICDLL void OnReSize(int Change_Width, int Change_Height) override;
	virtual HS_GRAPHICDLL void Render(std::queue<MeshData*>* meshList, GlobalData* global) override;
	virtual HS_GRAPHICDLL void Delete() override;

	//�ؽ��� ���۸�����
	virtual HS_GRAPHICDLL TextureBuffer* CreateTextureBuffer(std::string path) override;
	//�ε��� ���۸� ����
	virtual HS_GRAPHICDLL Indexbuffer*	CreateIndexBuffer(ParserData::Model* mModel) override;
	//���ؽ� ���۸� ����
	virtual HS_GRAPHICDLL Vertexbuffer* CreateVertexBuffer(ParserData::Model* mModel) override;
private:
	void CreateRenderTarget();	//����Ÿ�� �������ٽ� ����Ʈ�� �����Ѵ�
	void CreateRenderState();	//����Ÿ�� ���¸� �������ش�
	void BeginRender();			//������ ����
	void EngineRender();		//���� ������
	void EndRender();			//������ ����
	int GetAspectRatio();		//ȭ����� ��Ⱦ�� ����
private:

	///���� ������
	HWND					hwnd;				//������ �ڵ�
	ID3D11Device*			m_device;			//����̽�
	ID3D11DeviceContext*	m_deviceContext;	//����̽� ���ؽ�Ʈ
	ID3D11RenderTargetView* m_renderTargetView;	//���� Ÿ��
	ID3D11DepthStencilView* mDepthStencilView;	//���� ���ٽǺ�
	D3D11_VIEWPORT			mScreenViewport;	//����Ʈ
	IDXGISwapChain*			mSwapChain;			//����ü��	


	//������ ������
	int WinSizeX;	//������ ������ ����
	int WinSizeY;	//������ ������ ����


	//������ ���
	ID3D11RasterizerState* mWireframe;
	ID3D11RasterizerState* mSolid;
};