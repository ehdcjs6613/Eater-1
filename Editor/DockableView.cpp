// DockableView.cpp: 구현 파일
//

#include "pch.h"
#include "Editor.h"
#include "EWGameView.h" 
#include "DockableView.h"


// DockableView

IMPLEMENT_DYNAMIC(DockableView, CDockablePane)

DockableView::DockableView() : m_pXGameView(nullptr) , m_hWnd{}
{
	m_pXGameView = new EWGameView();
}

DockableView::~DockableView()
{
}


BEGIN_MESSAGE_MAP(DockableView, CDockablePane)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// DockableView 메시지 처리기






void DockableView::OnDestroy()
{
	CDockablePane::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void DockableView::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDockablePane::OnClose();
}


void DockableView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


int DockableView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_hWnd = this->GetSafeHwnd();
	
	m_pXGameView->Create(nullptr, L"ㅋㅋ",
		WS_SYSMENU |WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN  | CBRS_FLOAT_MULTI,
		CRect(0, 0, 1920, 1080), this, 50001);
	m_pXGameView->OnInitialUpdate();
	m_pXGameView->ShowWindow(SW_SHOW);
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


void DockableView::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDockablePane::PostNcDestroy();
}


BOOL DockableView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDockablePane::PreCreateWindow(cs);
}

EWGameView* DockableView::GetGameView()
{
	if (nullptr == m_pXGameView)
	{
		return nullptr;
	}
	return m_pXGameView;
}

DockableView* DockableView::GetDockableView()
{
	return this;
}
