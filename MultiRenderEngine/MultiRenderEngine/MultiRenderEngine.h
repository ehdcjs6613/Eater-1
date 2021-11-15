#pragma once

#ifdef MULTIRENDERENGINE_EXPORTS
#define MULTIENGINE_DLL __declspec(dllexport)
#else
#define MULTIENGINE_DLL __declspec(dllimport)

#ifdef _DEBUG
#pragma comment(lib,"MultiRenderEngine_x64d")
#else
#pragma comment(lib,"MultiRenderEngine_x64r")
#endif

#endif

// �ִ� �������� �� �ִ� ����Ÿ�� ��. (20���� ������..)
#define MAX_SPLIT_TARGET	20
// �ִ� ������
#define MAX_HORIZONTAL	6
// �ִ� ������
#define MAX_VERTICAL	5


#include <windows.h>
#include <map>
#include <queue>
#include <string>

struct ID3D11RenderTargetView;
class GraphicEngine;
class MeshData;
class GlobalData;

class MultiRenderEngine
{
private:
	/// �����ڸ� Private���� ���߾�, Initialize �� ȣ���ϰԲ� �Ѵ�.
	MultiRenderEngine();
	~MultiRenderEngine();

	static MultiRenderEngine* m_Engine;
	
private:
	// �ɰ� ȭ���� ��
	std::map<int, std::pair<ID3D11RenderTargetView* , GraphicEngine*>> Split_Window;
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

	MULTIENGINE_DLL void Render(std::queue<MeshData*>* meshList, GlobalData* global);
	MULTIENGINE_DLL void Delete();

private:
	void BeginRender();
	void EndRender();
};

