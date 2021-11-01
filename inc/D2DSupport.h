#pragma once
/*
2021-07-07 CDH
	1. D2D �� ����Ͽ� �ؽ�Ʈ�� ������ UI�� ������ ����.
	
*/

#include "D2DSupportDefine.h"
#include "D2DSupportHeader.h"

class D2DSupport
{
private:
	// ���� �ڵ�
	HWND g_hWnd;
	// DX11���� ������ ����ü��.
	IDXGISwapChain* m_3D_SwapChain = nullptr;
	// �����
	IDXGISurface* m_3D_BackBuffer = nullptr;
	// Direct2D Factory
	ID2D1Factory* m_2D_Factory = nullptr;
	// 3D�� ���� ������ 2D RenderTarget
	ID2D1RenderTarget* m_2D_RenderTarget = nullptr;
	// Ŀ���� ���� �ε带 ���� ���丮
	IDWriteFactory5* m_WriteFactory = nullptr;
	// Ŀ���� ��Ʈ ����.
	IDWriteFontCollection1* m_FontCollection = nullptr;
	// �ؽ�Ʈ ����.
	IDWriteTextFormat* m_TextFormat = nullptr;

	/// ���ʿ��� Release ����..
	// �ؽ�Ʈ ���̾ƿ�
	IDWriteTextLayout* m_TextLayOut = nullptr;
	// �ؽ�Ʈ Į��
	ID2D1SolidColorBrush* m_TextColor = nullptr;

	/// �̹��� �ε�
	// �̹��� ���丮.
	IWICImagingFactory* pWICFactory = nullptr;
	// ���� ��ȯ.
	IWICFormatConverter* pConvertedSrcBmp = nullptr;
	// ���ڴ� ����.
	IWICBitmapDecoder* pDecodePtr = nullptr;
	// ���ڴ��� ������ ȹ���� ����.
	IWICBitmapFrameDecode* pFramePtr = nullptr;

	/// �ε� ȭ�� �̹���
	ID2D1Bitmap* _Loading_Img = nullptr;

/// ��Ʈ ���� ����.

	float m_Font_Size = 24.f;
	
/// �׷����� �ؽ�Ʈ�� �̸� �־�д�. ( ������Ʈ Ǯ ���� )

	Non_ThreadObjectPool<Text_Queue_Data> Text_Data_Pool;
	Non_ThreadObjectPool<Image_Queue_Data> Image_Data_Pool;

	///	�̹����� �׷����Ŀ� �ؽ��İ� �׷���
	std::queue<Image_Queue_Data*> Image_Queue;	// �̹��� ������ ť	
	std::queue<Text_Queue_Data*> Msg_Queue;		// �ؽ�Ʈ ������ ť
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
	/// �ؽ�Ʈ ��� �Լ� - �������ڸ� ���� �� �ִ�.���� ��������.
	/// </summary>
	/// <param name="_Pos"> ����� ��ǥ (���� ����) </param>
	/// <param name="_Width"> �۾� �� </param>
	/// <param name="r"> Color �� R </param>
	/// <param name="g"> Color �� G </param>
	/// <param name="b"> Color �� B </param>
	/// <param name="a"> Color �� Alpha </param>
	/// <param name="_Size"> ��Ʈ ������ </param>
	/// <param name="_Input_String"> �Է� ��Ʈ�� </param>
	/// <param name=""> �������� </param>
	void Push_DrawText(POINT _Pos, float _Width,
		float r, float g, float b, float a,
		float _Size, const wchar_t* _Input_String, ...);

	void Draw_AllText();
	void Draw_AllImage();
};

