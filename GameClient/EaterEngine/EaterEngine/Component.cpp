#include "Component.h"

Component::Component()
{
	gameobject = nullptr;
	UpDateState = (int)COMPONENT_STATE::DEFAULT_UPDATE;
}

Component::~Component()
{

}

void Component::SetObject(GameObject* obj)
{
	gameobject = obj;
}

int Component::GetUpdateState()
{
	return UpDateState;
}


