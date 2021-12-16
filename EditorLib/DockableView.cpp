#include "LibDefine.h"

#include "EWGameView.h" 
#include "DockableView.h"


// DockableView

IMPLEMENT_DYNAMIC(DockableView, CDockablePane)

DockableView::DockableView() : m_pXGameView(nullptr), m_hWnd{}
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
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()



// DockableView �޽��� ó����






void DockableView::OnDestroy()
{
	CDockablePane::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void DockableView::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDockablePane::OnClose();
}


void DockableView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


int DockableView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_hWnd = this->GetSafeHwnd();

	m_pXGameView->Create(nullptr, L"����",
		WS_SYSMENU | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_FLOAT_MULTI,
		CRect(0, 0, 1920, 1080), this, 50001);
	m_pXGameView->OnInitialUpdate();
	m_pXGameView->ShowWindow(SW_SHOW);
	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	return 0;
}


void DockableView::PostNcDestroy()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CDockablePane::PostNcDestroy();
}


BOOL DockableView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

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


void DockableView::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// ���� ��ŷ ���� ���� �ּ��ִ� ũ�⸦ �����Ѵ�.

	//min
	lpMMI->ptMinTrackSize.x = 800;     // �ּҰ�
	lpMMI->ptMinTrackSize.y = 600;
	//max
	lpMMI->ptMaxTrackSize.x = 1920;   // �ִ밪
	lpMMI->ptMaxTrackSize.y = 1080;


	CDockablePane::OnGetMinMaxInfo(lpMMI);
}
