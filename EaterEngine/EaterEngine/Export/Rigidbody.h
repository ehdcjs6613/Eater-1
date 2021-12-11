#pragma once

#include "EaterEngineDLL.h"
#include "PhysX_API.h"
#include "Component.h"

class Transform;
class Rigidbody : public Component
{
public:
	EATER_ENGINEDLL Rigidbody();
	EATER_ENGINEDLL ~Rigidbody();

	virtual void Start();
	virtual void TransformUpdate();
private:
	Transform* Tr;
	PhysTrData* ReturnData;
};

