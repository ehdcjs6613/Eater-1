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
	gameobject->transform->SetRotate(0, 0, 0.01f);
	//gameobject->transform->SetScale(0.1f, 0, 0);
}

