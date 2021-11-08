#include "Transform.h"
#include "AI.h"
#include "GameObject.h"

AI::AI()
{

}

AI::~AI()
{

}

void AI::Awake()
{
	
	gameobject->transform->SetRotate(90, 0, 0);
}

void AI::Update()
{
	gameobject->transform->SetRotate(0, 0.01f, 0);
}

