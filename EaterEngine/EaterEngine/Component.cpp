#include "Component.h"


Component::Component()
{
	gameobject = nullptr;
}

Component::~Component()
{

}

void Component::SetObject(GameObject* obj)
{
	gameobject = obj;
}

