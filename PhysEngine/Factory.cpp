#include "Factory.h"
#include "PxPhysicsAPI.h"
#include "PhysData.h"

using namespace physx;
Factory::Factory()
{
	m_Phys = nullptr;
	m_Scene = nullptr;
}

Factory::~Factory()
{
	m_Phys = nullptr;
	m_Scene = nullptr;
}

void Factory::Initialize(physx::PxPhysics* Phys, physx::PxScene* Scene)
{
	m_Phys = Phys;
	m_Scene = Scene;
}

PxShape* Factory::CreateBoxCollider(PxMaterial* m)
{
	PxBoxGeometry temp = PxBoxGeometry();
	PxShape* shape = m_Phys->createShape(temp, *m);
	return shape;
}

PxShape* Factory::CreateBoxCollider( PxMaterial* m,float x,float y,float z)
{
	PxBoxGeometry temp = PxBoxGeometry(PxReal(x), PxReal(y), PxReal(z));
	PxShape* shape = m_Phys->createShape(temp, *m);
	return shape;
}

PxShape* Factory::CreateBoxCollider(PxMaterial* m,float length)
{
	PxBoxGeometry temp = PxBoxGeometry(PxReal(length), PxReal(length), PxReal(length) );
	PxShape* shape = m_Phys->createShape(temp, *m);
	return shape;
}


PxMaterial* Factory::CreateMaterial()
{
	return m_Phys->createMaterial(0, 0, 0);
}

PxMaterial* Factory::CreateMaterial(float x, float y, float z)
{
	return m_Phys->createMaterial(x, y, z);
}

PxMaterial* Factory::CreateMaterial(float length)
{
	return m_Phys->createMaterial(length, length, length);
}

physx::PxShape* Factory::CreateSphereCollider(physx::PxMaterial* m, float length)
{
	PxSphereGeometry temp = PxSphereGeometry(PxReal(length));
	PxShape* shape = m_Phys->createShape(temp, *m);
	return shape;
}

physx::PxShape* Factory::CreateCapsuleCollider(physx::PxMaterial* m, float Radius, float Height)
{
	physx::PxTransform T = physx::PxTransformFromSegment(physx::PxVec3(1, 1, 1), physx::PxVec3(0, 1, 0));

	PxCapsuleGeometry temp = PxCapsuleGeometry(PxReal(Radius), PxReal(Height));
	PxShape* shape = m_Phys->createShape(temp, *m);
	
	return shape;
}

void Factory::CreateDinamicActor(PhysData* Data, physx::PxShape* shape, physx::PxTransform* Tr)
{
	Tr->rotate(physx::PxVec3(45, 45, 45));
	Tr->transform(PxVec3(10, 0, 0));

	PxRigidDynamic* body = m_Phys->createRigidDynamic(*Tr);

	shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, true);
	shape->setFlag(PxShapeFlag::eVISUALIZATION,true); //Ray, sweep등 할때 사용됨
	shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE,false);

	body->attachShape(*shape);

	physx::PxVec3 temp = physx::PxVec3(Data->CenterPoint.x, Data->CenterPoint.y, Data->CenterPoint.z);

	PxRigidBodyExt::updateMassAndInertia(*body, Data->MT_Mass,&temp);
	m_Scene->addActor(*body);

	//서로 연결
	body->userData = Data;
	Data->ActorObj = body;

	body->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC,Data->isKinematic);
	body->setActorFlag(PxActorFlag::eDISABLE_GRAVITY ,!Data->isGrvity);
	int num = 0;
}

void Factory::CreateStaticActor(PhysData* Data, physx::PxShape* shape, physx::PxTransform* Tr)
{
	PxRigidStatic* body = m_Phys->createRigidStatic(*Tr);
	body->attachShape(*shape);
	m_Scene->addActor(*body);

	//서로 연결
	body->userData = Data;
	Data->ActorObj = body;
}





