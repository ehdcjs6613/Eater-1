#pragma once
#include <windows.h>

/// <summary>
/// �׽�Ʈ�� �ӽ� ����� Ŭ����
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