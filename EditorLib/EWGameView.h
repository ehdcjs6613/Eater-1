#pragma once

#include "DllExport.h"

class EditorSystem;

class VS_MFC_EXPORT EWGameView : public CView
{
private:
	DECLARE_DYNCREATE(EWGameView)
	EditorSystem* m_EditorSystem;

	HWND			m_hWnd;
	CWnd* m_CWnd;

public:
	EWGameView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~EWGameView();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	//MFC �⺻ ���� �Լ� & ��� �Լ�
	virtual void OnInitialUpdate();
	virtual void OnFinalRelease();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	//����� �����Լ�
	void ViewSetting(HWND);

	bool Update(float);
	bool Render();
	bool Finalize();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


