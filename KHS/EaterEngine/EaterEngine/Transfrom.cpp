#include "Component.h"
#include "Transfrom.h"
#include "DebugManager.h"

Transfrom::Transfrom()
{
	
}

Transfrom::~Transfrom()
{

}


void Transfrom::Awake()
{
	DebugManager::GM()->Print("Transfrom Awake 함수 실행 \n");
}

void Transfrom::Start()
{
	DebugManager::GM()->Print("Transfrom Start 함수 실행 \n");
}

void Transfrom::Update()
{
	DebugManager::GM()->Print("Transfrom Update 함수 실행 \n");
}


