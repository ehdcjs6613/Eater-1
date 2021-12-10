#include "PhysEngine.h"
#include "PxPhysicsAPI.h"
#include <vector>
#include <ctype.h>
#include "Broad.h"
#include "Factory.h"

#pragma comment(lib,"PhysX_64.lib")
#pragma comment(lib,"PhysXFoundation_64.lib")
#pragma comment(lib,"PhysXExtensions_static_64.lib")
#pragma comment(lib,"PhysXCooking_64.lib")
#pragma comment(lib,"PhysXCommon_64.lib")
#pragma comment(lib,"PhysXPvdSDK_static_64.lib")

//#pragma comment(lib,"PhysXVehicle_static_64.lib")				//차량
//#pragma comment(lib,"PhysXCharacterKinematic_static_64.lib")	//캐릭터



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

bool PhysEngine::Initialize(int ThreadCount , bool Debug)
{
	/// <summary>
	/// https://gameworksdocs.nvidia.com/PhysX/4.0/documentation/PhysXGuide/Manual/Startup.html
	/// </summary>
	if (Debug == true)
	{
		Initialize_Debug(ThreadCount);
	}
	else
	{
		Initialize_Release(ThreadCount);
	}

	//스크린 생성
	CreateScene(Debug);


	//펙토리 생성
	m_Factory = new Factory();
	m_Factory->Initialize(m_Physics);



	

	return true;
}

void PhysEngine::Release()
{
	//생성의 역순으로 삭제
	m_Dispatcher->release();
	m_Physics->release();
	m_Foundation->release();

	delete m_Allocator;
	delete m_ErrorCallback;
	delete m_TolerancesScale;

	//디버깅일때 삭제
	if (m_Pvd != nullptr)
	{
		PxPvdTransport* transport = m_Pvd->getTransport();
		m_Pvd->release();	m_Pvd = NULL;
		transport->release();
	}
}

void PhysEngine::Update(float m_time)
{
	if (Start == false)
	{
		m_Scene->simulate(0);
		m_Scene->fetchResults(true);
		Start = true;
	}
	else
	{
		m_Scene->simulate(m_time);
		m_Scene->fetchResults(true);
	}
}

void PhysEngine::CreateRigidbody()
{
	Test = new physx::PxTransform(PxVec3(0, 40, 100));


	PxMaterial* pMaterial = m_Physics->createMaterial(0.5f, 0.5f, 0.5f);


	//충돌체 모양을 설정해준다
	// 1. Geometry로 반지름인1인 구 모양을 만든다
	// 2. 충돌재질
	// 3. Actor가 오브젝트를 독점할것인가?
	PxShape* pShape = m_Physics->createShape(PxSphereGeometry(1.0f),*pMaterial,true);
	pShape->setFlag(PxShapeFlag::eVISUALIZATION, true);
	pShape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, true); //ray , sweep 등의 충돌을 검출할때 사용
	
	pShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false); 
	pShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, false);	//Trigger로 사용할것인지 선택 


	//생성한다
	PxRigidDynamic* pActor = m_Physics->createRigidDynamic(*Test);
	pActor->attachShape(*pShape);
	pActor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, false);

	pActor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, false); //중력을 받도록 설정한다
	////위에서 생성한 pShape를 붙여준다
	////Scene에 추가한다
	m_Scene->addActor(*pActor);

}

void PhysEngine::CreateStack(PhysData data)
{
	PxTransform* TR			= new physx::PxTransform(data.Position.x, data.Position.y, data.Position.z);
	PxMaterial* pMaterial	= m_Factory->CreateMaterial(data.MT_StaticFriction, data.MT_DynamicFriction, data.MT_Restitution);
	PxShape* shape			= m_Factory->CreateBoxCollider(pMaterial,data.Col.x, data.Col.y, data.Col.z);

	
	PxRigidDynamic* body = m_Physics->createRigidDynamic(*TR);
	body->attachShape(*shape);
	
	PxRigidBodyExt::updateMassAndInertia(*body, 1.0f);
	m_Scene->addActor(*body);

	shape->release();
}

PhysData  PhysEngine::GetActors()
{
	PxU32 nbActors = m_Scene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC);
	std::vector<PxRigidActor*> actors(nbActors);
	m_Scene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC, reinterpret_cast<PxActor**>(&actors[0]), nbActors);
	
	PxTransform temp = actors[1]->getGlobalPose();

	PhysData test;
	test.Position.x = temp.p.x;
	test.Position.y = temp.p.y;
	test.Position.z = temp.p.z;


	test.Rotation.x = temp.q.x;
	test.Rotation.y = temp.q.y;
	test.Rotation.z = temp.q.z;
	test.Rotation.w = temp.q.w;

	return test;
}

bool PhysEngine::CreateScene(bool Debug)
{
	PxSceneDesc sceneDesc = PxSceneDesc(m_Physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	sceneDesc.cpuDispatcher = m_Dispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	sceneDesc.broadPhaseType	= PxBroadPhaseType::eMBP;
	m_Scene = m_Physics->createScene(sceneDesc);


	if (Debug == true) 
	{
		PxPvdSceneClient* pvdClient = m_Scene->getScenePvdClient();
		if (pvdClient)
		{
			pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
			pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
			pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
		}
	}

	//충돌될 범위를 지정해준다
	PxBroadPhaseRegion regions[4] =
	{
		{	PxBounds3(PxVec3(-100, -100, -100),  PxVec3(0, 100,   0)), reinterpret_cast<void*>(1) },
		{	PxBounds3(PxVec3(-100, -100,    0),  PxVec3(0, 100, 100)), reinterpret_cast<void*>(2) },
		{	PxBounds3(PxVec3(0, -100, -100),  PxVec3(100, 100,   0)), reinterpret_cast<void*>(3) },
		{	PxBounds3(PxVec3(0, -100,    0),  PxVec3(100, 100, 100)), reinterpret_cast<void*>(4) }
	};

	for (PxU32 i = 0; i < 4; i++)
	{
		m_Scene->addBroadPhaseRegion(regions[i]);
	}

	//바닥생성
	m_Material = m_Physics->createMaterial(0.5f, 0.5f, 0.6f);
	PxRigidStatic* groundPlane = PxCreatePlane(*m_Physics, PxPlane(0, 1, 0, 0), *m_Material);
	m_Scene->addActor(*groundPlane);

	return false;
}


bool PhysEngine::Initialize_Release(int ThreadCount)
{
	CreateStart();

	m_Foundation	= PxCreateFoundation(PX_PHYSICS_VERSION, *m_Allocator, *m_ErrorCallback);
	m_Physics		= PxCreatePhysics(PX_PHYSICS_VERSION, *m_Foundation, *m_TolerancesScale);
	m_Dispatcher	= PxDefaultCpuDispatcherCreate(ThreadCount);

	if (m_Foundation == nullptr) { return false; }
	if (m_Physics == nullptr) { return false; }
	if (m_Dispatcher == nullptr) { return false; }

	return true;
}

bool PhysEngine::Initialize_Debug(int ThreadCount)
{
	CreateStart();

	m_Foundation= PxCreateFoundation(PX_PHYSICS_VERSION, *m_Allocator, *m_ErrorCallback);

	//PhysX visual Debugger 와 연결 준비를 한다
	m_Pvd		= PxCreatePvd(*m_Foundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
	m_Pvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

	//physX 생성
	m_Physics	= PxCreatePhysics(PX_PHYSICS_VERSION, *m_Foundation, PxTolerancesScale(), true, m_Pvd);
	PxInitExtensions(*m_Physics, m_Pvd);


	//쓰레드 개수만큼 Phys 를 돌림
	m_Dispatcher = PxDefaultCpuDispatcherCreate(ThreadCount);

	//생성여부 체크
	if (m_Foundation == nullptr) { return false; }
	if (m_Physics == nullptr) { return false; }
	if (m_Dispatcher == nullptr) { return false; }

	return true;
}

void PhysEngine::CreateStart()
{
	m_Allocator			= new PxDefaultAllocator();
	m_ErrorCallback		= new PxDefaultErrorCallback();
	m_TolerancesScale	= new PxTolerancesScale();
}




