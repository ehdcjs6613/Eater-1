#pragma once
#include <windows.h>
#include <string>
#include "EnumClass.h"
/// <summary>
/// 테스트용 임시 디버깅 클래스
/// </summary>
class KeyinputManager;
class DebugManager
{
public:
	~DebugManager();
	DebugManager();

	enum class MSG_TYPE
	{
		MSG_LOAD,
		MSG_CREATE,
		MSG_DELETE,
		MSG_ENGINE,
		MSG_ERROR,
	};

	void Initialize(KeyinputManager* mkeyManager,bool mDebugOn);
	void printStart();
	static void Print(std::string Msg, MSG_TYPE type,bool Error = false);
	void Update();
	void Delete();
private:
	static HANDLE hConsole;
	KeyinputManager* KeyManager;
	static bool DebugON;
};