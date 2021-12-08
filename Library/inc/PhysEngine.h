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
}


class PhysEngine
{
public:
	PHYS_ENGINEDLL PhysEngine();
	PHYS_ENGINEDLL ~PhysEngine();

	
	PHYS_ENGINEDLL bool Initialize();	//�ʱ�ȭ
	PHYS_ENGINEDLL void Release();		//����

	

private:
	//�������� ��������� ������ �����Ѵ�
	void CreateRigidbody();//���� �浹�ϴ� ��ü�� ����
	bool CreateScene();

	physx::PxDefaultAllocator*		m_Allocator;
	physx::PxDefaultErrorCallback*	m_ErrorCallback;

	physx::PxFoundation*			m_Foundation;
	physx::PxPhysics*				m_Physics;
	physx::PxDefaultCpuDispatcher*	m_Dispatcher;
	physx::PxScene*					m_Scene;
	physx::PxMaterial*				m_Material;

	//PxRigidStatic* groundPlane;

	//���� ������
	//physx::PxPvd*					gPvd = NULL;

	//PxRigidDynamic* CreateBox();
};