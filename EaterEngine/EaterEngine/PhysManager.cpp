#include "PhysManager.h"
#include "PhysEngine.h"

PhysManager::PhysManager()
{
	Phys = nullptr;
}

PhysManager::~PhysManager()
{

}

void PhysManager::Initialize()
{
	Phys = new PhysEngine();
	Phys->Initialize();
}

void PhysManager::Release()
{
	//Phys->Release();
}

void PhysManager::Update()
{
	Phys->Run();
}

