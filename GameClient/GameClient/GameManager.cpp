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
	
	//스크린을 생성
	CreateScene("Intro", Intro_Awake, Intro_Start, Intro_Update, Intro_End);
	CreateScene("InGame", InGame_Awake, InGame_Start, InGame_Update, InGame_End);

	ChoiceScene("InGame");
	StartScene();
}

void GameManager::Update()
{
	//넘겨준 스크린 바탕으로 스크린의 업데이트를 돌려줌
	UpdateEngine();
}