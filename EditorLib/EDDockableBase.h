#pragma once

#define XNUM_0 2000
#define XNUM_1 2001
#define XNUM_2 2002

#define XNUM_3 2000
#define XNUM_4 2001
#define XNUM_5 2002

// CDockalbePannel
#include <afxdockablepane.h>
#include "DllExport.h"

class GameDlg;
class SaveData;
class CMainFrame;
class EWGameView;
class DockableView;

class HsGraphic;

class DockableBase : public CDockablePane
{
private:
	DECLARE_DYNAMIC(DockableBase)
	//CPaneDialog	   m_pDialog;
	CEdit*		   m_pCEdit[3];
	CEdit*		   m_pCEditScale[3];
	CStatic*	   m_pCStatic[3];
	//GameDlg*	   m_pDialog;
public:
	VS_MFC_EXPORT DockableBase();
	VS_MFC_EXPORT virtual ~DockableBase();

	CString x, y, z;
	CString sx, sy, sz;
	
	float xf;
	float yf;
	float zf;

	float xs;
	float ys;
	float zs;
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
	VS_MFC_EXPORT void CreateDlg();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnEnterIdle(UINT nWhy, CWnd* pWho);
public:
	VS_MFC_EXPORT   void Update();
	VS_MFC_EXPORT  DockableBase* GetDockableBase();
	
};


