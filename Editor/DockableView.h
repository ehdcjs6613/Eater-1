#pragma once


// DockableView
class EWGameView;

class DockableView : public CDockablePane
{
	DECLARE_DYNAMIC(DockableView)
	EWGameView* m_pXGameView;
public:
	HWND		m_hWnd;
public:
	DockableView();
	virtual ~DockableView();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void PostNcDestroy();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	EWGameView* GetGameView();
	DockableView* GetDockableView();
};


