#pragma once

/*
	���� ���� ����� ������

	�ϴ���.. �ٸ� ������Ʈ�� ������������� �����ϳ�. ����Ŭ�� lib���ƴϰ�.
	������� �������Ǵµ�. �������� ���簡 �־. ��ũ����. �����غ���� �ذ�����?

	1.����Ŭ�� ������Ʈ���ǵ�ų�, 
	2.���� �����ڵ带 ���� �׽�Ʈ�ϰų�

	2���� ����.
	= ���� Ŭ�� �ƴ� ���� ����� ������ ���� ���� �ξ���� �ʿ䰡 �ִ�.
	
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

