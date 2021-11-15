#pragma once


// CDockalbePannel

class GameDlg;
class SaveData;

class HsGraphic;

class DockableBase : public CDockablePane
{
private:
	DECLARE_DYNAMIC(DockableBase)

	CPaneDialog	   m_pDialog;
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
};


