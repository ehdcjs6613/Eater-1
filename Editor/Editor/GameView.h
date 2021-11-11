#pragma once


// GameView 대화 상자

class GameView : public CDialogEx
{
	DECLARE_DYNAMIC(GameView)

public:
	GameView(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~GameView();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_VIEW_0 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg virtual BOOL Create(UINT nIDTemplate, CWnd* pParentWnd);
};
