#pragma once


// XGameView 보기
//////////////////////////////////////////////////////////////////////////
 

/// <summary>
/// '게임 뷰' 클래스 주로 '보여질' 뷰어 클래스이다.
/// 
/// </summary>
class EditorSystem;

class EWGameView : public CView
{
private:
	DECLARE_DYNCREATE(EWGameView)
	EditorSystem* m_EditorSystem;

	HWND			m_hWnd;
	CWnd			m_CWnd;

public:
	EWGameView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~EWGameView();

public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	//MFC 기본 생성 함수 & 상속 함수
	virtual void OnInitialUpdate();
	virtual void OnFinalRelease();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	//사용자 정의함수
	void ViewSetting(HWND );

	bool Update(float);
	bool Render();
	bool Finalize();

	afx_msg void OnSize(UINT nType, int cx, int cy);
};


