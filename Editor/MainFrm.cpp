
// MainFrm.cpp: CMainFrame 클래스의 구현
//


#include "framework.h"
#include "resource.h"
#include "Editor.h"

#include "../../GameClient/GameManager.h"
#include "EWGameView.h"
#include "EDDockableBase.h"
#include "DockableView.h"


#include "MainFrm.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_FILE_NEW, &CMainFrame::OnDockTable)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
	m_pDlg = nullptr;
	m_pDockableView = nullptr;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP |
		CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);

	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	//// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndStatusBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);



	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CMDIFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE | WS_SYSMENU;

	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기



void CMainFrame::OnDockTable()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.


	//EnableDocking(CBRS_ALIGN_LEFT);
	//EnableAutoHidePanes(CBRS_ALIGN_RIGHT);
	//m_pDialog.EnableDocking(CBRS_ALIGN_ANY);
	//DockPane(&m_pDialog);

	/*
	
	
	*/
	if (nullptr == m_pDockableView && m_Num == 0)
	{
		m_pDockableView = new DockableView();
		m_pDockableView->Create(_T("Game"), this, CRect(0, 0, 1920, 1080),
			TRUE, ID_FILE_NEW,
			WS_SYSMENU | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS
			| WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI);

		m_pDockableView->m_pXGameView->m_hWnd;// = m_pDockableView->m_hWnd;//this->GetSafeHwnd();
		m_pDockableView->EnableDocking(CBRS_ALIGN_ANY);

		DockPane(m_pDockableView);

		m_pDockableView->SetAutoHideMode(false, CBRS_ALIGN_ANY);

		m_pDockableView->ShowPane(true, false, true);
		m_pDockableView->ShowWindow(SW_SHOW);
		m_Num++;
		//m_pDockableView->m_pXGameView->m_pGameManger->Start(this->GetSafeHwnd());
	}
	else if (nullptr == m_pDlg && m_Num==1)
	{
		m_pDlg = new DockableBase();

		m_pDlg->Create(_T("Inst"), this, CRect(0, 0, 500, 500), TRUE, ID_FILE_NEW,
			WS_SYSMENU | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI);
		
		m_pDlg->EnableDocking(CBRS_ALIGN_ANY);
		
		DockPane(m_pDlg);
		
		m_pDlg->SetAutoHideMode(false, CBRS_ALIGN_ANY);
		
		m_pDlg->ShowPane(true, false, true);
		m_pDlg->CreateDlg();
		m_Num++;

	}
	else if(nullptr == m_pDialog && m_Num == 2)
	{
		//BOOL bRet = m_pDialog.Create(this, MAKEINTRESOURCE(IDD_GAME_VIEW_0),
		//	WS_SYSMENU | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS
		//	| WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI,
		//	ID_WINDOW_GAME
		//);
		//
		//m_pDialog.ShowWindow(SW_SHOW);
		//m_pDialog.EnableDocking(CBRS_ALIGN_ANY);
		////DockPane(m_pDialog);
		//
		//m_pDialog.ShowPane(true, false, true);
	}

	if (nullptr != m_pDockableView)
	{
		m_pDockableView->ShowPane(true, false, true);
	}

	//해당 프레임 및 자식창의 크기를 재조절함
	RecalcLayout();

	//m_pGameView->OnInitDialog();
}

DockableView* CMainFrame::GetDockableView()
{
	if (nullptr == m_pDockableView)
	{
		return nullptr;
	}
	return m_pDockableView;
}

DockableBase* CMainFrame::GetDockableBase()
{
	if (nullptr == m_pDlg)
	{
		return nullptr;
	}
	return m_pDlg;
}
