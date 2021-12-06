// XGameView.cpp: ���� ����
//
#include "LibDefine.h"
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
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// XGameView �׸���

void EWGameView::OnDraw(CDC* pDCc)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.



}


// XGameView ����

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


// XGameView �޽��� ó����


void EWGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	m_hWnd = this->GetSafeHwnd();
	m_CWnd = CWnd::FromHandle(m_hWnd);

	m_EditorSystem = new EditorSystem();


	m_EditorSystem->Start(m_hWnd);

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}


void EWGameView::OnFinalRelease()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CView::OnFinalRelease();
}


int EWGameView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.


	return 0;
}

void EWGameView::ViewSetting(HWND _hWnd)
{
	m_hWnd = _hWnd;
	m_hWnd = this->GetSafeHwnd();
	m_CWnd = CWnd::FromHandle(m_hWnd);

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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


int EWGameView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}
