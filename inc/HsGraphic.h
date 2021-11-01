#pragma once

#include "GraphicsEngine.h"
#include <d3d11.h>
#include <string>

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
	virtual HS_GRAPHICDLL void OnReSize(float Change_Width, float Change_Height) override;
	virtual HS_GRAPHICDLL void Render(std::queue<MeshData*>* meshList, GlobalData* global) override;
	virtual HS_GRAPHICDLL void Delete() override;

	virtual HS_GRAPHICDLL TextureBuffer* CreateTextureBuffer(std::string path) override;
	virtual HS_GRAPHICDLL Indexbuffer*	CreateIndexBuffer(ParserData::Model* mModel) override;
	virtual HS_GRAPHICDLL Vertexbuffer* CreateVertexBuffer(ParserData::Model* mModel) override;
private:
	void CreateRenderTarget();	//랜더타겟 뎁스스텐실 뷰포트를 생성한다
	void CreateRenderState();	//랜더타겟 상태를 생성해준다
	void BeginRender();			//랜더링 시작
	void EngineRender();		//엔진 랜더링
	void EndRender();			//랜더링 종료
	float GetAspectRatio();		//화면비율 종횡비를 설정
private:

	///엔진 데이터
	HWND					hwnd;				//윈도우 핸들
	ID3D11Device*			m_device;			//디바이스
	ID3D11DeviceContext*	m_deviceContext;	//디바이스 컨텍스트
	ID3D11RenderTargetView* m_renderTargetView;	//랜더 타겟
	ID3D11DepthStencilView* mDepthStencilView;	//뎁스 스텐실뷰
	D3D11_VIEWPORT			mScreenViewport;	//뷰포트
	IDXGISwapChain*			mSwapChain;			//스왑체인	


	//윈도우 사이즈
	int WinSizeX;	//윈도우 사이즈 가로
	int WinSizeY;	//윈도우 사이즈 세로


	//랜더링 모드
	ID3D11RasterizerState* mWireframe;
	ID3D11RasterizerState* mSolid;
};