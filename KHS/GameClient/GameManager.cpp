#pragma
#include "MainHeader.h"
#include "GameManager.h"
#include "intro.h"

#pragma comment (lib,"EaterEngine")
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

	CreateScene<intro>("intro");
	ChoiceScene("intro");

	
}

void GameManager::Update()
{
	//�Ѱ��� ��ũ�� �������� ��ũ���� ������Ʈ�� ������
	UpdateEngine();
}