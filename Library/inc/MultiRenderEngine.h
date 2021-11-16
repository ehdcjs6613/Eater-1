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

	MULTIENGINE_DLL void Render(int count, std::queue<MeshData*>* meshList, GlobalData* global);
	MULTIENGINE_DLL void Delete();



	MULTIENGINE_DLL Vertexbuffer* CreateVertexBuffer(ParserData::Mesh* mModel);
	MULTIENGINE_DLL Indexbuffer*  CreateIndexBuffer(ParserData::Mesh* mModel);
	MULTIENGINE_DLL void EndRender();
	MULTIENGINE_DLL	void BeginRender();
	MULTIENGINE_DLL int GetWindowCount();
private:


	//�׷��� ���� ����̽��� ���ؽ�Ʈ�� ��������
	void CreateDevice(HWND hwnd,int screenWidth, int screenHeight);

	//����ü�ο� �پ��ִ� ����Ÿ���� �������ش�
	void Create_SwapChain_RenderTarget();

	void Create_ViewPort(int count, int StartX, int StartY, int Width, int Height);
	
	//����ϱ����� ����Ÿ���� �������
	TextureBase* Create_RenderTarget(int StartX,int StartY,int Width,int Height);
private:
	HWND m_Hwnd;

	int m_ScreenHeight;
	int m_ScreenWidth;
	int WindowCount;

	ID3D11Device*			m_Device;
	ID3D11DeviceContext*	m_DeviceContext;
	IDXGISwapChain*			m_SwapChain;

	ID3D11RenderTargetView* m_RenderTargetView;
	ID3D11DepthStencilView* m_DepthStencilView;
	D3D11_VIEWPORT*			m_ViewPort;

	//����Ʈ ����Ʈ
	std::map<int,D3D11_VIEWPORT*> ViewPortList;
};


