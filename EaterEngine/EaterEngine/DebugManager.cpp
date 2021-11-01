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
	///��������� ��Լ����� ����Ǵ��� �򰥸���� ���� ������
	if (DebugON == false) { return; }

	DWORD dwByte(0);
	std::string Msg;

	Msg += "===============================================================\n";
	Msg += "Eater Engine ������\n";
	Msg += "===============================================================\n";
	Msg += "===============================================================\n";
	Msg += "\n";
	Msg += "______________���� ����_________________\n";
	Msg += "[����]���� ���� �ʱ�ȭ\n";
	Msg += "[Ŭ��]���ӸŴ������� ���� ���� ����\n";
	Msg += "[Ŭ��]���ӸŴ������� ���� ����\n";
	Msg += "[����]������Ʈ �Ŵ��� ������ �Լ�����Ʈ ���� ���� ����\n";
	Msg += "[����]������Ʈ �Ŵ��� ������ ������Ʈ ���� ���� ����\n";
	Msg += "[����]����� ���� Awack,Start �Լ� ����\n";
	Msg += "[����]������ ������Ʈ���� �Լ�����Ʈ�� �����׽��� (Awack,Start)  \n";
	Msg += "[����]������ �Լ�����Ʈ ������� ������Ʈ\n";
	Msg += "[����]������Ʈ�� ����ť�� �׷��ȿ��������� ����\n";
	Msg += "[����]������ ������ ������Ʈ���� �ִٸ� ����\n";


	Msg += "\n";
	Msg += "____________���۳�Ʈ ����_____________\n";
	Msg += "Awake				(�ѹ� ȣ��)\n";
	Msg += "Start				(�ѹ� ȣ��)\n";
	Msg += "StartUpdate			(������ ȣ��)\n";
	Msg += "TransformUpdate			(������ ȣ��)\n";
	Msg += "PhysicsUpdate			(������ ȣ��)\n";
	Msg += "Update				(������ ȣ��)\n";
	Msg += "EndUpdate			(������ ȣ��)\n";
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
		MSG = "[�ε�]" + mMsg;
		break;
	case (int)MSG_TYPE::MSG_CREATE:
		MSG = "[����]" + mMsg;
		break;
	case (int)MSG_TYPE::MSG_DELETE:
		MSG = "[����]" + mMsg;
		break;
	case (int)MSG_TYPE::MSG_ENGINE:
		MSG = "[����]" + mMsg;
		break;
	case (int)MSG_TYPE::MSG_ERROR:
		MSG = "[����]" + mMsg;
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

void DebugManager::Update()
{
	if (DebugON == false) { return; }

	if (KeyManager->GetKeyDown('C'))
	{
		Print("�׽�Ʈ�� �޼���", MSG_TYPE::MSG_ENGINE);
	}
}

void DebugManager::Delete()
{
	

}


