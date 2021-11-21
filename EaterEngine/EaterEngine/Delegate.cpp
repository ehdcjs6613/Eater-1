#include "Delegate.h"

Delegate_Map::Delegate_Map()
{
}

Delegate_Map::~Delegate_Map()
{
}

void Delegate_Map::Push(ComponentFunctionData temp)
{
	FunctionList.push_back(temp);
}

void Delegate_Map::Pop(Component* Key)
{
	int size = (int)FunctionList.size();
	for (int i = 0; i < size; i++)
	{
		if (FunctionList[i].ComponentPoiner == Key)
		{
			FunctionList.erase(FunctionList.begin() + i);
			break;
		}
	}
}

void Delegate_Map::Clear()
{
	FunctionList.clear();
}

void Delegate_Map::Play(bool OnePlay)
{
	int size = (int)FunctionList.size();
	for (int i = 0; i < size; i++)
	{
		//�Լ������Ͱ� ���ٸ� ���
		if (FunctionList[i].FunctionPointer == nullptr) { continue; }
		//����������ٸ� ���
		if (*(FunctionList[i].Enabled) == false) { continue; }


		//�Լ� ����
		FunctionList[i].FunctionPointer();
	}

	//�ѹ��� ����Ǵ� �Լ������Ͷ�� ��� ������ ����
	if (OnePlay == true)
	{
		FunctionList.clear();
	}
}
