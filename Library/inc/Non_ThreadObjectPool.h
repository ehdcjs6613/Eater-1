#pragma once

#include <queue>

template <class T>
class Non_ThreadObjectPool
{
private:
	int m_Pool_Size = 0;
	std::queue<T*> Object_Manage_Queue;

public:
	Non_ThreadObjectPool(int _Pool_Size = 1000);
	~Non_ThreadObjectPool();

	// ������Ʈ �ϳ��� �޾ƿ�.
	T* GetObject();
	// �ۿ��� �� �� �� �����ڸ� ȣ���� �ʱ�ȭ �Ͽ� �ݳ��ϴ� ���.
	void ResetObject(T* _Used_Object);
	// �ʱⰪ�� �ۿ��� �����ؼ� ť�� �־�� �Ǵ� ���..
	void Non_ResetObject(T* _Used_Object);
};

template <class T>
Non_ThreadObjectPool<T>::Non_ThreadObjectPool(int _Pool_Size /* = 1000 */)
{
	m_Pool_Size = _Pool_Size;
	// Pool_Size ��ŭ �����ؼ� ť�� �־��.
	for (int i = 0; i < _Pool_Size; i++)
	{
		T* Pool_Data = new T;
		Object_Manage_Queue.push(Pool_Data);
	}
}

template <class T>
Non_ThreadObjectPool<T>::~Non_ThreadObjectPool()
{

}

template <class T>
T* Non_ThreadObjectPool<T>::GetObject()
{
	// ť�� ��������� ������ ����.
	if (Object_Manage_Queue.empty())
	{
		for (int i = 0; i < m_Pool_Size / 10; i++)
		{
			T* Pool_Data = new T;
			Object_Manage_Queue.push(Pool_Data);
		}
	}

	T* return_Value = Object_Manage_Queue.front();
	Object_Manage_Queue.pop();

	return return_Value;
}

template <class T>
void Non_ThreadObjectPool<T>::ResetObject(T* _Used_Object)
{
	// �Ҹ��� ȣ��.
	_Used_Object->~T();
	// ������ ȣ��.
	T* Reset_Object = new (_Used_Object) T;

	// �ʱ�ȭ �� push
	Object_Manage_Queue.push(_Used_Object);
}

template <class T>
void Non_ThreadObjectPool<T>::Non_ResetObject(T* _Used_Object)
{
	// �ʱ�ȭ�� �������� �ʰ� push
	Object_Manage_Queue.push(_Used_Object);
}