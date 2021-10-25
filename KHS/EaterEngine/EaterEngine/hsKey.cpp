#include "windows.h"
#include "Conio.h"
#include "hsKey.h"

hsKey::hsKey()
{
	for (int i = 0; i < 256; i++)
	{
		isCurrent[i] = false;
		isPrev[i] = false;
		isDown[i] = false;
		isUp[i] = false;
		isToggle[i] = false;
	}
}

hsKey::~hsKey()
{

}

bool hsKey::GetKey(byte _keyNum)
{
	return isCurrent[_keyNum];
}

bool hsKey::GetKeyDown(byte _keyNum)
{
	return isDown[_keyNum];
}

bool hsKey::GetKeyUp(byte _keyNum)
{
	return isUp[_keyNum];
}

bool hsKey::GetKeyToggle(byte _keyNum)
{
	return isToggle[_keyNum];
}

void hsKey::KeyUpDate()
{
	for (int i = 0; i < 256; i++)
	{
		if (GetAsyncKeyState(i))
		{
			isCurrent[i] = true; //����� ���ȴ�
			if (isPrev[i] == false) //����� ���Ȱ� ���Ŵ� �ȴ�������
			{
				if (isToggle[i] == true)
				{
					isToggle[i] = false;
				}
				else
				{
					isToggle[i] = true;
				}

				isDown[i] = true;
			}
			else if (isPrev[i] == true)//����� ���Ȱ� ���ſ��� ��������
			{
				isDown[i] = false;
			}
		}
		else//���翡 �ȴ�������
		{
			isCurrent[i] = false;
			if (isPrev[i] == false) //����� �ȴ��Ȱ� ���ſ��� �ȴ�������
			{
				isUp[i] = false;
			}
			else if (isPrev[i] == true) //����� �ȴ��Ȱ� ���ſ��� ��������
			{
				isUp[i] = true;
			}
		}
		isPrev[i] = isCurrent[i];
	}

	int num = 0;
}

void hsKey::UpdataMouseCursor(HWND hwnd)
{
	GetCursorPos(&CursorPos);
	ScreenToClient(hwnd,&CursorPos);
}

 const LPPOINT hsKey::GetMousePos()
{
	return &CursorPos;
}


