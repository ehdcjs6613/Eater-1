#pragma once

#include "GraphicsEngine.h"
#include "DH3DEngineDefine.h"
#include "DH3DEngineHeader.h"

#ifdef DH3DENGINE_EXPORTS
#define DHENGINE_DLL __declspec(dllexport)
#else
#define DHENGINE_DLL __declspec(dllimport)

#ifdef _DEBUG
#pragma comment(lib,"DH3DEngine_x64d")
#else
#pragma comment(lib,"DH3DEngine_x64r")
#endif

#endif

class AxisGrid;

class DH3DEngine : public GraphicEngine
{

	/// Graphic Engine ���� ���.
public:
	DHENGINE_DLL DH3DEngine();
	DHENGINE_DLL virtual ~DH3DEngine();
	/// �ʱ�ȭ ����
	DHENGINE_DLL void Initialize(HWND _hWnd, int screenWidth, int screenHeight);
	/// ȭ�� ���Ž� Resize�� �� �Լ�.
	DHENGINE_DLL Indexbuffer* CreateIndexBuffer(ParserData::Mesh* mModel);	//�ε��� ���۸� ������ش�
	DHENGINE_DLL Vertexbuffer* CreateVertexBuffer(ParserData::Mesh* mModel);	//���ؽ� ���۸� ������ش�
	DHENGINE_DLL TextureBuffer* CreateTextureBuffer(std::string path);					//�ؽ��ĸ� ������ش�
	DHENGINE_DLL void OnReSize(int Change_Width, int Change_Height);
	DHENGINE_DLL void Delete();
	/// �������� �Ѵ� �Ž� ���������� ����Ʈ, �۷ι� ������
	DHENGINE_DLL void Render(std::queue<MeshData*>* meshList, GlobalData* global);

	DHENGINE_DLL void SetViewPort(void* VPT, int Change_Width, int Change_Height);
	DHENGINE_DLL void SetDevice(void* Devie, void* DevieContext);


	/// �������ο��� �����ϸ� ���� ������?
private:
	/// View Mat
	DirectX::SimpleMath::Matrix View_Mat;
	/// Proj Mat
	DirectX::SimpleMath::Matrix Proj_Mat;
	/// World Mat
	DirectX::SimpleMath::Matrix World_Mat;
	// WVP ����
	DirectX::SimpleMath::Matrix Mul_WVP;		// W * V * P
	DirectX::SimpleMath::Matrix World_Inverse;	// ���� �����
	DirectX::SimpleMath::Matrix World_Inverse_Transpose;

	HWND g_hWnd;
	float g_Screen_Width = 0.0f;
	float g_Screen_Height = 0.0f;
	POINT m_Last_Mouse_Position = { 0, };
	// ����� ����ΰ�?
	bool Is_Debug = true;
	// skybox
	std::string Sky_Box_Path = "";

public:
	struct DHVertex
	{
		DirectX::SimpleMath::Vector3 Pos;
		DirectX::SimpleMath::Vector3 Normal;
		DirectX::SimpleMath::Vector2 Tex;
		DirectX::SimpleMath::Vector3 Tangent;
	};
	/// �ʱ� ������.
	void CreateGraphicResource();
	/// ����� ���ð�
	void SetDebug(bool _Is_Debug, int _Grid_Num = 50);
	/// ���� Draw ����
	void BeginDraw();
	/// ���� Draw ����.
	void EndDraw();
	/// DX11 ������ �Լ���.
private:
	/// ���� ��Ⱦ�� �����ϴ� �κ�.
	float GetAspectRatio() const;
	/// ���� ������Ʈ�� ������ �����ΰ� ����Ī.
	void CreateRenderStates();

private:
	/// Render State
	// �̸� ���� ��Ʈ�� �����ΰ� ����Ī�Ѵ�.
	ID3D11RasterizerState* mWireframeRS = nullptr;
	ID3D11RasterizerState* mSolidRS = nullptr;

	// ��Ʈ������ �������Ľ� ������Ʈ�� ����.
	ID3D11DepthStencilState* NormalDSS = nullptr;

	/// Axis, Grid
	AxisGrid* m_AxisGrid = nullptr;

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
	ID3D11Buffer* Render_VB = nullptr;
	ID3D11Buffer* Render_IB = nullptr;

	/// Render���� �Ź� �Ҵ� / ���� �ϴ� �������� ���� �����ص���.
	// Buffer ����
	UINT Vertex_Buffer_Stride = 0;
	UINT Vertex_Buffer_Offset = 0;


	/// �Ⱦ��̰� �ִ°�
	ID3DX11EffectMatrixVariable* mfxWorldViewProj = nullptr;

	ID3DX11Effect* mFX = nullptr;
	ID3DX11EffectTechnique* mTech = nullptr;
};

