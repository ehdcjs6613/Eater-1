#pragma once


// CGameView 보기

class CGameView : public CTabView
{
	DECLARE_DYNCREATE(CGameView)
public:
	CGameView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CGameView();
protected:

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	virtual void OnDraw(CDC* pDC);

protected:
	DECLARE_MESSAGE_MAP()
};


