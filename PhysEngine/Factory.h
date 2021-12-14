#pragma once

#include "PxPhysicsAPI.h"
namespace physx
{
	class PxPhysics;
	class PxShape;
	class PxSphereGeometry;
	class PxRigidActor;
	class PxRigidDynamic;
	class PxTransform;
	class PxCooking;
}
class PhysData;
class GeometryGenerator;

class Factory
{
public:
	Factory();
	~Factory();

	void Initialize(physx::PxPhysics* Phys, physx::PxScene* Scene,physx::PxCooking* Cooking);

	physx::PxShape* CreateBoxCollider(physx::PxMaterial* m);
	physx::PxShape* CreateBoxCollider(physx::PxMaterial* m ,float x, float y, float z);
	physx::PxShape* CreateBoxCollider(physx::PxMaterial* m, float  Radius);

	physx::PxShape* CreateSphereCollider(physx::PxMaterial* m, float  Radius);

	physx::PxShape* CreateCapsuleCollider(physx::PxMaterial* m, float Radius, float Height);

	physx::PxMaterial* CreateMaterial(float x,float y,float z);
	physx::PxMaterial* CreateMaterial(float length);

	physx::PxTriangleMesh* CreateTriangleCollider();

	void CreateDinamicActor(PhysData* Data, physx::PxShape* shape, physx::PxTransform* Tr);
	void CreateStaticActor(PhysData* Data, physx::PxShape* shape, physx::PxTransform* Tr);
private:
	physx::PxPhysics*	m_Phys;
	physx::PxScene*		m_Scene;
	physx::PxCooking*	m_Cooking;

	GeometryGenerator* m_Geometry;
};

