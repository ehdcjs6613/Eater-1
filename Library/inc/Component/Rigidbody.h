#pragma once

#include "EaterEngineDLL.h"
#include "PhysX_API.h"
#include "Component.h"

class Transform;
struct PhysData;
class Rigidbody : public Component
{
public:
	

	EATER_ENGINEDLL Rigidbody();
	EATER_ENGINEDLL ~Rigidbody();

	virtual void Start();
	virtual void TransformUpdate();

	//타입을 정의 한다(static , Dinamic)
	EATER_ENGINEDLL void SetType(bool Dinamic);
	//중력 적용 여부
	EATER_ENGINEDLL void SetGrvity(bool grvity);
	//
	EATER_ENGINEDLL void SetKinematic(bool kinematic);
	//무게를 지정한다
	EATER_ENGINEDLL void SetSetMass(float mass);
	//원하는 축의 방향이동을 고정 시킨다
	EATER_ENGINEDLL void SetFreezePosition(bool x,bool y,bool z);
	//원하는 축의 방향회전을 고정 시킨다 
	EATER_ENGINEDLL void SetFreezeRotation(bool x,bool y,bool z);
	//rigdbody를 이용해서 움직임
	EATER_ENGINEDLL void SetVelocity(float x, float y, float z);
	//Shape Type
	EATER_ENGINEDLL void SetShapeType(int type);

	static const int BOX	= 0;
	static const int SPHERE	= 1;
	static const int CAPSULE = 2;
private:
	Transform* Tr;
	PhysData* RigidbodyData;
};

