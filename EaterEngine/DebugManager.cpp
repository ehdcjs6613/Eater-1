#include "DebugManager.h"
#include "KeyinputManager.h"
HANDLE DebugManager::hConsole;
bool DebugManager::DebugON = true;
DebugManager::DebugManager()
{
	KeyManager = nullptr;
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
		KeyManager = mkeyManager;
	}
}

void DebugManager::printStart()
{
	///어느시점에 어떤함수들이 실행되는지 헷갈릴까봐 엔진 순서도
	if (DebugON == false) { return; }

	DWORD dwByte(0);
	std::string Msg;

	Msg += "===============================================================\n";
	Msg += "Eater Engine 순서도\n";
	Msg += "===============================================================\n";
	Msg += "===============================================================\n";
	Msg += "\n";
	Msg += "______________엔진 순서_________________\n";
	Msg += "[엔진]게임 엔진 초기화\n";
	Msg += "[클라]게임매니저에서 각종 씬을 생성\n";
	Msg += "[클라]게임매니저에서 씬을 선택\n";
	Msg += "[엔진]오브젝트 매니저 이전씬 함수리스트 정보 전부 삭제\n";
	Msg += "[엔진]오브젝트 매니저 이전씬 오브젝트 정보 전부 삭제\n";
	Msg += "[엔진]변경된 씬의 Awack,Start 함수 실행\n";
	Msg += "[엔진]생성된 오브젝트들의 함수리스트를 생성및실행 (Awack,Start)  \n";
	Msg += "[엔진]생성된 함수리스트 기반으로 업데이트\n";
	Msg += "[엔진]업데이트된 랜더큐를 그래픽엔진쪽으로 전달\n";
	Msg += "[엔진]마지막 삭제할 오브젝트들이 있다면 삭제\n";


	Msg += "\n";
	Msg += "____________컨퍼넌트 순서_____________\n";
	Msg += "Awake				(한번 호출)\n";
	Msg += "Start				(한번 호출)\n";
	Msg += "StartUpdate			(프레임 호출)\n";
	Msg += "TransformUpdate			(프레임 호출)\n";
	Msg += "PhysicsUpdate			(프레임 호출)\n";
	Msg += "Update				(프레임 호출)\n";
	Msg += "EndUpdate			(프레임 호출)\n";
	Msg += "------------------------------\n";
	


	WriteFile(hConsole, Msg.c_str(), Msg.size(), &dwByte, NULL);
}

void DebugManager::Print(std::string mMsg, MSG_TYPE type, bool Error)
{
	if (DebugON == false) { return; }

	std::string MSG;
	std::string temp;
	switch ((int)type)
	{
	case (int)MSG_TYPE::MSG_LOAD:
		MSG = "[로드]" + mMsg;
		break;
	case (int)MSG_TYPE::MSG_CREATE:
		MSG = "[생성]" + mMsg;
		break;
	case (int)MSG_TYPE::MSG_DELETE:
		MSG = "[삭제]" + mMsg;
		break;
	case (int)MSG_TYPE::MSG_ENGINE:
		MSG = "[엔진]" + mMsg;
		break;
	case (int)MSG_TYPE::MSG_ERROR:
		MSG = "[에러]" + mMsg;
		break;
	}

	if (Error == true)
	{
		temp = "-------------[실패]\n";
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

void DebugManager::Update()
{
	if (DebugON == false) { return; }

	if (KeyManager->GetKeyDown('C'))
	{
		Print("테스트용 메세지", MSG_TYPE::MSG_ENGINE);
	}
}

void DebugManager::Delete()
{
	

}


