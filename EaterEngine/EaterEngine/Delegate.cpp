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
		//리스트를 전부 다돌았다면
		if (Index == (int)FunctionList.size())
		{
			break;;
		}

		if (FunctionList[Index].FunctionPointer == nullptr) { continue; }
		if (*(FunctionList[Index].Enabled) == false){ continue; }

		//함수 실행
		FunctionList[Index].FunctionPointer();
		Index++;
	}

	//한번만 실행되는 함수포인터라면 모두 실행후 삭제
	if(OnePlay == true)
	{
		FunctionList.clear();
		int num = 0;
	}
}
