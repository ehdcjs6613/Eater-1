﻿#pragma comment(lib,"winmm")
#include <windows.h>
//#include <digitalv.h>
#include "framework.h"
#include "stdio.h"
#include "GameManager.h"
#include "MainHeader.h"


// 윈도 프로시저의 전방선언
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// 메인 함수
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int nCmdShow)
{
	srand((int)GetTickCount64());
	/// 윈도를 등록한다.
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;			// LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;		// MAKEINTRESOURCEW(IDC_PROJECT1);
	wcex.lpszClassName = L"PROJECT1";
	wcex.hIconSm = NULL;			//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassExW(&wcex);

	//현재 모니터의 최대 크기 해상도
	int Width = GetSystemMetrics(SM_CXSCREEN);     // 현재 모니터 가로 해상도
	int Height = GetSystemMetrics(SM_CYSCREEN);    // 현재 모니터 세로 해상도

	// 애플리케이션 초기화를 수행합니다:
	HWND hWnd = CreateWindowW(L"PROJECT1", L"EngineTestClient", WS_OVERLAPPEDWINDOW,
		0, 0, 1920, 1080, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	MSG msg;

	GameManager* GM = new GameManager();
	GM->Start(hWnd);


	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
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
			GM->Update();
		}
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_SIZE:
	{
		int SizeX = LOWORD(lParam);
		int SizeY = HIWORD(lParam);
		OnReSize(SizeX, SizeY);
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

