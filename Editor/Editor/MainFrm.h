
// MainFrm.h: CMainFrame 클래스의 인터페이스
//

#pragma once

class CDockalbePannel;
class GameView;
class CGameView;

class SaveData;

class CMainFrame : public CMDIFrameWndEx
{
private:
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame() noexcept;

	//CWnd			 m_pGameView;
	CDockalbePannel* m_pCDockalbePannel[2];
	GameView*		 m_pGameView;
	CGameView*		 m_pCGameView;
// 특성입니다.
public:
	


// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CMFCToolBar          m_wndToolBar;
	CMFCStatusBar        m_wndStatusBar;

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDockTable();
};


