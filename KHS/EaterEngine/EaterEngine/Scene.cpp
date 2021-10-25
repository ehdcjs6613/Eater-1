#include "Scene.h"

Scene::Scene()
{
	LinkScene = nullptr;
}
Scene::~Scene()
{

}

void Scene::PushFunction(void(*mAwake)(), void(*mStart)(), void(*mUpdate)(), void(*mEnd)())
{
	AwakeFunction = mAwake;
	StartFunction = mStart;
	UpdateFunction = mUpdate;
	EndFunction = mEnd;
}

void Scene::Awake()
{
	AwakeFunction();
}

void Scene::Start()
{
	StartFunction();
}

void Scene::Update()
{
	UpdateFunction();
}

void Scene::End()
{
	EndFunction();
}