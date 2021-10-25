#pragma once

#include <functional>
#include <vector>
#include <map>

/// ////////////////////////////////////////////////////////////////
/// // ����Ƽ�� ��������Ʈ�� �����Ͽ� ������ �Լ� ������ ����Ʈ Ŭ���� //
/// ////////////////////////////////////////////////////////////////
/// 
/// �ΰ��� ��������Ʈ
/// 1.vector �� ����� �Լ������� ����Ʈ
/// 2.map �� ����� �Լ������� ����Ʈ
/// 
/// vector�� ����� �Լ������͸� ����Ұ��� ���������� �������ʿ���°�� ���
/// map�� ����� �Լ������͸� ����Ұ�� �߰��� ��� �Լ������͸� ���������� ���
///
/// ����:https://modoocode.com/254


///1.Map�� ����� �Լ������� ����Ʈ 
class Component;
template<typename T>
class Delegate_Map
{
public:
	Delegate_Map();
	~Delegate_Map();
	
	//Ű���� ������ Map�� ����� �Լ������ͷ� ����Ѵ�
	
	void Push(T* ComponentKey, std::function<void()> temp);
	void Pop(T* Key);
	void Clear();
	

	//��� �Լ� ������ ����Ʈ ����
	void Play();
private:
	std::map<T*,std::function<void()>> FunctionList;
};

template<typename T>
Delegate_Map<T>::Delegate_Map()
{


}

template<typename T>
Delegate_Map<T>::~Delegate_Map()
{


}

template<typename T>
//template<typename Key>
inline void Delegate_Map<T>::Push(T* ComponentKey, std::function<void()> temp)
{
	FunctionList.insert({ ComponentKey,temp });
}

template<typename T>
inline void Delegate_Map<T>::Pop(T* Key)
{
	FunctionList.erase(Key);
}

template<typename T>
inline void Delegate_Map<T>::Clear()
{
	FunctionList.clear();
}

template<typename T>
inline void Delegate_Map<T>::Play()
{
	//map�� ó������ ������ ��ȯ
	auto list = FunctionList.begin();

	while (list != FunctionList.end())
	{
		if (list->second != nullptr)
		{
			list->second();
		}
		++list;
	}
}
