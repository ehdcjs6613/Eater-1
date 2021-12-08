#pragma once
#include "PhysEngineDLL.h"
class PhysEngine
{
public:
	PHYS_ENGINEDLL PhysEngine();
	PHYS_ENGINEDLL ~PhysEngine();

	//�ʱ�ȭ
	PHYS_ENGINEDLL void Initialize();
private:
	physx::PxDefaultAllocator		m_Allocator;
	physx::PxDefaultErrorCallback	m_ErrorCallback;
	physx::PxFoundation*			m_Foundation = NULL;
	physx::PxPhysics*				m_Physics = NULL;
	physx::PxDefaultCpuDispatcher*	m_Dispatcher = NULL;
	physx::PxScene*					m_Scene = NULL;
	physx::PxMaterial*				m_Material = NULL;

	//���� ������
	//physx::PxPvd*					gPvd = NULL;
};