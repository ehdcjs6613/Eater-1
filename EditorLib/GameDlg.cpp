#include "LibDefine.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "GameDlg.h"


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


// GameView �޽��� ó����




void GameDlg::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{

}


BEGIN_MESSAGE_MAP(GameDlg, CPaneDialog)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// GameView �޽��� ó����





int GameDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CPaneDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.



	return 0;
}
