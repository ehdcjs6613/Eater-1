#pragma once
#include "Component.h"

class AnimationController;
class Transform;
class MeshFilter;

class Player :public Component
{
public:
	Player();
	~Player();

	void Awake();
	void Start();

private:
	AnimationController* AC;
	Transform*	Tr;
	MeshFilter* Mf;


};