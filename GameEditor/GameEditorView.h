
// GameEditorView.h: CGameEditorView 클래스의 인터페이스
//

#pragma once

class CGameEditorDoc;
/// <summary>
/// 게임엔진 편집기에서 보여질 뷰어이고, 모든것을 보여질 월드 뷰어이다.
/// 이 클래스는 보여지는 역할 담당이니까 렌더링관련 객체를 들고있는게 좋을거같다
/// </summary>

class CGameEditorView : public CView
{
private:
	DECLARE_DYNCREATE(CGameEditorView)
public: // serialization에서만 만들어집니다.
	CGameEditorView() noexcept;
	virtual ~CGameEditorView();

public:
	// 특성입니다.
	CGameEditorDoc* GetDocument() const;

public:
	// 작업입니다.

public:
	// 재정의입니다.
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

public:
	// 구현입니다.
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

protected:
	// 생성된 메시지 맵 함수
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // GameEditorView.cpp의 디버그 버전
inline CGameEditorDoc* CGameEditorView::GetDocument() const
   { return reinterpret_cast<CGameEditorDoc*>(m_pDocument); }
#endif

