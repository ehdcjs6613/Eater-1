#include "GameObject.h"
#include "Transform.h"
#include "AI.h"

AI::AI()
{

}

AI::~AI()
{

}

void AI::Awake()
{
	

}

void AI::Update()
{
	gameobject->transform->SetRotate(0.01f, 0, 0);
}

