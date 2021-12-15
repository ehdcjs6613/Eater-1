#pragma once

#include "HsGraphicDLL.h"
#include "GraphicsEngine.h"

class ShaderManager;
class RenderingManager;
class GraphicDebugManager;
class TextureBuffer;
class Indexbuffer;
class Vertexbuffer;

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct D3D11_VIEWPORT;
struct IDXGISwapChain;
struct ID3D11RasterizerState;

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
	
	virtual HS_GRAPHICDLL Vertexbuffer* CreateTerrainVertexBuffer(ParserData::Mesh* mModel, std::string maskName) override;

	ID3D11RenderTargetView* GetEngineRTV();
	ID3D11DepthStencilView* GetEngineDSV();
private:
	void Create_SwapChain_RenderTarget();	//����Ÿ�� ����
	void Create_ViewPort();					//����Ʈ ����
	void CreateDevice();		//������ ����̽��� �������ش�
	void BeginRender();			//������ ����
	void EndRender();			//������ ����
	
	//�޽� Ÿ�Ժ� ����
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