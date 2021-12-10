#include "PhysEngine.h"
#include "PxPhysicsAPI.h"
#include <ctype.h>

#pragma comment(lib,"PhysX_64.lib")
#pragma comment(lib,"PhysXFoundation_64.lib")
#pragma comment(lib,"PhysXExtensions_static_64.lib")
//#pragma comment(lib,"PhysXVehicle_static_64.lib") //����
//#pragma comment(lib,"PhysXCharacterKinematic_static_64.lib")
#pragma comment(lib,"PhysXCooking_64.lib")


//PhysXExtensions_static_64.lib
//e\PhysX_64.lib
//e\PhysXPvdSDK_static_64.lib
//e\PhysXVehicle_static_64.lib
//e\PhysXCharacterKinematic_static_64.lib
//e\PhysXCooking_64.lib
//e\PhysXCommon_64.lib
//e\SnippetUtils_static_64.lib
//e\SnippetRender_static_64.lib
//e\PhysXFoundation_64.lib

using namespace physx;
PhysEngine::PhysEngine()
{
	m_Foundation	= nullptr;
	m_Physics		= nullptr;
	m_Dispatcher	= nullptr;
	m_Scene			= nullptr;
	m_Material		= nullptr;
}

PhysEngine::~PhysEngine()
{

}

bool PhysEngine::Initialize()
{
	/// <summary>
	/// https://gameworksdocs.nvidia.com/PhysX/4.0/documentation/PhysXGuide/Manual/Startup.html
	/// </summary>
	//physx::PxDefaultAllocator		m_Allocator;
	//physx::PxDefaultErrorCallback	m_ErrorCallback;
	m_Allocator = new PxDefaultAllocator();
	m_ErrorCallback = new physx::PxDefaultErrorCallback();

	//PxFoundation �� ���μ��� �� 1�� ����
	m_Foundation = PxCreateFoundation(PX_PHYSICS_VERSION, *m_Allocator, *m_ErrorCallback);
	m_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_Foundation, PxTolerancesScale(), false);
	m_Dispatcher = PxDefaultCpuDispatcherCreate(2);

	if (m_Foundation == nullptr){return false;}
	if (m_Physics == nullptr){return false;}
	if (m_Dispatcher == nullptr){return false;}

	//��ũ�� ����
	CreateScene();

	//CreateRigidbody();
	return true;
}

void PhysEngine::Release()
{
	//������ �������� ����
	m_Dispatcher->release();
	m_Physics->release();
	m_Foundation->release();
}

void PhysEngine::CreateRigidbody()
{
	PxTransform transform = PxTransform(PxVec3(0,0,0), PxQuat(0,0,0,0));
	

	PxMaterial* pMaterial = m_Physics->createMaterial(0.5f, 0.5f, 0.5f);


	//�浹ü ����� �������ش�
	// 1. Geometry�� ��������1�� �� ����� �����
	// 2. �浹����
	// 3. Actor�� ������Ʈ�� �����Ұ��ΰ�?
	PxShape* pShape = m_Physics->createShape(PxSphereGeometry(1.0f),*pMaterial);

	pShape->setFlag(PxShapeFlag::eVISUALIZATION, true);
	pShape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, true); //ray , sweep ���� �浹�� �����Ҷ� ���

	pShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false); 
	pShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, false);	//Trigger�� ����Ұ����� ���� 


	//�����Ѵ�
	PxRigidDynamic* pActor = m_Physics->createRigidDynamic(transform);
	pActor->attachShape(*pShape);
	pActor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, false);
	
	pActor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false); //�߷��� �޵��� �����Ѵ�
	////������ ������ pShape�� �ٿ��ش�
	////Scene�� �߰��Ѵ�
	m_Scene->addActor(*pActor);
}

bool PhysEngine::CreateScene()
{
	PxSceneDesc sceneDesc(m_Physics->getTolerancesScale());

	//�߷� ����
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	sceneDesc.cpuDispatcher = m_Dispatcher;

	//�ùķ��̼� �߿� �浹 �̺�Ʈ �Լ��� ���ǵ� Ŭ����������
	//sceneDesc.simulationEventCallback = NULL;

	//�ùķ��̼� �߿� ����� ���� �Լ�(����� ����Ʈ)
	sceneDesc.filterShader		= PxDefaultSimulationFilterShader;
	sceneDesc.broadPhaseType	= PxBroadPhaseType::eMBP;

	//��ũ�� ����
	m_Scene = m_Physics->createScene(sceneDesc);

	//�ٴڻ���
	m_Material = m_Physics->createMaterial(0.5f, 0.5f, 0.6f);
	PxRigidStatic* groundPlane = PxCreatePlane(*m_Physics, PxPlane(0, 1, 0, 0), *m_Material);
	m_Scene->addActor(*groundPlane);

	return false;
}


