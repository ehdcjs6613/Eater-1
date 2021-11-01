#pragma once
/// <summary>
/// 컨퍼넌트들의 최상위 클래스
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
	//이컨퍼넌트를 가지고 있는 게임오브젝트
	GameObject* gameobject;
protected:
	//업데이트 순서를 지키기위해 순서를 넣어줌 
	int  UpDateState;
};



