#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "AI.h"

AI::AI()
{

}

AI::~AI()
{

}

void AI::Awake()
{
	trans = gameobject->GetComponent<Transform>();

}

void AI::Update()
{
	trans->SetRotate(1, 0, 1);
}

