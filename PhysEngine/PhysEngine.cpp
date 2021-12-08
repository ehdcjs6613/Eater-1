#include "PhysEngine.h"
using namespace physx;
PhysEngine::PhysEngine()
{

}

PhysEngine::~PhysEngine()
{

}

void PhysEngine::Initialize()
{
	/// <summary>
	/// https://gameworksdocs.nvidia.com/PhysX/4.0/documentation/PhysXGuide/Manual/Startup.html
	/// </summary>

	//��ü ����
	m_Foundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_Allocator, m_ErrorCallback);
	if (m_Foundation == nullptr)
	{
		//����
	}

	m_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_Foundation, PxTolerancesScale(), true);
}
