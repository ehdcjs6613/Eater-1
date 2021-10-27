#include "DebugManager.h"

HANDLE DebugManager::hConsole;
DebugManager::DebugManager()
{


}

DebugManager::~DebugManager()
{
}

void DebugManager::Initialize()
{
	AllocConsole();
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void DebugManager::Print(const char* strMsg)
{
	DWORD dwByte(0);
	// Ãâ·Â
	WriteFile(hConsole, strMsg, strlen(strMsg), &dwByte, NULL);
}

void DebugManager::Delete()
{


}


