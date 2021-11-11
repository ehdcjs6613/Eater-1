// CGameView.cpp: 구현 파일
//

#include "pch.h"
#include "Editor.h"
#include "CGameView.h"


// CGameView

IMPLEMENT_DYNCREATE(CGameView, CTabView)

CGameView::CGameView()
{

}

CGameView::~CGameView()
{
}

BEGIN_MESSAGE_MAP(CGameView, CTabView)
END_MESSAGE_MAP()


// CGameView 진단

#ifdef _DEBUG
void CGameView::AssertValid() const
{
	CTabView::AssertValid();
}

#ifndef _WIN32_WCE
void CGameView::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}
void CGameView::OnDraw(CDC* pDCc)
{
	CRect rect;
	GetClientRect(&rect);

	int a = GetScrollPos(1);

	rect.bottom += a;
	rect.top += a;

	CDC* pDC = new CDC;
	CBitmap* pOldBitmap, bitmap;

	pDC->CreateCompatibleDC(pDCc);
	bitmap.CreateCompatibleBitmap(pDCc, rect.right, rect.bottom);
	pOldBitmap = pDC->SelectObject(&bitmap);

	pDC->Rectangle(0, 0, rect.right, rect.bottom);

	// GDI
	pDC->TextOut(0, 0, CString("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
		"[GDI]"
		"------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"));

	// CPen 예제
	{
		int		aiStyle[] = { PS_SOLID,		PS_DASH,	   PS_DOT,		 PS_DASHDOT,	   PS_DASHDOTDOT,		PS_NULL };
		CString	astrSytle[] = { _T("PS_SOLID"), _T("PS_DASH"), _T("PS_DOT"), _T("PS_DASHDOT"), _T("PS_DASHDOTDOT"), _T("PS_NULL") };

		int iCount = sizeof(aiStyle) / sizeof(aiStyle[0]);

		for (int i = 0; i < iCount; ++i)
		{
			// 어떤 타입인지 출력
			pDC->TextOut(0, 25 + (i * 25), astrSytle[i], astrSytle[i].GetLength());

			// 펜 생성
			CPen pen, * pOldPen;
			pen.CreatePen(aiStyle[i], 1, RGB(0, 0, 0));							// 타입, 1px 크기, 검은색

			pOldPen = pDC->SelectObject(&pen);									// 지정
			pDC->MoveTo(CPoint(150, 25 + (i * 25)));								// 라인 시작점 지정( CPoint 사용 )
			pDC->LineTo(CPoint(300, 25 + (i * 25 + 25)));							// 라인 종료점 지정 및 출력( CPoint 사용 )
			pDC->Rectangle(CRect(350, 25 + (i * 25), 500, 25 + (i * 25 + 25)));	// 직사각형 출력( CRect 사용 )
			pDC->Ellipse(CRect(550, 25 + (i * 25), 700, 25 + (i * 25 + 25)));	// 타원 출력( CRect 사용 )
			pDC->SelectObject(pOldPen);											// 복원

			//pen.DeleteObject();													// GDI 객체들은 소멸자에서 DeleteObject() 를 호출 해주므로 호출하지 않아도 무방합니다.
																					// 때문에 이어지는 예제에서는 항상 DeleteObject() 를 따로 호출하지 않겠습니다.
		}
	}
}
#endif
#endif //_DEBUG


// CGameView 메시지 처리기
