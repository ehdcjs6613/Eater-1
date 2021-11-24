#pragma once
#include "Component.h"

class AnimationController;
class Transform;
class MeshFilter;

class Player: public Component
{
public:
	void Awake();
	void Start();
	void Update();

private:

	AnimationController* AC;
	Transform* Tr;
	MeshFilter* Mf;
};