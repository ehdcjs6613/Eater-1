#pragma once

#include <functional>
#include "EngineData.h"
#include <vector>

/// <summary>
///	��ȯ�������� �Լ��������� ������ �������ֱ����� map ���� vector �κ���
/// </summary>
class Component;
class Delegate_Map
{
public:
	Delegate_Map();
	~Delegate_Map();
	
	void Push(ComponentFunctionData temp);
	void Pop(Component* Key);
	void Clear();
	
	//��� �Լ� ������ ����Ʈ ����
	void Play(bool OnePlay = false);
private:
	std::vector<ComponentFunctionData> FunctionList;
};

