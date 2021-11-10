
// GameEditor.h: GameEditor 애플리케이션의 기본 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.

class CMainFrame;
/// <summary>
/// 
/// CWINAPP 클래스는 프레임윈도우를 생성, 메세지 루프를 제공해준다.
/// 닫기, 최대화 , 최소화 윈도우의 조절역할을 해줌
/// </summary>

class CGameEditorApp : public CWinApp
{
private:
	CMainFrame* pMainFrame;
public:
	CGameEditorApp() noexcept;


// 재정의입니다.
public:
	virtual BOOL InitInstance() override;
	virtual int ExitInstance()  override;

// 구현입니다.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	//OnIdle함수는 리턴값에 따라 . 반복재생여부 결정
	//true 무한반복 , false 중지
	virtual BOOL OnIdle(LONG lCount) override;
};

extern CGameEditorApp theApp;
