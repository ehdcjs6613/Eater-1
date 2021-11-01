#pragma once
#include <windows.h>

class WinApp
{
private:
	HWND	  m_hWnd;
	HINSTANCE m_hInst;
	WNDCLASSEXW m_WnclassEx;
	int m_iWidth;
	int m_iHeight;
	wchar_t m_wcWinName[32];
public:
	WinApp();
	~WinApp();
	

	bool OnWindow();
	bool OnClose();

	bool Initialize(int _wComd);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

