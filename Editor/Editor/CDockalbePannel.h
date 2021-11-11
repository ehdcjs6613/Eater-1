#pragma once


// CDockalbePannel

class CGameView;

class CDockalbePannel : public CDockablePane
{
	DECLARE_DYNAMIC(CDockalbePannel)

	CGameView* m_pCGameView;
	CWnd	   m_pCWND;
	CDialog	   m_pDialog;

public:
	CDockalbePannel();
	virtual ~CDockalbePannel();

	

protected:
	CRect	m_RectPos;

	int		m_DialogPosX;
	int		m_DialogPosY;

	int		m_DialogWidth;
	int		m_DialogHeight;

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnPaint();
};


