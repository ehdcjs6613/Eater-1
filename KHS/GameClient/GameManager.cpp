#pragma 
#include "MainHeader.h"
#include "GameManager.h"
#include "intro.h"

#pragma comment (lib,"../lib/EaterEngine")
GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

void GameManager::Start()
{
	//엔진 초기화 (매니저들 생성)
	StartEngine();

	CreateScene("Intro")->AddFunction<intro>();
	CreateScene("InGame")->AddFunction<intro>();
 	




	ChoiceScene("Intro");
	StartScene();
	
}

void GameManager::Update()
{
	//넘겨준 스크린 바탕으로 스크린의 업데이트를 돌려줌
	UpdateEngine();
}