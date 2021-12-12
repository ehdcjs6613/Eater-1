#pragma once
#include "PhysEngineDLL.h"


namespace physx
{
	class PxDefaultAllocator;
	class PxDefaultErrorCallback;
	class PxFoundation;
	class PxPhysics;
	class PxDefaultCpuDispatcher;
	class PxScene;
	class PxMaterial;
	class PxRigidDynamic;
	class PxRigidStatic;
	class PxCooking;
	class PxPvd;
	class PxTolerancesScale;
	class PxTransform;
}

class Factory;

class PhysEngine
{
public:
	PhysEngine();
	~PhysEngine();

	//�ʱ�ȭ
	bool Initialize(int ThreadCount,  bool Debug);
	bool CreateScene(bool Debug);
	

	void Release();					
	void Update(float m_time);

	int Create_DinamicActor	(PhysData data);
	int	Create_StaticActor	(PhysData data);
	int	Create_KnematicActor(PhysData data);


	PhysData GetActors(int Index, ACTOR_TYPE type);
private:
	void CreateRigidbody();//���� �浹�ϴ� ��ü�� ����

	bool Initialize_Release(int ThreadCount);
	bool Initialize_Debug(int ThreadCount);
	void CreateStart();

	bool Start = false;


	physx::PxDefaultAllocator*		m_Allocator;
	physx::PxDefaultErrorCallback*	m_ErrorCallback;
	physx::PxTolerancesScale*		m_TolerancesScale;


	physx::PxFoundation*			m_Foundation;
	physx::PxPhysics*				m_Physics;
	physx::PxDefaultCpuDispatcher*	m_Dispatcher;
	physx::PxScene*					m_Scene;
	physx::PxMaterial*				m_Material;
	physx::PxPvd*					m_Pvd;				//������� ����ϱ�����

	Factory* m_Factory;
};