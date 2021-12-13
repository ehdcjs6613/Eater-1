#include "Rigidbody.h"
#include "Transform.h"
#include "GameObject.h"


Rigidbody::Rigidbody()
{
	//���۳�Ʈ ���� ������ ����
	Component::TransformUpdate_Order	= Component::FUNCTION_ORDER_FIRST;
	Component::Start_Order				= Component::FUNCTION_ORDER_LAST;
	RigidbodyData = new PhysData();
}

Rigidbody::~Rigidbody()
{
	delete RigidbodyData;
}

void Rigidbody::Start()
{
	/// ���� ���� �־��ش�
	Tr = gameobject->GetTransform();

	RigidbodyData->WorldPosition	= { Tr->Position.x,Tr->Position.y,Tr->Position.z };
	RigidbodyData->Rotation			= { Tr->Rotation.x,Tr->Rotation.y,Tr->Rotation.z };
	
	RigidbodyData->MT_DynamicFriction	= 0.5f;
	RigidbodyData->MT_StaticFriction	= 0.5f;
	RigidbodyData->MT_Restitution		= 0.6f;

	RigidbodyData->Shape_Size = { Tr->Scale.x,Tr->Scale.y,Tr->Scale.z };

	PhysX_Create_Actor(RigidbodyData);
}

void Rigidbody::TransformUpdate()
{
	PhysData temp;

	PhysX_Update_Actor(RigidbodyData);

	Tr->Position.x = RigidbodyData->WorldPosition.x;
	Tr->Position.y = RigidbodyData->WorldPosition.y;
	Tr->Position.z = RigidbodyData->WorldPosition.z;

	Tr->Q_Rotation.x = RigidbodyData->Rotation.x;
	Tr->Q_Rotation.y = RigidbodyData->Rotation.y;
	Tr->Q_Rotation.z = RigidbodyData->Rotation.z;
	Tr->Q_Rotation.w = RigidbodyData->Rotation.w;
}

 void Rigidbody::SetType(bool Dinamic)
{
	 //��ü�� Ÿ���� �����Ѵ� (Dinamic = �����̴°� , Static = �ȿ����� )
	 //�ڼ��Ѱ� PhysData.h �� �ּ����� ��ֿ�
	 RigidbodyData->isDinamic = Dinamic;
}
void Rigidbody::SetGrvity(bool grvity)
{
	//�߷� �ۿ� ���θ� �����Ѵ� 
	RigidbodyData->isGrvity = grvity;
}

void Rigidbody::SetKinematic(bool kinematic)
{
	RigidbodyData->isKinematic = kinematic;
}

void Rigidbody::SetSetMass(float mass)
{
	RigidbodyData->MT_Mass = mass;
}

void Rigidbody::SetFreezePosition(bool x, bool y, bool z)
{
	RigidbodyData->FreezePositon = { (float)x,(float)y,(float)z };
}

void Rigidbody::SetFreezeRotation(bool x, bool y, bool z)
{
	RigidbodyData->FreezeRotaticon = { (float)x,(float)y,(float)z };
}

void Rigidbody::SetVelocity(float x, float y, float z)
{
	RigidbodyData->Velocity = { x,y,z };
}

 void Rigidbody::SetShapeType(int type)
{
	 RigidbodyData->Shape_type = (SHAPE_TYPE)type;
}



