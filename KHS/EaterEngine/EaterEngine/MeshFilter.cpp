#include "MeshFilter.h"
#include "DebugManager.h"
MeshFilter::MeshFilter()
{
}

MeshFilter::~MeshFilter()
{
}

void MeshFilter::Awake()
{
	DebugManager::GM()->Print("MeshFilter Awake �Լ� ���� \n");
}

void MeshFilter::Update()
{
	DebugManager::GM()->Print("MeshFilter Update �Լ� ���� \n");
}

void MeshFilter::Start()
{
	DebugManager::GM()->Print("MeshFilter Start �Լ� ���� \n");
}



