#pragma once
#include "GraphicsEngine.h"

//    DirectX관련 클래스
//	  장치의 관리의 D		evice클래스
class DirectXDevice;
//	  장치의 그리기를 담당할 DeviceContext클래스
class DirectXDeviceContext;
//	  스왑체인의 클래스
class DirectXSwapChain;
//	  그래픽카드(어뎁터,비디오카드) 정보 클래스
class DirectXAdapter;

//	  어떻게 그릴지의 레스터라이져 클래스
class DirectXRasterizerState;
//	  렌더러 클래스
class XRenderer;


class X3Engine : public GraphicEngine
{
private:
	//
///-----------[엔진이 지니는 변수들]------------///
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
	//렌더러 기능
	XRenderer*				m_pRenderer;



private:
	int					  m_iWidth;
	int					  m_iHeight;
	int					  m_videoCardMemory;
public:

public:
	//기본엔진 생성자
	X3Engine();
	//이 엔진에 아래는 없다
	virtual ~X3Engine() final;
public:
#pragma region Parents Overriding Function List

	///GraphicEngine class로부터 상속된 함수들
	
	///게임 엔진쪽에서 윈도우 핸들을 넘겨줄것임
	virtual void Initialize(HWND _hWnd, int screenWidth, int screenHeight) override;


	///그래픽 엔진과 게임엔진에서 주고받아야할 함수들
	virtual Indexbuffer*  CreateIndexBuffer(ParserData::Model* mModel) override;	//인덱스 버퍼를 만들어준다
	virtual Vertexbuffer* CreateVertexBuffer(ParserData::Model* mModel) override;	//버텍스 버퍼를 만들어준다
	virtual void		  CreateTextureBuffer() override;									//텍스쳐를 만들어준다
	virtual void		  OnReSize(float Change_Width, float Change_Height) override;			//리사이즈


	/// 랜더링을 한다 매쉬 랜더데이터 리스트, 글로벌 데이터
	virtual void		  Render(std::queue<MeshData*>* meshList, GlobalData* global) override;

#pragma endregion Parents Overriding Function List
public:
	//엔진 고유의 함수
	void CreateRenderState();
};

