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
		if (FunctionList[i].ComponentPointer == Key)
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
	int Index = 0;
	while(true)
	{
		//����Ʈ�� ���� �ٵ��Ҵٸ�
		if (Index == (int)FunctionList.size())
		{
			break;;
		}

		if (FunctionList[Index].FunctionPointer == nullptr) { continue; }
		if (*(FunctionList[Index].Enabled) == false){ continue; }

		//�Լ� ����
		FunctionList[Index].FunctionPointer();
		Index++;
	}

	//�ѹ��� ����Ǵ� �Լ������Ͷ�� ��� ������ ����
	if(OnePlay == true)
	{
		FunctionList.clear();
		int num = 0;
	}
}
