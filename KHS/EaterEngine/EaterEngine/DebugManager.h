#pragma once
#include <windows.h>

/// <summary>
/// �׽�Ʈ�� �ӽ� ����� Ŭ����
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