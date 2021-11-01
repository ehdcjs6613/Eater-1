#pragma once
/*
2021-07-07 CDH
	1. D2D 를 사용하여 텍스트나 간단한 UI를 구현할 에정.
	
*/

#include "D2DSupportDefine.h"
#include "D2DSupportHeader.h"

class D2DSupport
{
private:
	// 메인 핸들
	HWND g_hWnd;
	// DX11에서 생성된 스왑체인.
	IDXGISwapChain* m_3D_SwapChain = nullptr;
	// 백버퍼
	IDXGISurface* m_3D_BackBuffer = nullptr;
	// Direct2D Factory
	ID2D1Factory* m_2D_Factory = nullptr;
	// 3D로 부터 생성된 2D RenderTarget
	ID2D1RenderTarget* m_2D_RenderTarget = nullptr;
	// 커스텀 폰드 로드를 위한 팩토리
	IDWriteFactory5* m_WriteFactory = nullptr;
	// 커스텀 폰트 정보.
	IDWriteFontCollection1* m_FontCollection = nullptr;
	// 텍스트 포멧.
	IDWriteTextFormat* m_TextFormat = nullptr;

	/// 불필요한 Release 방지..
	// 텍스트 레이아웃
	IDWriteTextLayout* m_TextLayOut = nullptr;
	// 텍스트 칼러
	ID2D1SolidColorBrush* m_TextColor = nullptr;

	/// 이미지 로딩
	// 이미지 팩토리.
	IWICImagingFactory* pWICFactory = nullptr;
	// 포맷 변환.
	IWICFormatConverter* pConvertedSrcBmp = nullptr;
	// 디코더 생성.
	IWICBitmapDecoder* pDecodePtr = nullptr;
	// 디코더의 프레임 획득을 위함.
	IWICBitmapFrameDecode* pFramePtr = nullptr;

	/// 로딩 화면 이미지
	ID2D1Bitmap* _Loading_Img = nullptr;

/// 폰트 셋팅 관련.

	float m_Font_Size = 24.f;
	
/// 그려야할 텍스트를 미리 넣어둔다. ( 오브젝트 풀 생성 )

	Non_ThreadObjectPool<Text_Queue_Data> Text_Data_Pool;
	Non_ThreadObjectPool<Image_Queue_Data> Image_Data_Pool;

	///	이미지가 그려진후에 텍스쳐가 그려짐
	std::queue<Image_Queue_Data*> Image_Queue;	// 이미지 데이터 큐	
	std::queue<Text_Queue_Data*> Msg_Queue;		// 텍스트 데이터 큐
	std::map<ATL::CString, ID2D1Bitmap*> Image_Resource;

public:
	D2DSupport(HWND g_hWnd, IDXGISwapChain* _3D_SwapChain, float _Font_Size = 24.f);
	~D2DSupport();

	void LoadLoadingImage(ATL::CString _Image_Path);
	void DrawLoadingImage();

	void LoadBitMap(ATL::CString _Image_Name ,ATL::CString _File_Path);

	void thDrawBitmap(ATL::CString _Image_Name, POINTF _Position, float _Alpha, float _Scale_X = 1.f, float _Scale_Y = 1.f, float _Angle = 0.f);

	void Push_DrawImage(ATL::CString _Image_Name, POINTF _Pos, POINTF _Scale, float _Angle, float _Alpha,
		POINTF UI_Pos, POINTF UI_Scale, float UI_Angle, float UI_Alpha);

	/// <summary>
	/// 텍스트 출력 함수 - 가변인자를 받을 수 있다.색깔도 지정가능.
	/// </summary>
	/// <param name="_Pos"> 출력할 좌표 (시작 지점) </param>
	/// <param name="_Width"> 글씨 폭 </param>
	/// <param name="r"> Color 의 R </param>
	/// <param name="g"> Color 의 G </param>
	/// <param name="b"> Color 의 B </param>
	/// <param name="a"> Color 의 Alpha </param>
	/// <param name="_Size"> 폰트 사이즈 </param>
	/// <param name="_Input_String"> 입력 스트링 </param>
	/// <param name=""> 가변인자 </param>
	void Push_DrawText(POINT _Pos, float _Width,
		float r, float g, float b, float a,
		float _Size, const wchar_t* _Input_String, ...);

	void Draw_AllText();
	void Draw_AllImage();
};

