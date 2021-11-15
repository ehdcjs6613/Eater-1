#include "MultiRenderEngine.h"
#include <iostream>

#include "EngineData.h"
#include "GraphicsEngine.h"
#include <d3d11.h>


MultiRenderEngine* MultiRenderEngine::m_Engine = nullptr;

MultiRenderEngine::MultiRenderEngine()
{

}

MultiRenderEngine::~MultiRenderEngine()
{

}

MultiRenderEngine* MultiRenderEngine::Initialize(HWND hwnd, int screenWidth, int screenHeight)
{
	m_Engine = new MultiRenderEngine();



	return m_Engine;
}

BOOL MultiRenderEngine::SplitWindow(int _Horizontal, int _Vertical)
{
	// �̹� �ɰ��� ������ ���.. (���� ��� �������� �𸣰����� �ϴ� ���Ƴ���)
	if (!Split_Window.empty())							
	{
		std::cout << "[MultiRenderEngine::SplitWindow() ����] �̹� Split�� Window�� �����մϴ�. (�ߺ�ȣ��)" << std::endl;
		return false;
	}
	// ������ �ִ� ������ �ʰ��� ��� false ����..
	if (_Horizontal > MAX_HORIZONTAL)
	{
		std::cout << "[MultiRenderEngine::SplitWindow() ����]" << MAX_HORIZONTAL << " �� �̻��� Horizontal ������ �Ұ����մϴ�." << std::endl;
		return false;
	}
	if (_Vertical > MAX_VERTICAL)
	{
		std::cout << "[MultiRenderEngine::SplitWindow() ����]" << MAX_VERTICAL << " �� �̻��� Vertical ������ �Ұ����մϴ�." << std::endl;
		return false;
	}
	if ((_Horizontal * _Vertical) > MAX_SPLIT_TARGET)
	{
		std::cout << "[MultiRenderEngine::SplitWindow() ����]" << MAX_SPLIT_TARGET << " �� �̻��� Window Split�� �Ұ����մϴ�." << std::endl;
		std::cout << " ���� �Է°� => Horizontal : " << _Horizontal << "\tVertical : " << _Vertical << std::endl;
		return false;
	}

	for (int i = 0; i < _Horizontal * _Vertical; i++)
	{
		/// RenderTargetView �� �����ؼ� ID3D11RenderTargetView* �ڸ��� �Ҵ��صθ� ��.
		Split_Window.insert({i, {nullptr, nullptr}});
		/// �ڷ����� �򰥸��Ŵٸ� ������ �����Ͻø�˴ϴ�..
		//std::pair<int, std::pair<ID3D11RenderTargetView*, GraphicEngine*>> InsertData = { i, {nullptr, nullptr} };
		//Split_Window.emplace(InsertData);
	}

	// ������ ����Ÿ���� ������ ����.
	return Split_Window.size();
}

BOOL MultiRenderEngine::RegisterRenderer(GraphicEngine* _Renderer, std::string _Engine_Name)
{
	// �̹� �����ϴ� �����̶�� return false;
	if (Registered_Engine_List.find(_Engine_Name) != Registered_Engine_List.end())
	{
		std::cout << "[MultiRenderEngine::RegisterRenderer() ����] �̹� ��ϵ� Graphic Engine�� �����մϴ�. (�ߺ�ȣ��)" << std::endl;
		return false;
	}

	// �Ҵ���� ������ ����Ʈ�� ����س��´�.
	Registered_Engine_List.insert({ _Engine_Name, _Renderer });

	return true;
}

BOOL MultiRenderEngine::SetRenderer(int _ViewPort_Number, std::string _Engine_Name)
{
	// �����찡 �����Ǿ����� ������� return false;
	if (!Split_Window.empty()) 
	{ 
		std::cout << "[MultiRenderEngine::SetRenderer() ����] ���� Split Window �� ���� �ʾҽ��ϴ�." << std::endl;
		return false; 
	}

	/// �Է¹��� ����Ʈ�� �����͸� �޾ƿ´�.
	auto Split_Window_Data = Split_Window.find(_ViewPort_Number);
	// ���� �������� ���� ����Ʈ index�� ȣ���ϰԵȴٸ� false�� ����.
	if (Split_Window_Data == Split_Window.end())
	{
		std::cout << "[MultiRenderEngine::SetRenderer() ����] �߸��� ViewPort Number�� ȣ���ϼ̽��ϴ�." << std::endl;
		std::cout << " ���� ������ ViewPort ���� => " << Split_Window.size() << std::endl;
		return false;
	}

	/// �Է¹��� ������ �����͸� �޾ƿ´�.
	auto Find_Engine_Ptr = Registered_Engine_List.find(_Engine_Name);
	// ���� ��ϵ��� ���� ������ ȣ���Ѵٸ�..
	if (Find_Engine_Ptr == Registered_Engine_List.end())
	{
		std::cout << "[MultiRenderEngine::SetRenderer() ����] ��ϵ��� ���� Engine�� ȣ���ϼ̽��ϴ�. ���� RegisterRenderer() �� ���� �׷��� ������ ������ּ���." << std::endl;
		return false;
	}

	/// �ش��ϴ� ����Ʈ�� ������ ��Ī��Ų��.
	GraphicEngine* Target_Engine = Find_Engine_Ptr->second;
	Split_Window_Data->second.second = Target_Engine;

	/// ���⼭ ��!!!!!!!!!!!!!!!!!! ������ ViewPort�� �����.
	ID3D11RenderTargetView* Target_ViewPort = Split_Window_Data->second.first;
	// ex) Target_Engine->SetViewPort(Target_ViewPort); �̷�������..

	return true;
}

void MultiRenderEngine::Render(std::queue<MeshData*>* meshList, GlobalData* global)
{
	BeginRender();

	for (auto _Renderer : Split_Window)
	{
		/// ���������� VeiwPort ���� ������ ���ִ��� �ؾߵȴ�..
		// ex) _Renderer.second.second->Render(meshList, global);
	}

	EndRender();
}

void MultiRenderEngine::Delete()
{
	Registered_Engine_List.clear();
	Split_Window.clear();
}

void MultiRenderEngine::BeginRender()
{

}

void MultiRenderEngine::EndRender()
{

}
