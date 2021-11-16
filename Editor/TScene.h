#pragma once

/*
	따로 씬을 만들어 둔이유

	일단은.. 다른 프로젝트의 헤더파일참조는 가능하나. 게임클라가 lib도아니고.
	헤더파일 접근은되는데. 구현부의 부재가 있어서. 링크에러. 생각해본결과 해결방법은?

	1.게임클라 프로젝트를건들거나, 
	2.같은 구현코드를 만들어서 테스트하거나

	2번을 선택.
	= 게임 클라가 아닌 툴을 만들기 때문에 따로 씬을 두어야할 필요가 있다.
	
*/


#include "Scene.h"


class GameObject;


class TScene : public Scene
{
public:
	TScene();
	~TScene();
public:
	virtual void Awake() override;
	virtual void Start()override;
	virtual void Update()override;
	virtual void End()override;
private:
	GameObject* testobj;
};

