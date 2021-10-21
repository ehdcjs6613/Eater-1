#include "DebugManager.h"

DebugManager* DebugManager::instance = nullptr;
HANDLE DebugManager::hConsole;
DebugManager::DebugManager()
{


}

DebugManager::~DebugManager()
{
}

void DebugManager::init()
{
	if (instance == nullptr)
	{
		instance = new DebugManager();
		AllocConsole();
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}
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

DebugManager* DebugManager::GM()
{
	if (instance == nullptr)
	{
		instance = new DebugManager();
		AllocConsole();
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	return instance;
}
