#pragma once
#include <vector>
/// <summary>
/// vector 형 함수포인트 리스트
/// </summary>
 
 

template<typename T>
class Delegate
{
public:
	Delegate();
	~Delegate();

private:
	std::vector<void(T)> FunctionList;
};

template<typename T>
inline Delegate<T>::Delegate()
{

}

template<typename T>
inline Delegate<T>::~Delegate()
{

}
