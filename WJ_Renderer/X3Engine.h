#pragma once



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
//	  샘플러 스테이트 클래스
class DirectXSamplerState;

class SharedRenderData;

class Grahpics2D;

//그리기를 위한 포인터의  클래스
class Vertexbuffer;
class Indexbuffer;
class TextureBuffer;
class MeshData;
class GlobalData;
//개인그리기
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
/// 개별 렌더러 엔진?
/// </summary>
class X3Engine : public  GraphicEngine
{
private:
	FLOAT					 m_ArrColor[4];
	D3D11_VIEWPORT*			 m_ViewPort;
private:
	//
///-----------[엔진이 지니는 변수들]------------///
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
	//사용자 재정의로 다시한번 매핑 한? 클래스변수
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
	//기본엔진 생성자
	X3Engine_DLL X3Engine();
	//이 엔진에 아래는 없다
	X3Engine_DLL virtual ~X3Engine() final;
public:
#pragma region Parents Overriding Function List

	///GraphicEngine class로부터 상속된 함수들

	///게임 엔진쪽에서 윈도우 핸들을 넘겨줄것임
	X3Engine_DLL virtual void Initialize(HWND _hWnd, int _iWidth, int _iHeight) override;


	///그래픽 엔진과 게임엔진에서 주고받아야할 함수들


	X3Engine_DLL virtual Indexbuffer* CreateIndexBuffer(ParserData::Mesh* mModel)	override;	//인덱스 버퍼를 만들어준다
	X3Engine_DLL virtual Vertexbuffer* CreateVertexBuffer(ParserData::Mesh* mModel) override;	//버텍스 버퍼를 만들어준다
	X3Engine_DLL virtual TextureBuffer* CreateTextureBuffer(std::string path) override;									//텍스쳐를 만들어준다
	X3Engine_DLL virtual void		   OnReSize(int Change_Width, int Change_Height) override;			//리사이즈
	X3Engine_DLL virtual void		   Delete() override;

	/// 랜더링을 한다 매쉬 랜더데이터 리스트, 글로벌 데이터
	X3Engine_DLL virtual void		  Render(std::queue<MeshData*>* meshList, GlobalData* global) override;


	/// 랜더타겟에 해당하는 데이터를 넘겨줄것임 
	/// (사실 디바이스만 넘어가면 멀티그래픽엔진쪽으로 넘겨줘도될듯)
	virtual void SetViewPort(void* VPT);//랜더타겟뷰, 뎁스스텐실,뷰포트
	virtual void SetDevice(void* Devie, void* DevieContext); //디바이스,컨텍스트


#pragma endregion Parents Overriding Function List
public:
	//엔진 고유의 함수
	void CreateRenderState();
	void DrawSystemStatus();

	/// 텍스쳐를 만드는 부분
	void SetTextureSRV(SharedRenderData* _SRD);

	void Release();

public:
	void InitializeShaders();


private:
	////정점셰이더를 저장하기 위한 변수를 추가
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
	// 폰트때문에 뎁스스탠실 스테이트가 강제가 됐다.
	ID3D11DepthStencilState* NormalDSS;

	DirectX::SimpleMath::Matrix mWorld;	// Transform Matrix
	DirectX::SimpleMath::Matrix mView;
	DirectX::SimpleMath::Matrix mProj;

	ID3D11Buffer* Render_VB = nullptr;
	ID3D11Buffer* Render_IB = nullptr;
	// Buffer 관련
	UINT Vertex_Buffer_Stride = 0;
	UINT Vertex_Buffer_Offset = 0;
	// WVP 관련
	DirectX::SimpleMath::Matrix Mul_WVP;		// W * V * P
	DirectX::SimpleMath::Matrix World_Inverse;	// 월드 역행렬
	DirectX::SimpleMath::Matrix World_Inverse_Transpose;
};

