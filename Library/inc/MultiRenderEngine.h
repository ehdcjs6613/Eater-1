#pragma once

// �ִ� �������� �� �ִ� ����Ÿ�� ��. (20���� ������..)
#define MAX_SPLIT_TARGET	20
// �ִ� ������
#define MAX_HORIZONTAL	6
// �ִ� ������
#define MAX_VERTICAL	5

#include "MultiRenderDefine.h"


struct ID3D11RenderTargetView;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct IDXGISwapChain;
struct ID3D11DepthStencilView;
struct D3D11_VIEWPORT;

class GraphicEngine;
class MeshData;
class GlobalData;
class TextureBase;
class Vertexbuffer;
class Indexbuffer;
class TextureBuffer;

namespace ParserData
{
	class Mesh;
}

class MultiRenderEngine
{
private:
	/// �����ڸ� Private���� ���߾�, Initialize �� ȣ���ϰԲ� �Ѵ�.
	MultiRenderEngine();
	~MultiRenderEngine();

	static MultiRenderEngine* m_Engine;
private:
	// �ɰ� ȭ���� ��
	std::map<int, std::pair<D3D11_VIEWPORT* , GraphicEngine*>> Split_Window;
	// ���� ��ϵǾ��ִ� �������� ����.
	std::map<std::string, GraphicEngine*> Registered_Engine_List;

public:
	MULTIENGINE_DLL static MultiRenderEngine* Initialize(HWND hwnd, int screenWidth, int screenHeight);
	
	/// ȭ���� ��ŭ �ɰ��� ����. ���� �ִ� ������ �Ѱų�, ����/���� ���� �ִ밪�� ������ return ���� 0(false)�̴�.
	/*
		���� ��� Horizontal 4, Vertical 3 �̶��.. ������ ���� ��������
		 _______________________________
		|		|		|		|		|
		|	0	|	1	|	2	|	3	|
		|_______|_______|_______|_______|
		|		|		|		|		|
		|	4	|	5	|	6	|	7	|
		|_______|_______|_______|_______|
		|		|		|		|		|
		|	8	|	9	|	10	|	11	|
		|_______|_______|_______|_______|
	
	*/
	MULTIENGINE_DLL BOOL SplitWindow(int _Horizontal, int _Vertical);
	MULTIENGINE_DLL BOOL RegisterRenderer(GraphicEngine* _Renderer, std::string _Engine_Name);
	MULTIENGINE_DLL BOOL SetRenderer(int _ViewPort_Number, std::string _Engine_Name);
	MULTIENGINE_DLL BOOL OnResize(int Change_Width, int Change_Height);

	MULTIENGINE_DLL void ShadowRender(int count, std::queue<MeshData*>* meshList, GlobalData* global);
	MULTIENGINE_DLL void Render(int count, std::queue<MeshData*>* meshList, GlobalData* global);
	MULTIENGINE_DLL void Delete();


	MULTIENGINE_DLL Vertexbuffer* CreateVertexBuffer(ParserData::Mesh* mModel);	//���ؽ� ���۸� �����Ѵ�
	MULTIENGINE_DLL Indexbuffer*  CreateIndexBuffer(ParserData::Mesh* mModel);	//�ε��� ���۸� �����Ѵ�
	MULTIENGINE_DLL TextureBuffer* CreateTextureBuffer(std::string Name);		//�ؽ��ĸ� �����Ѵ�

	MULTIENGINE_DLL void EndRender();
	MULTIENGINE_DLL	void BeginRender();
	MULTIENGINE_DLL int GetWindowCount();
private:
	//�׷��� ���� ����̽��� ���ؽ�Ʈ�� ��������
	void CreateDevice(HWND hwnd,int screenWidth, int screenHeight);

	//����ü�ο� �پ��ִ� ����Ÿ���� �������ش�
	void Create_SwapChain_RenderTarget();

	//����Ʈ�� �����Ѵ�
	void Create_ViewPort(int count, int StartX, int StartY, int Width, int Height);
	
	//����Ʈ�� �������� ������ �缳��
	void ReSetting_ViewPort(int count, int StartX, int StartY, int Width, int Height);

	//����Ʈ�� �����ϱ� �� ���ð��� ���� (������ Create�� Resize ���Ұ��� ���� �����Ұ�����)
	void ViewPortSetting(int m_Horizontal, int m_Vertical,BOOL Create = true);

	//�Ž� ���ؽ� ���۸� ����
	Vertexbuffer* BasicVertexBuffer(ParserData::Mesh* mModel);

	//��Ű�� ���ؽ� ���۸� ����
	Vertexbuffer* SkinningVertexBuffer(ParserData::Mesh* mModel);

	//DDS �ؽ��ĸ� ����
	TextureBuffer* CreateDDSTexture(std::string Name);
	//WICT �ؽ��ĸ� ����
	TextureBuffer* CreateWICTexture(std::string Name);
private:
	HWND m_Hwnd;

	int m_ScreenHeight;
	int m_ScreenWidth;
	int WindowCount;

	int Split_X_Count;
	int Split_Y_Count;

	ID3D11Device*			m_Device;
	ID3D11DeviceContext*	m_DeviceContext;
	IDXGISwapChain*			m_SwapChain;

	ID3D11RenderTargetView* m_RenderTargetView;
	ID3D11DepthStencilView* m_DepthStencilView;
	D3D11_VIEWPORT*			m_ViewPort;
};


