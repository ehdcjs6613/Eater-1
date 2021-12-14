#include "Factory.h"
#include "PxPhysicsAPI.h"
#include "PhysData.h"
#include "GeometryGenerator.h"

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


void createRandomTerrain(const PxVec3& origin, PxU32 numRows, PxU32 numColumns,
	PxReal cellSizeRow, PxReal cellSizeCol, PxReal heightScale,
	PxVec3*& vertices, PxU32*& indices)
{
	PxU32 numX = (numColumns + 1);
	PxU32 numZ = (numRows + 1);
	PxU32 numVertices = numX * numZ;
	PxU32 numTriangles = numRows * numColumns * 2;

	if (vertices == NULL)
		vertices = new PxVec3[numVertices];
	if (indices == NULL)
		indices = new PxU32[numTriangles * 3];

	PxU32 currentIdx = 0;
	for (PxU32 i = 0; i <= numRows; i++)
	{
		for (PxU32 j = 0; j <= numColumns; j++)
		{
			PxVec3 v(origin.x + PxReal(j) * cellSizeRow, origin.y, origin.z + PxReal(i) * cellSizeCol);
			vertices[currentIdx++] = v;
		}
	}

	currentIdx = 0;
	for (PxU32 i = 0; i < numRows; i++)
	{
		for (PxU32 j = 0; j < numColumns; j++)
		{
			PxU32 base = (numColumns + 1) * i + j;
			indices[currentIdx++] = base + 1;
			indices[currentIdx++] = base;
			indices[currentIdx++] = base + numColumns + 1;
			indices[currentIdx++] = base + numColumns + 2;
			indices[currentIdx++] = base + 1;
			indices[currentIdx++] = base + numColumns + 1;
		}
	}

	for (PxU32 i = 0; i < numVertices; i++)
	{
		PxVec3& v = vertices[i];
		int num = (rand() % 2);
		v.y += heightScale * num;
	}
}


void Factory::Initialize(physx::PxPhysics* Phys, physx::PxScene* Scene, physx::PxCooking* Cooking)
{
	m_Phys		= Phys;
	m_Scene		= Scene;
	m_Cooking	= Cooking;

	m_Geometry = new GeometryGenerator();
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

PxMaterial* Factory::CreateMaterial(float x, float y, float z)
{
	return m_Phys->createMaterial(x, y, z);
}

PxMaterial* Factory::CreateMaterial(float length)
{
	return m_Phys->createMaterial(length, length, length);
}

physx::PxTriangleMesh* Factory::CreateTriangleCollider()
{
	const PxU32 numColumns = 128;
	const PxU32 numRows = 128;
	const PxU32 numVertices = (numColumns + 1) * (numRows + 1);
	const PxU32 numTriangles = numColumns * numRows * 2;

	PxVec3* vertices = new PxVec3[numVertices];
	PxU32* indices = new PxU32[numTriangles * 3];

	srand(50);

	createRandomTerrain(PxVec3(0.0f, 0.0f, 0.0f), numRows, numColumns, 10.0f, 10.0f, 10.f, vertices, indices);

	PxTriangleMeshDesc meshDesc;
	//버텍스 관련 데이터
	meshDesc.points.count = numVertices;
	meshDesc.points.data = vertices;
	meshDesc.points.stride = sizeof(PxVec3);

	//페이스 관련 데이터
	meshDesc.triangles.count = numTriangles;
	meshDesc.triangles.data = indices;
	meshDesc.triangles.stride =  3 * sizeof(PxU32);

	bool t = m_Cooking->validateTriangleMesh(meshDesc);


	PxDefaultMemoryOutputStream writeBuffer;
	PxTriangleMeshCookingResult::Enum result;
	bool status = m_Cooking->cookTriangleMesh(meshDesc, writeBuffer, &result);
	if (!status)
		return NULL;

	PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
	return m_Phys->createTriangleMesh(readBuffer);
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







