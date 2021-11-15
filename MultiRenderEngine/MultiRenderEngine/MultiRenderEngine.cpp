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
	// 이미 쪼개서 생성한 경우.. (추후 어떻게 관리될진 모르겠지만 일단 막아놨음)
	if (!Split_Window.empty())							
	{
		std::cout << "[MultiRenderEngine::SplitWindow() 오류] 이미 Split된 Window가 존재합니다. (중복호출)" << std::endl;
		return false;
	}
	// 지정된 최대 개수를 초과한 경우 false 리턴..
	if (_Horizontal > MAX_HORIZONTAL)
	{
		std::cout << "[MultiRenderEngine::SplitWindow() 오류]" << MAX_HORIZONTAL << " 줄 이상의 Horizontal 생성은 불가능합니다." << std::endl;
		return false;
	}
	if (_Vertical > MAX_VERTICAL)
	{
		std::cout << "[MultiRenderEngine::SplitWindow() 오류]" << MAX_VERTICAL << " 줄 이상의 Vertical 생성은 불가능합니다." << std::endl;
		return false;
	}
	if ((_Horizontal * _Vertical) > MAX_SPLIT_TARGET)
	{
		std::cout << "[MultiRenderEngine::SplitWindow() 오류]" << MAX_SPLIT_TARGET << " 개 이상의 Window Split은 불가능합니다." << std::endl;
		std::cout << " 현재 입력값 => Horizontal : " << _Horizontal << "\tVertical : " << _Vertical << std::endl;
		return false;
	}

	for (int i = 0; i < _Horizontal * _Vertical; i++)
	{
		/// RenderTargetView 를 생성해서 ID3D11RenderTargetView* 자리에 할당해두면 됨.
		Split_Window.insert({i, {nullptr, nullptr}});
		/// 자료형이 헷갈리신다면 다음을 참조하시면됩니다..
		//std::pair<int, std::pair<ID3D11RenderTargetView*, GraphicEngine*>> InsertData = { i, {nullptr, nullptr} };
		//Split_Window.emplace(InsertData);
	}

	// 생성된 랜더타겟의 개수를 리턴.
	return Split_Window.size();
}

BOOL MultiRenderEngine::RegisterRenderer(GraphicEngine* _Renderer, std::string _Engine_Name)
{
	// 이미 존재하는 엔진이라면 return false;
	if (Registered_Engine_List.find(_Engine_Name) != Registered_Engine_List.end())
	{
		std::cout << "[MultiRenderEngine::RegisterRenderer() 오류] 이미 등록된 Graphic Engine이 존재합니다. (중복호출)" << std::endl;
		return false;
	}

	// 할당받은 엔진을 리스트에 등록해놓는다.
	Registered_Engine_List.insert({ _Engine_Name, _Renderer });

	return true;
}

BOOL MultiRenderEngine::SetRenderer(int _ViewPort_Number, std::string _Engine_Name)
{
	// 윈도우가 생성되어있지 않은경우 return false;
	if (!Split_Window.empty()) 
	{ 
		std::cout << "[MultiRenderEngine::SetRenderer() 오류] 아직 Split Window 를 하지 않았습니다." << std::endl;
		return false; 
	}

	/// 입력받은 뷰포트의 데이터를 받아온다.
	auto Split_Window_Data = Split_Window.find(_ViewPort_Number);
	// 만약 생성되지 않은 뷰포트 index를 호출하게된다면 false를 리턴.
	if (Split_Window_Data == Split_Window.end())
	{
		std::cout << "[MultiRenderEngine::SetRenderer() 오류] 잘못된 ViewPort Number을 호출하셨습니다." << std::endl;
		std::cout << " 현재 생성된 ViewPort 개수 => " << Split_Window.size() << std::endl;
		return false;
	}

	/// 입력받은 엔진의 데이터를 받아온다.
	auto Find_Engine_Ptr = Registered_Engine_List.find(_Engine_Name);
	// 만약 등록되지 않은 엔진을 호출한다면..
	if (Find_Engine_Ptr == Registered_Engine_List.end())
	{
		std::cout << "[MultiRenderEngine::SetRenderer() 오류] 등록되지 않은 Engine을 호출하셨습니다. 먼저 RegisterRenderer() 를 통해 그래픽 엔진을 등록해주세요." << std::endl;
		return false;
	}

	/// 해당하는 뷰포트에 엔진을 매칭시킨다.
	GraphicEngine* Target_Engine = Find_Engine_Ptr->second;
	Split_Window_Data->second.second = Target_Engine;

	/// 여기서 꼭!!!!!!!!!!!!!!!!!! 엔진에 ViewPort를 줘야함.
	ID3D11RenderTargetView* Target_ViewPort = Split_Window_Data->second.first;
	// ex) Target_Engine->SetViewPort(Target_ViewPort); 이런식으로..

	return true;
}

void MultiRenderEngine::Render(std::queue<MeshData*>* meshList, GlobalData* global)
{
	BeginRender();

	for (auto _Renderer : Split_Window)
	{
		/// 다음과같이 VeiwPort 전용 랜더를 해주던가 해야된다..
		// ex) _Renderer.second.second->Render(meshList, global);
	}

	EndRender();
}

void MultiRenderEngine::Delete()
{
	Registered_Engine_List.clear();
	Split_Window.clear();
}

MULTIENGINE_DLL void MultiRenderEngine::CreateDevice(HWND hwnd,int screenWidth, int screenHeight)
{
	UINT createDeviceFlags = 0;

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// 스왑 체인 설정을 초기화..
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));

	// swapChainDesc을 단일 백 버퍼로 설정..
	swapChainDesc.BufferCount = 1;

	// 백 버퍼의 너비와 높이를 설정..
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;

	// 백 버퍼에 일반 32 비트 표면을 설정..
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// 백 버퍼의 재생률을 설정..
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	// 스캔 라인 순서 및 배율을 지정되지 않음으로 설정..
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// 백 버퍼의 사용 설정..
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	swapChainDesc.OutputWindow = (HWND)hwnd;

	// 멀티 샘플링을 끕니다..
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = true;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// 추가 플래그 설정 안 함..
	swapChainDesc.Flags = createDeviceFlags;

	// featureLevel을 DirectX 11로 설정..
	D3D_FEATURE_LEVEL featurelevel = D3D_FEATURE_LEVEL_11_0;

	// 스왑 체인, Direct3D 장치 및 Direct3D 장치 컨텍스트 생성..
	/// MSDN에선 SwapChain 과 Device 를 한번에 생성해주는 함수를 지향함..
	HR(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featurelevel, 1,
		D3D11_SDK_VERSION, &swapChainDesc, &m_SwapChain, &m_Device, NULL, &m_DeviceContext));
}

void MultiRenderEngine::BeginRender()
{

}

void MultiRenderEngine::EndRender()
{

}
