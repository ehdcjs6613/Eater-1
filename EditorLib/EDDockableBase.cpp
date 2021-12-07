// CDockalbePannel.cpp: 구현 파일
//
#include "../Editor/resource.h"
#include "LibDefine.h"
#include "EDDockableBase.h"


// CDockalbePannel

IMPLEMENT_DYNAMIC(DockableBase, CDockablePane)

DockableBase::DockableBase() 
{
}

DockableBase::~DockableBase()
{
}


BEGIN_MESSAGE_MAP(DockableBase, CDockablePane)
ON_WM_SIZE()
ON_WM_CREATE()
ON_WM_DESTROY()
ON_WM_CLOSE()
END_MESSAGE_MAP()



// CDockalbePannel 메시지 처리기



void DockableBase::OnSize(UINT nType, int cx, int cy)
{

	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


int DockableBase::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;


	
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	


	return 0;
}


void DockableBase::OnDestroy()
{
	
	CDockablePane::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void DockableBase::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	CDockablePane::OnClose();
}


void DockableBase::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	delete this;
}


BOOL DockableBase::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDockablePane::PreCreateWindow(cs);
}

void DockableBase::CreateDlg()
{
	BOOL bRet = m_pDialog.Create(this, MAKEINTRESOURCE(IDD_GAME_VIEW_0),
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_FLOAT_MULTI,
		ID_WINDOW_GAME
	);

	m_pDialog.ShowWindow(SW_SHOW);
	m_pDialog.EnableDocking(CBRS_ALIGN_ANY);


	m_pDialog.SetAutoHideMode(false, CBRS_ALIGN_ANY);

	m_pDialog.ShowPane(true, false, true);
}
