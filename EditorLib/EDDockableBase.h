#pragma once

#define XNUM_0 2000
#define XNUM_1 2001
#define XNUM_2 2002

// CDockalbePannel
#include "DllExport.h"

class GameDlg;
class SaveData;

class HsGraphic;

class VS_MFC_EXPORT DockableBase : public CDockablePane
{
private:
	DECLARE_DYNAMIC(DockableBase)
	CPaneDialog	   m_pDialog;
	CEdit*		   m_pCEdit[3];
	CStatic*	   m_pCStatic[3];
	//GameDlg*	   m_pDialog;
public:
	DockableBase();
	virtual ~DockableBase();

	
	
protected:

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	virtual void PostNcDestroy();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	void CreateDlg();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnEnterIdle(UINT nWhy, CWnd* pWho);
public:
	void Update();
	DockableBase* GetDockableBase();
	
};


