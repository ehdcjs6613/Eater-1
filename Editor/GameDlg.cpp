// GameView.cpp: 구현 파일
//


#include "framework.h"
#include "Editor.h"
#include "EWGameView.h"
#include "GameDlg.h"
#include "afxdialogex.h"


// GameView 대화 상자

IMPLEMENT_DYNAMIC(GameDlg, CPaneDialog)

GameDlg::GameDlg()
{

}

GameDlg::~GameDlg()
{
}

void GameDlg::DoDataExchange(CDataExchange* pDX)
{
	CPaneDialog::DoDataExchange(pDX);
}


// GameView 메시지 처리기




void GameDlg::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{

}


BEGIN_MESSAGE_MAP(GameDlg, CPaneDialog)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// GameView 메시지 처리기





int GameDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPaneDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.


	
	


	return 0;
}
