#pragma once


// GameView 대화 상자
class EWGameView;

class GameDlg : public CPaneDialog
{
private:
	DECLARE_DYNAMIC(GameDlg)

public:
	GameDlg();   // 표준 생성자입니다.
	virtual ~GameDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_VIEW_0 };
#endif

protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
