#pragma once


// XGameView 보기

 
class GameManager;

/// <summary>
/// '게임 뷰' 클래스 주로 '보여질' 뷰어 클래스이다.
/// </summary>

class EWGameView : public CView
{
private:
	DECLARE_DYNCREATE(EWGameView)

	

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
	virtual void OnInitialUpdate();
	virtual void OnFinalRelease();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


