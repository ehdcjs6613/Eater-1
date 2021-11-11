// GameView.cpp: 구현 파일
//

#include "pch.h"
#include "Editor.h"
#include "GameView.h"
#include "afxdialogex.h"


// GameView 대화 상자

IMPLEMENT_DYNAMIC(GameView, CDialogEx)

GameView::GameView(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_VIEW_0, pParent)
{

}

GameView::~GameView()
{
}

void GameView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


// GameView 메시지 처리기



BOOL GameView::Create(UINT nIDTemplate, CWnd* pParentWnd)
{
	return 0;
}


BEGIN_MESSAGE_MAP(GameView, CDialogEx)
END_MESSAGE_MAP()


// GameView 메시지 처리기



