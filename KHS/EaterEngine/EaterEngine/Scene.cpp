#include "Scene.h"

Scene::Scene()
{
	LinkScene = nullptr;
}
Scene::~Scene()
{

}

void Scene::AddFunction(std::function<void()> mAwake, std::function<void()> mStart, std::function<void()> mUpdate, std::function<void()> mEnd)
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