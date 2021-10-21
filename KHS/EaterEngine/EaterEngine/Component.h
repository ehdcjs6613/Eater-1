#pragma once
/// <summary>
/// 컨퍼넌트들의 최상위 클래스
/// </summary>

#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif

class GameObject;
class Component
{
public:
	EATER_ENGINEDLL Component();
	EATER_ENGINEDLL virtual ~Component();

	//시작 단계에 가장먼저 실행되는 함수
	virtual void Awake() {};
	//시작 함수
	virtual void Start() {};
	//처음
	virtual void StartUpdate() {};
	//일반 업데이트
	virtual void Update() {};
	//마지막 업데이트
	virtual void EndUpdate() {};


	unsigned int FUNCTION_MASK = 0x00000000;
public:
	EATER_ENGINEDLL void SetObject(GameObject* obj);
private:
	//이컨퍼넌트를 가지고 있는 게임오브젝트
	GameObject* gameobject;
protected:
};



