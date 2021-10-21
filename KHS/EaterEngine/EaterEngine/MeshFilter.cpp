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
	DebugManager::GM()->Print("MeshFilter Awake 함수 실행 \n");
}

void MeshFilter::Update()
{
	DebugManager::GM()->Print("MeshFilter Update 함수 실행 \n");
}

void MeshFilter::Start()
{
	DebugManager::GM()->Print("MeshFilter Start 함수 실행 \n");
}



