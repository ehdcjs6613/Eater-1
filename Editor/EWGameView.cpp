// XGameView.cpp: 구현 파일
//

#include "pch.h"
#include "EWGameView.h"
#include "EditorSystem.h"
#include "Editor.h"

// XGameView

IMPLEMENT_DYNCREATE(EWGameView, CView)

EWGameView::EWGameView()
{
	
}

EWGameView::~EWGameView()
{
}

BEGIN_MESSAGE_MAP(EWGameView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// XGameView 그리기

void EWGameView::OnDraw(CDC* pDCc)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.

	

}


// XGameView 진단

#ifdef _DEBUG
void EWGameView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void EWGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// XGameView 메시지 처리기


void EWGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	m_hWnd = this->GetSafeHwnd();

	m_EditorSystem = new EditorSystem();
	
	
	m_EditorSystem->Start(m_hWnd);

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void EWGameView::OnFinalRelease()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CView::OnFinalRelease();
}


int EWGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	

	return 0;
}

void EWGameView::ViewSetting(HWND _hWnd)
{
	m_hWnd = _hWnd;
}

bool EWGameView::Update(float)
{
	return false;
}

bool EWGameView::Render()
{
	if (nullptr == m_EditorSystem) { return true; }

	m_EditorSystem->Update();
	return false;
}

bool EWGameView::Finalize()
{
	return false;
}


void EWGameView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
