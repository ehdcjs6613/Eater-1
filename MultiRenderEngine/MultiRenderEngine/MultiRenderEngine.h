#pragma once

// 최대 나누어질 수 있는 랜더타겟 뷰. (20개로 지정함..)
#define MAX_SPLIT_TARGET	20
// 최대 가로축
#define MAX_HORIZONTAL	6
// 최대 세로축
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
	/// 생성자를 Private으로 감추어, Initialize 를 호출하게끔 한다.
	MultiRenderEngine();
	~MultiRenderEngine();

	static MultiRenderEngine* m_Engine;
private:
	// 쪼갠 화면의 수
	std::map<int, std::pair<D3D11_VIEWPORT* , GraphicEngine*>> Split_Window;
	// 현재 등록되어있는 엔진들을 관리.
	std::map<std::string, GraphicEngine*> Registered_Engine_List;

public:
	MULTIENGINE_DLL static MultiRenderEngine* Initialize(HWND hwnd, int screenWidth, int screenHeight);
	
	/// 화면을 얼만큼 쪼갤지 정함. 만약 최대 개수를 넘거나, 가로/세로 축의 최대값을 넘으면 return 값이 0(false)이다.
	/*
		예를 들어 Horizontal 4, Vertical 3 이라면.. 다음과 같이 나눠진다
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


	//그래픽 엔진 디바이스와 컨텍스트를 생성해줌
	void CreateDevice(HWND hwnd,int screenWidth, int screenHeight);

	//스왑체인에 붙어있는 랜더타겟을 생성해준다
	void Create_SwapChain_RenderTarget();

	void Create_ViewPort(int count, int StartX, int StartY, int Width, int Height);
	
	//사용하기위한 랜더타겟을 만들어줌
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

	//뷰포트 리스트
	std::map<int,D3D11_VIEWPORT*> ViewPortList;
};


