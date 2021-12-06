#pragma once

#include "HsGraphicDLL.h"
#include "../KHGraphic/Export/GraphicsEngine.h"
#include "d3d11.h"

class ShaderManager;
class RenderingManager;
class GraphicDebugManager;
class TextureBuffer;
class Indexbuffer;
class Vertexbuffer;

class HsGraphic : public GraphicEngine
{
public:
	HS_GRAPHICDLL HsGraphic();
	virtual HS_GRAPHICDLL ~HsGraphic();


	virtual HS_GRAPHICDLL void Initialize(HWND _hWnd, int screenWidth, int screenHeight) override;
	virtual HS_GRAPHICDLL void OnReSize(int Change_Width, int Change_Height) override;
	virtual HS_GRAPHICDLL void Render(std::queue<MeshData*>* meshList, GlobalData* global) override;
	virtual HS_GRAPHICDLL void Delete() override;
	virtual HS_GRAPHICDLL void SetViewPort(void* VPT, int Change_Width, int Change_Height);
	virtual HS_GRAPHICDLL void SetDevice(void* Devie, void* DevieContext);

	//�ؽ��� ���۸�����
	virtual HS_GRAPHICDLL TextureBuffer* CreateTextureBuffer(std::string path) override;
	//�ε��� ���۸� ����
	virtual HS_GRAPHICDLL Indexbuffer*	CreateIndexBuffer(ParserData::Mesh* mModel) override;
	//���ؽ� ���۸� ����
	virtual HS_GRAPHICDLL Vertexbuffer* CreateVertexBuffer(ParserData::Mesh* mModel) override;

	ID3D11RenderTargetView* GetEngineRTV();
	ID3D11DepthStencilView* GetEngineDSV();
private:
	void CreateRenderTarget();	//����Ÿ�� �������ٽ� ����Ʈ�� �����Ѵ�
	void CreateDevice();		//������ ����̽��� �������ش�
	void BeginRender();			//������ ����
	void EndRender();			//������ ����
	
	Vertexbuffer* CreateBasicVertexBuffer(ParserData::Mesh* mModel);
	Vertexbuffer* CreateSkinngingVertexBuffer(ParserData::Mesh* mModel);
private:

	///���� ������
	HWND					hwnd;				//������ �ڵ�
	ID3D11Device*			Device;				//����̽�
	ID3D11DeviceContext*	DeviceContext;		//����̽� ���ؽ�Ʈ
	ID3D11RenderTargetView* mRenderTargetView;	//���� Ÿ��
	ID3D11DepthStencilView* mDepthStencilView;	//���� ���ٽǺ�
	D3D11_VIEWPORT*			mScreenViewport;	//����Ʈ
	IDXGISwapChain*			mSwapChain;			//����ü��	


	//������ ������
	int WinSizeX;	//������ ������ ����
	int WinSizeY;	//������ ������ ����


	//������ ���
	ID3D11RasterizerState* mWireframe;
	ID3D11RasterizerState* mSolid;

	//�Ŵ�����
	ShaderManager*			mShaderManager;
	RenderingManager*		mRenderManager;
	GraphicDebugManager*	mDebugManager;
};