#pragma once
#include <windows.h>

/// <summary>
/// 테스트용 임시 디버깅 클래스
/// </summary>
class DebugManager
{
public:
	~DebugManager();
	DebugManager();

	void Initialize();
	void Print(const char* strMsg);
	void Delete();
private:
	static HANDLE hConsole;
};