#pragma once
#include <windows.h>

/// <summary>
/// 테스트용 임시 디버깅 클래스
/// </summary>
class DebugManager
{
public:
	~DebugManager();
	void init();
	void Print(const char* strMsg);
	void Delete();

	static DebugManager* GM();
private:
	DebugManager();
	static DebugManager* instance;

	static HANDLE hConsole;
};