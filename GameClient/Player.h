#pragma once
#include "Component.h"

class AnimationController;
class Transform;
class MeshFilter;
class Rigidbody;

class Player :public Component
{
public:
	Player();
	virtual ~Player();
	void Awake();
	void Start();
	void Update();
private:
	Transform*	Tr;
	MeshFilter* Mf;
	Rigidbody* ri;
	
	bool Move;
};