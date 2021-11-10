// MainFrm.h: CMainFrame 클래스의 인터페이스
//
#pragma once

class CGameEditorView;

/// <summary>
/// 메인 프레임윈도우 클레스이다.
/// 주로 작업할 화면이긴한데 뷰를 생성 하지만. 뷰의 역할은아니다.
/// 프레임윈도우의 '기능'을제공해준다. 생성이아니다.
/// 프레임윈도우의 '뷰'를 생성해준다.
/// </summary>

class CMainFrame : public CMDIFrameWndEx
{
private:
	DECLARE_DYNAMIC(CMainFrame)
public:
	CGameEditorView* m_pGameEditorView;

public:
	CMainFrame() noexcept;
	virtual ~CMainFrame() final;
public:
	// 특성입니다.

public:
	 // 작업입니다.

public:
	// 재정의입니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  
	// 컨트롤 모음이 포함된 멤버입니다.
	CMFCToolBar          m_wndToolBar;

protected:
	// 생성된 메시지 맵 함수
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

};


