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
ON_WM_MOVE()
ON_WM_ENTERIDLE()

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

	m_pCStatic[0] = new CStatic();
	m_pCStatic[1] = new CStatic();
	m_pCStatic[2] = new CStatic();
	
	m_pCStatic[0]->Create(_T("x"), WS_CHILD | WS_VISIBLE | SS_LEFT,
		CRect(10, 10, 60, 30), this);

	m_pCStatic[1]->Create(_T("y"), WS_CHILD | WS_VISIBLE | SS_LEFT,
		CRect(120, 10, 170, 30), this);

	m_pCStatic[2]->Create(_T("z"), WS_CHILD | WS_VISIBLE | SS_LEFT,
		CRect(310, 10, 360, 30), this);


	m_pCEdit[0] = new CEdit();
	m_pCEdit[0]->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
		CRect(000, 100, 100, 120), this, XNUM_0);

	m_pCEdit[1] = new CEdit();
	m_pCEdit[1]->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
		CRect(110, 100, 200, 120), this, XNUM_1);

	m_pCEdit[2] = new CEdit();
	m_pCEdit[2]->Create(ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER,
		CRect(210, 100, 300, 120), this, XNUM_2);

	m_pCEdit[0]->ShowWindow(SW_SHOW);
	m_pCEdit[0]->UpdateWindow();
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


void DockableBase::OnMove(int x, int y)
{
	m_pCEdit[0]->ShowWindow(SW_SHOW);
	m_pCEdit[0]->UpdateWindow();

	CDockablePane::OnMove(x, y);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void DockableBase::OnEnterIdle(UINT nWhy, CWnd* pWho)
{
	CDockablePane::OnEnterIdle(nWhy, pWho);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void DockableBase::Update()
{
	CString x(""), y(""), z("");
	CString sx(""),sy(""),sz("");

	if(m_pCEdit !=nullptr)
		m_pCEdit[0]->GetWindowTextW(x);
	if (m_pCEdit != nullptr)
		m_pCEdit[1]->GetWindowTextW(y);
	if (m_pCEdit != nullptr)
		m_pCEdit[2]->GetWindowTextW(z);
	
	float xf = _ttof(x);
	float yf = _ttof(y);
	float zf = _ttof(z);
}

DockableBase* DockableBase::GetDockableBase()
{
	if (this == nullptr)
	{
		return nullptr;
	}
	return this;
}
