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

	void AddFunction
	(
		std::function<void()> mAwake,
		std::function<void()> mStart,
		std::function<void()> mUpdate,
		std::function<void()> mEnd
	);

	void TestAddFunction()
	{
		
	}

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void End();


	std::string Name;
	std::function<void()> AwakeFunction;
	std::function<void()> StartFunction;
	std::function<void()> UpdateFunction;
	std::function<void()> EndFunction;
private:

	Scene* LinkScene;
};


