#pragma once

#include "Component.h"

class Transform;

class TKeyInput : public Component
{
public:
	TKeyInput();
	~TKeyInput();
public:
	virtual void Start();
	virtual void Update();

	Transform* transform;
private:
	float mLastMousePosX;
	float mLastMousePosY;
};

