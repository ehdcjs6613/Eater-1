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

class SharedRenderData;

class Grahpics2D;

//그리기를 위한 포인터의  클래스
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
///-----------[엔진이 지니는 변수들]------------///
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
	//렌더러 기능
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
	virtual Indexbuffer*   CreateIndexBuffer(ParserData::Model* mModel) override;	//인덱스 버퍼를 만들어준다
	virtual Vertexbuffer*  CreateVertexBuffer(ParserData::Model* mModel) override;	//버텍스 버퍼를 만들어준다
	virtual TextureBuffer* CreateTextureBuffer(std::string path) override;									//텍스쳐를 만들어준다
	virtual void		   OnReSize(int Change_Width, int Change_Height) override;			//리사이즈
	virtual void		   Delete() override;

	/// 랜더링을 한다 매쉬 랜더데이터 리스트, 글로벌 데이터
	virtual void		  Render(std::queue<MeshData*>* meshList, GlobalData* global) override;

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
	//Microsoft::WRL::ComPtr<ID3D10Blob> m_pVertexShaderBuffer;
	IDXGISwapChain* m_pSwapChain;
	XVertexShader m_XVertexShader;
	XPixelShader  m_XPexelShader;
public:
	//test
	ID3D11Buffer* m_pVertexBuffer;
	bool TestScene();
private:
	// 폰트때문에 뎁스스탠실 스테이트가 강제.
	ID3D11DepthStencilState* NormalDSS = nullptr;

	ID3D11RasterizerState* mWireframeRS = nullptr;
	ID3D11RasterizerState* mSolidRS = nullptr;
	//-----------------------------------

public:

};

