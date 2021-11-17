#include "DebugManager.h"
#include "KeyinputManager.h"

HANDLE DebugManager::hConsole[2];
int	DebugManager::ConsoleIndex = 0;

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
		//�ܼ��� ���۸� �����´�
		hConsole[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		hConsole[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		KeyManager = mkeyManager;

		CONSOLE_CURSOR_INFO cci;
		cci.dwSize = 1;
		cci.bVisible = FALSE;

		SetConsoleCursorInfo(hConsole[0], &cci);
		SetConsoleCursorInfo(hConsole[1], &cci);
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
	
	COORD CursorPosition = { 0, 0 };
	DWORD dw;
	SetConsoleCursorPosition(hConsole[ConsoleIndex], CursorPosition);
	WriteFile(hConsole[ConsoleIndex], Msg.c_str(), Msg.size(), &dw, NULL);
}

void DebugManager::Print(std::string Msg, int X, int Y, MSG_TYPE type, bool Error)
{
	if (DebugON == false) { return; }

	std::string MSG;
	std::string temp;
	switch ((int)type)
	{
	case (int)MSG_TYPE::MSG_LOAD:
		MSG = "[�ε�]" + Msg;
		break;
	case (int)MSG_TYPE::MSG_CREATE:
		MSG = "[����]" + Msg;
		break;
	case (int)MSG_TYPE::MSG_DELETE:
		MSG = "[����]" + Msg;
		break;
	case (int)MSG_TYPE::MSG_ENGINE:
		MSG = "[����]" + Msg;
		break;
	case (int)MSG_TYPE::MSG_ERROR:
		MSG = "[����]" + Msg;
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
	


	COORD CursorPosition = { X, Y };
	DWORD dw;
	SetConsoleCursorPosition(hConsole[ConsoleIndex], CursorPosition);
	WriteFile(hConsole[ConsoleIndex], MSG.c_str(), MSG.size(), &dw, NULL);
}

void DebugManager::Begin()
{
	//�׸��� ����
	COORD CursorPosition = { 0, 0 };
	DWORD dw;
	SetConsoleCursorPosition(hConsole[ConsoleIndex], CursorPosition);
	std::string temp = "����";
	WriteFile(hConsole[ConsoleIndex], temp.c_str(), temp.size(), &dw, NULL);

}

void DebugManager::End()
{
	//ȭ�鿡 ������ �ܼ��� ����Ī ���ش�
	SetConsoleActiveScreenBuffer(hConsole[ConsoleIndex]);

	ConsoleIndex = !ConsoleIndex;
}

void DebugManager::Clear()
{
	//�׸����� �����ش�
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(hConsole[ConsoleIndex], ' ', 80 * 25, Coor, &dw);
}

void DebugManager::Update()
{
	
	

	



}

void DebugManager::Delete()
{
	CloseHandle(hConsole[0]);
	CloseHandle(hConsole[1]);
}


