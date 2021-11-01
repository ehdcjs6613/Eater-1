#pragma once

#include "SharedData.h"
#include "DH3DEngineDefine.h"
#include "DH3DEngineHeader.h"

class D2DSupport;
class AxisGrid;
class SkyBox;

class DH3DEngine
{
	/// �������ο��� �����ϸ� ���� ������?
private:
	HWND g_hWnd;
	float g_Screen_Width = 0.0f;
	float g_Screen_Height = 0.0f;
	POINT m_Last_Mouse_Position = { 0, };

	// ����� ����ΰ�?
	bool Is_Debug = true;
	// AxisGrid�� �ѹ��� �׸�����!
	bool Is_Draw_AxisGrid = false;

	// skybox
	ATL::CString Sky_Box_Path = "";
	SkyBox* m_SkyBox = nullptr;

public:
	DH3DEngine();
	virtual ~DH3DEngine();

	/// �ʱ�ȭ ����
	void Initialize(HWND hWnd, int screenWidth, int screenHeight);
	void CreateGraphicResource();

	/// ����� ���ð�
	void SetDebug(bool _Is_Debug, int _Grid_Num = 50);

	/// ��ī�̹ڽ� ����
	void SetSkyBox(ATL::CString _Sky_Box_Path);

	/// ���� Draw ����
	void BeginDraw();

	/// ���� Update ( Dtime ��� )
	void Update(float DTime);

	/// ���� Draw
	void RenderDraw(OneFrameData* _OFD, SharedRenderData* _SRD);
	void UIDraw(Shared2DRenderData* _S2DRD);
	// �ؽ�Ʈ ��ο� ( �������ڴ� �ȵ� ���� )
	void TextDraw(POINT _Pos, float _Width,
		float r, float g, float b, float a,
		float _Size, const wchar_t* _Input_String);
	void LoadingDraw(ATL::CString _Loading_Path);

	/// ���� Draw ����.
	void EndDraw();

	/// ���� ����.
	void Finalize();

	/// ȭ�� ���Ž� Resize�� �� �Լ�.
	void On_Resize(float Change_Width, float Change_Height);
	/// DX11 ������ �Լ���.
	void CreateIndexBuffer(DHParser::Mesh* _Mesh);
	void CreateVertexBuffer(DHParser::Mesh* _Mesh);

	/// �ؽ��ĸ� ����� �κ�
	void SetTextureSRV(SharedRenderData* _SRD);
private:
	/// ��ī�̹ڽ� ������ �Ǿ��ִٸ� �׷���.
	void DrawSkyBox(OneFrameData* _OFD);

	/// ���� ��Ⱦ�� �����ϴ� �κ�.
	float GetAspectRatio() const;


	/// ȭ��ũ�Ⱑ �������� ����.

	/// �ϵ���� ������ �޾ƿ´�.
	HRESULT GetAdapterInfo();

	/// ���� ���¸� ȭ�鿡 ���.
	void Draw_Status();
	/// ���ۻ���

	/// ���� ������Ʈ�� ������ �����ΰ� ����Ī.
	void CreateRenderStates();

	/// Build �ϴ� �͵�..
	void BuildFX();
	void BuildFX_Create();

private:
	/// Render State
	// �̸� ���� ��Ʈ�� �����ΰ� ����Ī�Ѵ�.
	ID3D11RasterizerState* mWireframeRS = nullptr;
	ID3D11RasterizerState* mSolidRS = nullptr;

	// ��Ʈ������ �������Ľ� ������Ʈ�� ����.
	ID3D11DepthStencilState* NormalDSS = nullptr;

	/// Text���
	D2DSupport* m_D2DSupport = nullptr;

	/// Axis, Grid
	AxisGrid* m_AxisGrid = nullptr;

	/// DTime
	float m_Delta_Time = 0.0f;

	/// ��� ����
	DXGI_ADAPTER_DESC1 m_Adapter_Desc1;

	/// DX11 ���� �ʿ亯��.
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
	D3D11_VIEWPORT DX11_View_Port = { 0, };					// ����Ʈ

private:
	/// ���̰��ִ°�
	ID3D11Buffer* mVB;
	ID3D11Buffer* mIB;

	/// Render���� �Ź� �Ҵ� / ���� �ϴ� �������� ���� �����ص���.
	// Buffer ����
	UINT Vertex_Buffer_Stride = 0;
	UINT Vertex_Buffer_Offset = 0;

	// WVP ����
	DirectX::SimpleMath::Matrix Mul_WVP;		// W * V * P
	DirectX::SimpleMath::Matrix World_Inverse;	// ���� �����
	DirectX::SimpleMath::Matrix World_Inverse_Transpose;

	/// �Ⱦ��̰� �ִ°�
	ID3DX11EffectMatrixVariable* mfxWorldViewProj = nullptr;

	ID3DX11Effect* mFX = nullptr;
	ID3DX11EffectTechnique* mTech = nullptr;
};

