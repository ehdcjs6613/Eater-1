#pragma once

#include "SharedData.h"
#include "DH3DEngineDefine.h"
#include "DH3DEngineHeader.h"

class D2DSupport;
class AxisGrid;
class SkyBox;

class GameTimer;
//테스트용 
class Texture;


class DH3DEngine
{
	/// 엔진내부에서 관리하면 좋은 변수들?
private:
	HWND g_hWnd;
	float g_Screen_Width = 0.0f;
	float g_Screen_Height = 0.0f;
	POINT m_Last_Mouse_Position = { 0, };

	// 디버그 모드인가?
	bool Is_Debug = true;
	// AxisGrid는 한번만 그리도록!
	bool Is_Draw_AxisGrid = false;

	// skybox
	std::wstring Sky_Box_Path = L"";
	SkyBox* m_SkyBox = nullptr;

public:
	DH3DEngine();
	virtual ~DH3DEngine();

	/// 초기화 관련
	void Initialize(HWND hWnd, int screenWidth, int screenHeight);
	void CreateGraphicResource();

	/// 디버그 세팅값
	void SetDebug(bool _Is_Debug, int _Grid_Num = 50);

	/// 스카이박스 셋팅
	void SetSkyBox(std::wstring _Sky_Box_Path);

	/// 엔진 Draw 시작
	void BeginDraw();

	/// 엔진 Update ( Dtime 기반 )
	void Update(GameTimer* _pTimer);
	//void Update(float DTime);

	/// 엔진 Draw
	void RenderDraw(OneFrameData* _OFD, SharedRenderData* _SRD);
	void UIDraw(Shared2DRenderData* _S2DRD);
	// 텍스트 드로우 ( 가변인자는 안됨 ㅎㅎ )
	void TextDraw(POINT _Pos, float _Width,
		float r, float g, float b, float a,
		float _Size, const wchar_t* _Input_String);
	void LoadingDraw(std::wstring _Loading_Path);

	/// 엔진 Draw 종료.
	void EndDraw();

	/// 엔진 해제.
	void Finalize();

	/// 화면 갱신시 Resize를 할 함수.
	void On_Resize(float Change_Width, float Change_Height);

	/// DX11 고유의 함수들.
private:
	/// 스카이박스 셋팅이 되어있다면 그려줌.
	void DrawSkyBox(OneFrameData* _OFD);

	/// 현재 종횡비를 리턴하는 부분.
	float GetAspectRatio() const;

	/// 텍스쳐를 만드는 부분
	void SetTextureSRV(SharedRenderData* _SRD);

	/// 화면크기가 변했을때 갱신.

	/// 하드웨어 정보를 받아온다.
	HRESULT GetAdapterInfo();

	/// 현재 상태를 화면에 출력.
	void Draw_Status();
	/// 버퍼생성
	void CreateIndexBuffer(DHParser::Mesh* _Mesh);
	void CreateVertexBuffer(DHParser::Mesh* _Mesh);

	/// 랜더 스테이트를 여러개 만들어두고 스위칭.
	void CreateRenderStates();

	/// Build 하는 것들..
	void BuildFX();
	void BuildFX_Create();

private:
	/// Render State
	// 미리 여러 세트를 만들어두고 스위칭한다.
	ID3D11RasterizerState* mWireframeRS = nullptr;
	ID3D11RasterizerState* mSolidRS = nullptr;

	// 폰트때문에 뎁스스탠실 스테이트가 강제.
	ID3D11DepthStencilState* NormalDSS = nullptr;

	/// Text출력
	D2DSupport* m_pD2DSupport = nullptr;

	/// Axis, Grid
	AxisGrid* m_AxisGrid = nullptr;

	/// DTime
	float m_Delta_Time = 0.0f;

	/// 어뎁터 정보
	DXGI_ADAPTER_DESC1 m_Adapter_Desc1;

	/// DX11 관련 필요변수.
	int Video_Card_Memory = 0;
	D3D_FEATURE_LEVEL featureLevel;

	IDXGISwapChain* DX11_Swap_Chain = nullptr;
	ID3D11Device* DX11_Device = nullptr;
	ID3D11DeviceContext* DX11_Device_Context = nullptr;
	ID3D11RenderTargetView* DX11_Render_Target_View = nullptr;
	ID3D11Texture2D* DX11_Depth_Stencil_Buffer = nullptr;
	ID3D11DepthStencilState* DX11_Depth_Stencil_State = nullptr;
	ID3D11DepthStencilView* DX11_Depth_Stencil_View = nullptr;
	ID3D11RasterizerState* DX11_Raster_State = nullptr;
	D3D11_VIEWPORT DX11_View_Port = { 0, };					// 뷰포트

private:
	/// 쓰이고있는거
	ID3D11Buffer* mVB;
	ID3D11Buffer* mIB;

	/// Render에서 매번 할당 / 해제 하는 변수들은 따로 선언해두자.
	// Buffer 관련
	UINT Vertex_Buffer_Stride = 0;
	UINT Vertex_Buffer_Offset = 0;

	// WVP 관련
	DirectX::SimpleMath::Matrix Mul_WVP;		// W * V * P
	DirectX::SimpleMath::Matrix World_Inverse;	// 월드 역행렬
	DirectX::SimpleMath::Matrix World_Inverse_Transpose;

	/// 안쓰이고 있는거
	ID3DX11EffectMatrixVariable* mfxWorldViewProj = nullptr;

	ID3DX11Effect* mFX = nullptr;
	ID3DX11EffectTechnique* mTech = nullptr;
	/// 나중에 버릴거
	Texture* m_pTestTexture;

};

