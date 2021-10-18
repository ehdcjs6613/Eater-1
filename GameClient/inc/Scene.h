#pragma once

#include <functional>
#include <string>

/// <summary>
/// 생성은 엔진쪽에서 생성할때 이름과 함수포인터들만 넘겨주고 생성과삭제는 스크린매니저에서 해준다
/// </summary>
class Scene
{
public:
	Scene();
	virtual ~Scene();

	//스크린을 넣어주면 
	void PushFunction(void(*mAwake)(), void(*mStart)(), void(*mUpdate)(), void(*mEnd)());
	void Awake();
	void Start();
	void Update();
	void End();

	std::string Name;
private:
	std::function<void()> AwakeFunction;
	std::function<void()> StartFunction;
	std::function<void()> UpdateFunction;
	std::function<void()> EndFunction;
};