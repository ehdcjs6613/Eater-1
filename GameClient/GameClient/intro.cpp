#include "Scene.h"
#include "intro.h";
#include "MainHeader.h"
#include "GameObject.h"
#include "MeshFilter.h"
#include "Transfrom.h"
#include "AI.h"

void Intro_Awake()
{
	GameObject* obj = CreateGameObject();
	obj->AddComponent<Transfrom>();
	obj->AddComponent<MeshFilter>();
	obj->AddComponent<AI>();
}

void Intro_Start()
{


}

void Intro_Update()
{



}

void Intro_End()
{



}

void InGame_Awake()
{
	GameObject* obj = CreateGameObject();
	obj->AddComponent<Transfrom>();
	obj->AddComponent<MeshFilter>();
}

void InGame_Start()
{



}

void InGame_Update()
{



}


void InGame_End()
{



}
