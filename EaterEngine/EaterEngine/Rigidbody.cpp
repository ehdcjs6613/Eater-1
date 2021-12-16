#include "Rigidbody.h"
#include "Transform.h"
#include "GameObject.h"
#include "PhysData.h"
#include "PhysX_API.h"
#include "LoadManager.h"
#include "EngineData.h"
#include "PhysData.h"

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

	RigidbodyData->SetWorldPosition(Tr->Position.x, Tr->Position.y, Tr->Position.z);
	RigidbodyData->SetRotation(Tr->Rotation.x, Tr->Rotation.y, Tr->Rotation.z);

	PhysX_Create_Actor(RigidbodyData);
}

void Rigidbody::TransformUpdate()
{
	PhysX_Update_Actor(RigidbodyData);

	Tr->Position.x = RigidbodyData->WorldPosition.x;
	Tr->Position.y = RigidbodyData->WorldPosition.y;
	Tr->Position.z = RigidbodyData->WorldPosition.z;

	Tr->Q_Rotation.x = RigidbodyData->Rotation.x;
	Tr->Q_Rotation.y = RigidbodyData->Rotation.y;
	Tr->Q_Rotation.z = RigidbodyData->Rotation.z;
	Tr->Q_Rotation.w = RigidbodyData->Rotation.w;

	//if (mKeyInputManger->GetKey(VK_RIGHT))
	//{
	//	RigidbodyData->Velocity.x = 0.1f;
	//	RigidbodyData->Velocity.y = PhysX_GetGrvity();
	//}
	//else if(mKeyInputManger->GetKey(VK_LEFT))
	//{
	//	RigidbodyData->Velocity.x = -0.1f;
	//}
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
	//RigidbodyData->FreezePositon = { (float)x,(float)y,(float)z };
}

void Rigidbody::SetFreezeRotation(bool x, bool y, bool z)
{
	//RigidbodyData->FreezeRotaticon = { (float)x,(float)y,(float)z };
}

void Rigidbody::SetVelocity(float x, float y, float z)
{
	//RigidbodyData->Velocity = { x,y,z };
}

 void Rigidbody::SetTranlate(float x, float y, float z)
{
	 RigidbodyData->SetTranlate(x, y, z);
}

 void Rigidbody::SetAddForce(float x, float y, float z)
 {
	 RigidbodyData->AddForce(x, y, z);
 }

 void Rigidbody::CreateBoxCollider(float x, float y, float z)
{
	 RigidbodyData->CreateBoxCollider(x, y, z);
}

 void Rigidbody::CreateBoxCollider(float Radius)
{
	 RigidbodyData->CreateBoxCollider(Radius);
}

 void Rigidbody::CreateSphereCollider(float Radius)
{
	 RigidbodyData->CreateSphereCollider(Radius);
}

 void Rigidbody::CreateCapsuleCollider(float Radius, float Height)
{
	 RigidbodyData->CreateCapsuleCollider(Radius, Height);
}

 void Rigidbody::CreateTriangleCollider(std::string MeshName)
 {
	 ModelData* data = LoadManager::GetMesh(MeshName);

	 TriangleMeshData* TRData = new TriangleMeshData();
	 TRData->IndexList	= &(data->TopMeshList[0]->Index_List);
	 TRData->VertexList = &(data->TopMeshList[0]->Vertex_List);

	 RigidbodyData->CreateTriangleCollider(TRData);
 }




