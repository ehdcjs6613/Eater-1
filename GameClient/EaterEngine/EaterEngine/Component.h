#pragma once
/// <summary>
/// ���۳�Ʈ���� �ֻ��� Ŭ����
/// </summary>

#include <iostream>
#include <string>

#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

#include "EnumClass.h"
class GameObject;
class Component
{
public:
	EATER_ENGINEDLL Component();
	EATER_ENGINEDLL virtual ~Component();

	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
public:
	
	EATER_ENGINEDLL void SetObject(GameObject* obj);
	EATER_ENGINEDLL	int GetUpdateState();
private:
	//�����۳�Ʈ�� ������ �ִ� ���ӿ�����Ʈ
	GameObject* gameobject;
protected:
	//������Ʈ ������ ��Ű������ ������ �־��� 
	int  UpDateState;
};



