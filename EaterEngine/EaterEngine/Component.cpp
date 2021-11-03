#include "Component.h"


Component::Component()
{
	gameobject = nullptr;
}

Component::~Component()
{

}



void Component::SetConponentType(size_t type)
{
	ComponentType = type;
}

size_t Component::GetConponentType()
{
	return ComponentType;
}

void Component::SetObject(GameObject* obj)
{
	gameobject = obj;
}

