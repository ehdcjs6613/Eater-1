// CDockalbePannel.cpp: 구현 파일
//

#include "pch.h"
#include "Editor.h"
#include "MainFrm.h"
#include "CGameView.h"
#include "SaveData.h"
#include "CDockalbePannel.h"


SaveData* g_pTestSaveData;
// CDockalbePannel

IMPLEMENT_DYNAMIC(CDockalbePannel, CDockablePane)

CDockalbePannel::CDockalbePannel() : m_DialogWidth(0), m_DialogHeight(0)
{
	g_pTestSaveData = new SaveData();
}

CDockalbePannel::~CDockalbePannel()
{
}


BEGIN_MESSAGE_MAP(CDockalbePannel, CDockablePane)
//	ON_WM_PAINT()
ON_WM_TIMER()
ON_WM_SIZE()
ON_WM_CREATE()
ON_WM_DESTROY()
ON_WM_CLOSE()
ON_WM_MOVE()
ON_WM_MOVING()
ON_WM_PAINT()
ON_WM_LBUTTONUP()
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CDockalbePannel 메시지 처리기


int g_SaveXPos;
int g_SaveYPos;

//void CDockalbePannel::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
//					   // 그리기 메시지에 대해서는 CDockablePane::OnPaint()을(를) 호출하지 마십시오.
//}

int g_PosX =0;
void CDockalbePannel::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	
	g_PosX++;
	CDockablePane::OnTimer(nIDEvent);
}


void CDockalbePannel::OnSize(UINT nType, int cx, int cy)
{
	if (cx == 0 || cy == 0)
	{
		return;
	}
	m_RectPos.right = cx;
	m_RectPos.bottom = cy;

	m_pDialog.MoveWindow(m_RectPos.left, m_RectPos.top, m_RectPos.right, m_RectPos.bottom);

	CDockablePane::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


int CDockalbePannel::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	

	BOOL bRet = m_pDialog.Create(IDD_GAME_VIEW_0,this);
	assert(bRet);

	m_pDialog.ShowWindow(SW_SHOW);


	//HICON hFileViewIcon = (HICON)::LoadImage(
	//	::AfxGetResourceHandle(),
	//	MAKEINTRESOURCE(theApp.m_hIcon),
	//	IMAGE_ICON,
	//	::GetSystemMetrics(SM_CXSMICON),
	//	::GetSystemMetrics(SM_CYSMICON),
	//	0);

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	


	return 0;
}


void CDockalbePannel::OnDestroy()
{
	
	CDockablePane::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CDockalbePannel::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	CDockablePane::OnClose();
}


void CDockalbePannel::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	delete this;
}


BOOL CDockalbePannel::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDockablePane::PreCreateWindow(cs);
}


void CDockalbePannel::OnMove(int x, int y)
{
	if (x == 0)
	{
		return;
	}

	if (x != 0 || y != 0)
	{
	
		m_RectPos.left = x;
		m_RectPos.top = y;

		m_pDialog.SetWindowPos(this, m_RectPos.left, m_RectPos.top, m_RectPos.right, m_RectPos.bottom, 0);

		CDockablePane::OnMove(m_RectPos.left, m_RectPos.bottom);
	}
	else
	{
		if (0 != m_RectPos.left || 0 != m_RectPos.top)
		{
			m_pDialog.SetWindowPos(this, 
				m_RectPos.left,
				m_RectPos.top,
				m_RectPos.right, 
				m_RectPos.bottom, TRUE);
		}
	
	}


	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CDockalbePannel::OnMoving(UINT fwSide, LPRECT pRect)
{
	if (pRect->right != 0 || pRect->bottom != 0)
	{
		m_pDialog.SetWindowPos(this,m_RectPos.left, m_RectPos.top , m_RectPos.right, m_RectPos.bottom,0);
		
		CDockablePane::OnMoving(fwSide, m_RectPos);
	}



	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CDockalbePannel::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDockablePane::OnPaint()을(를) 호출하지 마십시오.

	CRect rectDlg;
	m_pDialog.GetWindowRect(rectDlg);
	ScreenToClient(rectDlg);
	rectDlg.InflateRect(1, 1);
	dc.Draw3dRect(rectDlg, ::GetSysColor(COLOR_3DDKSHADOW), ::GetSysColor(COLOR_3DDKSHADOW));

}

///파라미터 nFlags는 Down(1) Up(0)이다.

void CDockalbePannel::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_sMousePoint.x = point.x;
	m_sMousePoint.y = point.y;

	m_bMouse = nFlags;//false


	CDockablePane::OnLButtonUp(nFlags, point);
}


void CDockalbePannel::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_sMousePoint.x = point.x;
	m_sMousePoint.y = point.y;
	
	m_bMouse = nFlags;//true


	CDockablePane::OnLButtonDown(nFlags, point);
}
