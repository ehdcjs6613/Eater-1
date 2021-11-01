#include "WinApp.h"


int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	WinApp App;
	App.Initialize(nShowCmd);



	return 0;
}



WinApp::WinApp() : m_hInst(nullptr), m_hWnd(nullptr), m_iWidth(0), m_iHeight(0), m_wcWinName{}, m_WnclassEx{}
{

}

WinApp::~WinApp()
{

}

bool WinApp::OnWindow()
{
	MSG msg;
	while (true)
	{
		if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		else
		{
			//Update
		}

	}
	return 0;
}

bool WinApp::OnClose()
{
	return 0;
}

bool WinApp::Initialize(int _wComd)
{
	
	m_WnclassEx.cbSize = sizeof(WNDCLASSEX);
	m_WnclassEx.style = CS_HREDRAW | CS_VREDRAW;
	m_WnclassEx.lpfnWndProc = WinApp::WndProc;
	m_WnclassEx.cbClsExtra = 0;
	m_WnclassEx.cbWndExtra = 0;
	m_WnclassEx.hInstance = m_hInst;
	m_WnclassEx.hIcon = NULL;											// LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT1));
	m_WnclassEx.hCursor = LoadCursor(nullptr, IDC_ARROW);
	m_WnclassEx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //(COLOR_WINDOW + 1);
	m_WnclassEx.lpszMenuName = NULL;								// MAKEINTRESOURCEW(IDC_PROJECT1);
	m_WnclassEx.lpszClassName = L"PROJECT1";
	m_WnclassEx.hIconSm = NULL;									 //LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		//현재 모니터의 최대 크기 해상도
	m_iWidth  = GetSystemMetrics(SM_CXSCREEN);     // 현재 모니터 가로 해상도
	m_iHeight = GetSystemMetrics(SM_CYSCREEN);    // 현재 모니터 세로 해상도

	if ( (m_hWnd = CreateWindowW(L"WJEngine", L"WJEngine Test", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080, nullptr, nullptr, m_hInst, nullptr)))
	{
		ShowWindow(m_hWnd, _wComd);
		UpdateWindow(m_hWnd);
	}
	else
	{
		return -1;
	}
	

	return 0;
}

LRESULT WinApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SIZE:
	{
		int SizeX = LOWORD(lParam);
		int SizeY = HIWORD(lParam);

		//Engine->OnResize(SizeX, SizeY);
		break;

	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
		PAINTSTRUCT pr;
		BeginPaint(hWnd, &pr);
		EndPaint(hWnd, &pr);
		break;
	case WM_MOUSEMOVE:
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
