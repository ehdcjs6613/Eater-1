#include "PhysX_API.h"
#include "PhysEngine.h"

PhysEngine* Engine = nullptr;
void PhysX_Initialize(int ThreadCount, bool OnDebug)
{
	Engine = new PhysEngine();
	Engine->Initialize(ThreadCount, OnDebug);
}

void PhysX_Release()
{
	if (Engine != nullptr)
	{
		Engine->Release();
	}
}

void PhysX_Update(float m_time)
{
	if (Engine != nullptr)
	{
		Engine->Update(m_time);
	}
}

void PhysX_CreateInstance(PhysData data)
{
	if (Engine != nullptr)
	{
		Engine->CreateStack(data);
	}
}

PhysData GetActors()
{
	if (Engine != nullptr)
	{
		return Engine->GetActors();
	}
}

 void PhysX_CreateScene()
{


}
