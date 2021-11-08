#include "GameManager.h"
#include "MainHeader.h"
#include "intro.h"
#include "inGame.h"




GameManager::GameManager()
{
}

GameManager::~GameManager()
{

}

void GameManager::Start(HWND _g_hWnd)
{
	//���� �ʱ�ȭ (�Ŵ����� ����)
	EngineInitialize(_g_hWnd);
	int num = 0;
	

	CreateScene<intro>("intro");
	CreateScene<InGame>("inGame");
	ChoiceScene("intro");

}

void GameManager::Update()
{
	//�Ѱ��� ��ũ�� �������� ��ũ���� ������Ʈ�� ������
	UpdateEngine();
}