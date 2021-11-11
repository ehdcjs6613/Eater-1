
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "Editor.h"

#include "SaveData.h"
#include "CGameView.h"
#include "GameView.h"
#include "CDockalbePannel.h"

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
	m_pCDockalbePannel[0] = nullptr;
	m_pCDockalbePannel[1] = nullptr;
	m_pGameView = nullptr;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP |
		CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC ) ||
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
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);

	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	//// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndStatusBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);

	m_pCGameView = new CGameView();
	m_pCGameView->Create(_T("cs"), _T("cs"), WS_CHILD | WS_VISIBLE, CRect(200, +500, 200, 100), this, -1);
	//m_pCGameView->ShowWindow(SW_SHOW);
	//m_pCGameView->UpdateWindow();


	//m_pGameView = new GameView(this);
	//
	//m_pGameView->Create(IDD_GAME_VIEW_0, this);
	//
	//m_pGameView->ShowWindow(SW_SHOW);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
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



	if (m_pCDockalbePannel[0] == nullptr && m_pCDockalbePannel[1] == nullptr)
	{
		m_pCDockalbePannel[0] = new CDockalbePannel();

		m_pCDockalbePannel[0]->Create(_T(""), this, CRect(0, 0, 300, 200), TRUE, ID_FILE_NEW,
			WS_SYSMENU |	WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI);

		m_pCDockalbePannel[0]->EnableDocking(CBRS_ALIGN_ANY);

		DockPane(m_pCDockalbePannel[0]);

		m_pCDockalbePannel[0]->SetAutoHideMode(false, CBRS_ALIGN_ANY);

		m_pCDockalbePannel[0]->ShowPane(true, false, true);
	}
	else if (m_pCDockalbePannel[0] != nullptr && m_pCDockalbePannel[1] == nullptr)
	{
		m_pCDockalbePannel[1] = new CDockalbePannel();

		m_pCDockalbePannel[1]->Create(_T(""), this, CRect(0, 0, 300, 200), TRUE, ID_FILE_NEW,
			WS_SYSMENU | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI);

		m_pCDockalbePannel[1]->EnableDocking(CBRS_ALIGN_ANY);

		DockPane(m_pCDockalbePannel[1]);

		m_pCDockalbePannel[1]->SetAutoHideMode(false, CBRS_ALIGN_ANY);

		m_pCDockalbePannel[1]->ShowPane(true, false, true);
	}
	
	
	
	//m_pGameView->OnInitDialog();
}
