#pragma once


// GameView ��ȭ ����
class EWGameView;

#ifdef DEBUG
AFX_EXT_CLASS
#else
AFX_EXT_CLASS

#endif // DEBUG


class  GameDlg : public CPaneDialog
{
private:
	DECLARE_DYNAMIC(GameDlg)

public:
	GameDlg();   // ǥ�� �������Դϴ�.
	virtual ~GameDlg();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_VIEW_0 };
#endif

protected:

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
