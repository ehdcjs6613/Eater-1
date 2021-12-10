#include "Rigidbody.h"
#include "Transform.h"
#include "GameObject.h"

Rigidbody::Rigidbody()
{
	Component::TransformUpdate_Order = Component::FUNCTION_ORDER_FIRST;
}

Rigidbody::~Rigidbody()
{

}

void Rigidbody::Start()
{
	Tr = gameobject->GetTransform();


	PhysData data;
	data.Position = { Tr->Position.x,10,Tr->Position.z };
	data.Rotation = { Tr->Rotation.x,Tr->Rotation.y,Tr->Rotation.z };
	data.Scale = { 1,1,1 };

	data.MT_DynamicFriction = 0;
	data.MT_StaticFriction = 0;
	data.MT_Restitution = 1;

	data.Collider_length(COLLIDER_TYPE::BOX, 0.5f);
	data.type = BOX;


	PhysX_CreateInstance(data);
}

void Rigidbody::TransformUpdate()
{
	PhysData temp = GetActors();
	Tr->Position.x = temp.Position.x;
	Tr->Position.y = temp.Position.y;
	Tr->Position.z = temp.Position.z;

	Tr->Q_Rotation.x = temp.Rotation.x;
	Tr->Q_Rotation.y = temp.Rotation.y;
	Tr->Q_Rotation.z = temp.Rotation.z;
	Tr->Q_Rotation.w = temp.Rotation.w;

	
	
}
