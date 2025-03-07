#include "DebugManager.h"
#include "KeyinputManager.h"
HANDLE DebugManager::hConsole;
bool DebugManager::DebugON = true;
DebugManager::DebugManager()
{
	DebugON = true;
}

DebugManager::~DebugManager()
{
}

void DebugManager::Initialize(KeyinputManager* mkeyManager, bool mDebugOn)
{
	DebugON = mDebugOn;
	if (DebugON == true)
	{
		AllocConsole();
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}
}

void DebugManager::Print(MSG_TYPE type, std::string typeData, std::string msg, bool Error = false)
{
	if (DebugON == false) { return; }

	std::string MSG;
	std::string temp;
	switch ((int)type)
	{
	case (int)MSG_TYPE::MSG_LOAD:
		MSG = "[ Load ][" + typeData + "]"+ msg;
		break;
	case (int)MSG_TYPE::MSG_GET:
		MSG = "[ Get ][" + typeData + "]" + msg;
		break;
	case (int)MSG_TYPE::MSG_DELETE:
		MSG = "[ Delete ][" + typeData + "]" + msg;
		break;
	case (int)MSG_TYPE::MSG_PUSH:
		MSG = "[ Push ][" + typeData + "]" + msg;
		break;
	case (int)MSG_TYPE::MSG_CREATE:
		MSG = "[ Create ][" + typeData + "]" + msg;
		break;
	case (int)MSG_TYPE::MSG_SYSTEM:
		MSG = "[ System ][" + typeData + "]" + msg;
		break;
	}

	if (Error == true)
	{
		temp = "-------------[����]\n";
		MSG += temp;
	}
	else
	{
		temp = "\n";
		MSG += temp;
	}
	

	DWORD dwByte(0);
	WriteFile(hConsole, MSG.c_str(), MSG.size(), &dwByte, NULL);
}

void DebugManager::Line(std::string ObjType)
{
	DWORD dwByte(0);
	std::string temp01 = "-----------------------------------------";
	std::string temp02 = ObjType;
	std::string temp03 = "\n";

	temp01 += temp02;
	temp01 += temp03;
	WriteFile(hConsole, temp01.c_str(), temp01.size(), &dwByte, NULL);
}

void DebugManager::Update()
{


}

void DebugManager::Delete()
{
	

}


