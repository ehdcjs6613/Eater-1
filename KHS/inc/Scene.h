#pragma once

#include <functional>
#include <string>

/// <summary>
/// 생성은 엔진쪽에서 생성할때 이름과 함수포인터들만 넘겨주고 생성과삭제는 스크린매니저에서 해준다
/// </summary>

#ifdef ENGINE_INTERFACE
#define EATER_ENGINEDLL __declspec(dllexport)
#else
#define EATER_ENGINEDLL __declspec(dllimport)
#endif


class Scene
{
public:
	EATER_ENGINEDLL Scene();
	EATER_ENGINEDLL virtual ~Scene();

	//스크린을 넣어주면 
	EATER_ENGINEDLL void PushFunction(void(*mAwake)(), void(*mStart)(), void(*mUpdate)(), void(*mEnd)());

	
	template<typename T>
	EATER_ENGINEDLL void AddFunction();

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void End();


	std::string Name;
private:
	std::function<void()> AwakeFunction;
	std::function<void()> StartFunction;
	std::function<void()> UpdateFunction;
	std::function<void()> EndFunction;

	Scene* LinkScene;
};

template<typename T>
inline void Scene::AddFunction()
{
	T* temp = new T();
	
	AwakeFunction = std::bind(&T::Awake,	temp);
	StartFunction = std::bind(&T::Start,	temp);
	UpdateFunction = std::bind(&T::Update,	temp);
	EndFunction = std::bind(&T::End,		temp);
}

