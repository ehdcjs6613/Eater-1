#include "D2DSupport.h"

D2DSupport::D2DSupport(HWND _hWnd, IDXGISwapChain* _3D_SwapChain, float _Font_Size /*= 24.f*/)
{
	g_hWnd = _hWnd;
	// ����� ��������.
	_3D_SwapChain->GetBuffer(0, IID_PPV_ARGS(&m_3D_BackBuffer));

	// ȭ���� dpi�� ������.
	float dpi;
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_2D_Factory);

	// com �ʱ�ȭ
	HRESULT hr = CoInitialize(0);

	// Windows Imaging Component Factory�� �����Ѵ�. (WIC Factory ����)
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pWICFactory));
	hr = CoCreateInstance(CLSID_WICBmpDecoder, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pDecodePtr));

	dpi = GetDpiForWindow(_hWnd);

	// ������ RenderTarget �� ���� ���� ����.
	D2D1_RENDER_TARGET_PROPERTIES props =
		D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
			dpi, dpi
		);

	// DXGI �� Ȱ���� 3D ����ۿ��� 2D ����Ÿ���� ����.
	m_2D_Factory->CreateDxgiSurfaceRenderTarget(m_3D_BackBuffer, &props, &m_2D_RenderTarget);

	// pWriteFactory5 ����
	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(m_WriteFactory),
		reinterpret_cast<IUnknown**>(&m_WriteFactory)
	);

	// FontFileReference�� ��� ���� �ʿ��� ��ü. 
	IDWriteFontFile* pFontFileReference;
	// FontFile�� �߰��Ͽ� FontSet�� ����� Builder ��ü.
	IDWriteFontSetBuilder1* pFontSetBuilder1;
	// FontCollection�� �ٲ���� ��.
	IDWriteFontSet* pCustomFontSet;

	m_WriteFactory->CreateFontFileReference(L"../Font/Font1.ttf", nullptr, &pFontFileReference);

	m_WriteFactory->CreateFontSetBuilder(&pFontSetBuilder1);

	pFontSetBuilder1->AddFontFile(pFontFileReference);

	pFontSetBuilder1->CreateFontSet(&pCustomFontSet);

	m_WriteFactory->CreateFontCollectionFromFontSet(pCustomFontSet, &m_FontCollection);

	pFontFileReference->Release();
	pFontSetBuilder1->Release();
	pCustomFontSet->Release();

	IDWriteFontFamily* fontFamily;
	IDWriteLocalizedStrings* localizedFontName;
	TCHAR c_styleFontName[65];

	m_FontCollection->GetFontFamily(0, &fontFamily);
	fontFamily->GetFamilyNames(&localizedFontName);
	localizedFontName->GetString(0, c_styleFontName, 65);

	fontFamily->Release();
	localizedFontName->Release();

	// pTextFormat 
	//pWriteFactory5->CreateTextLayout()
	m_WriteFactory->CreateTextFormat(
		c_styleFontName,
		m_FontCollection,
		DWRITE_FONT_WEIGHT_SEMI_BOLD,	// ��Ÿ�� ���� 1
		DWRITE_FONT_STYLE_NORMAL,		// ��Ÿ�� ���� 2
		DWRITE_FONT_STRETCH_NORMAL,		// ��Ÿ�� ���� 3
		m_Font_Size,
		L"ko-kr", //locale
		&m_TextFormat
	);

	// �»�� �������� �ؽ�Ʈ ����.
	m_TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	m_TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

}

D2DSupport::~D2DSupport()
{
	m_TextLayOut->Release();
	m_TextColor->Release();
}

void D2DSupport::LoadLoadingImage(ATL::CString _Image_Path)
{
	// �̹����� �̹� �ε� �Ǿ������� �ι� �ε����� �ʴ´�.
	if (_Loading_Img != nullptr)
	{
		return;
	}

	// ������
	HRESULT hr;

	// ���ڴ� ����
	hr = pWICFactory->CreateDecoderFromFilename(_Image_Path, nullptr,
		GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecodePtr);

	// ���ڴ����� ������ ȹ��
	pDecodePtr->GetFrame(0, &pFramePtr);

	// ������ ������� ���� ������ ����

	pWICFactory->CreateFormatConverter(&pConvertedSrcBmp);

	// �ʱ�ȭ.
	pConvertedSrcBmp->Initialize(pFramePtr, GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, nullptr, 0.0f, WICBitmapPaletteTypeCustom);

	m_2D_RenderTarget->CreateBitmapFromWicBitmap(pConvertedSrcBmp, nullptr, &_Loading_Img);

	SafeRelease(&pConvertedSrcBmp);
	SafeRelease(&pDecodePtr);
	SafeRelease(&pFramePtr);
}

void D2DSupport::DrawLoadingImage()
{
	m_2D_RenderTarget->BeginDraw();

	D2D1_SIZE_F Bitmap_Size = _Loading_Img->GetSize();
	D2D1_RECT_F Draw_Area = { 0,0, Bitmap_Size.width , Bitmap_Size.height};

	m_2D_RenderTarget->DrawBitmap(_Loading_Img, Draw_Area, 1.0f);

	m_2D_RenderTarget->EndDraw();
}

void D2DSupport::LoadBitMap(ATL::CString _Image_Name, ATL::CString _File_Path)
{
	// �̹����� �̹� �ε� �Ǿ������� �ι� �ε����� �ʴ´�.
	if (Image_Resource.find(_Image_Name) != Image_Resource.end())
	{
		return;
	}

	ID2D1Bitmap* _Img_Data = nullptr;
	// ������
	HRESULT hr;

	// ���ڴ� ����
	hr = pWICFactory->CreateDecoderFromFilename(_File_Path, nullptr,
		GENERIC_READ, WICDecodeMetadataCacheOnDemand, &pDecodePtr);

	// ���ڴ����� ������ ȹ��
	pDecodePtr->GetFrame(0, &pFramePtr);

	// ������ ������� ���� ������ ����

	pWICFactory->CreateFormatConverter(&pConvertedSrcBmp);

	// �ʱ�ȭ.
	pConvertedSrcBmp->Initialize(pFramePtr, GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone, nullptr, 0.0f, WICBitmapPaletteTypeCustom);

	m_2D_RenderTarget->CreateBitmapFromWicBitmap(pConvertedSrcBmp, nullptr, &_Img_Data);

	// �̹��� �����͸� �����ص�. ���߿� �̸����� ������!
	Image_Resource.insert(std::pair(_Image_Name, _Img_Data));

	SafeRelease(&pConvertedSrcBmp);
	SafeRelease(&pDecodePtr);
	SafeRelease(&pFramePtr);
}

void D2DSupport::thDrawBitmap(ATL::CString _Image_Name, POINTF _Position, float _Alpha, float _Scale_X /*= 1.f*/, float _Scale_Y /*= 1.f*/, float _Angle /*= 0.f*/)
{
	auto _map_data = Image_Resource.find(_Image_Name);
	ID2D1Bitmap* _Img_Data = _map_data->second;

	D2D1_SIZE_F Bitmap_Size = _Img_Data->GetSize();
	D2D1_RECT_F Draw_Area = { _Position.x, _Position.y,
	 _Position.x + Bitmap_Size.width * _Scale_X, _Position.y + Bitmap_Size.height * _Scale_Y };

	m_2D_RenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(_Angle, D2D1::Point2F(_Position.x, _Position.y)));

	m_2D_RenderTarget->DrawBitmap(_Img_Data, Draw_Area, _Alpha);

	m_2D_RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void D2DSupport::Push_DrawImage(ATL::CString _Image_Name, POINTF _Pos, POINTF _Scale, float _Angle, float _Alpha,
	POINTF UI_Pos, POINTF UI_Scale, float UI_Angle, float UI_Alpha)
{
	Image_Queue_Data* Queue_Data = Image_Data_Pool.GetObject();

	Queue_Data->Img_Name = _Image_Name;
	Queue_Data->Position_X = UI_Pos.x + _Pos.x;
	Queue_Data->Position_Y = UI_Pos.y + _Pos.y;
	Queue_Data->Scale_X = UI_Scale.x * _Scale.x;
	Queue_Data->Scale_Y = UI_Scale.y * _Scale.y;
	Queue_Data->Rotate_Angle = UI_Angle + _Angle;
	Queue_Data->Alpha = UI_Alpha * _Alpha;

	Image_Queue.push(Queue_Data);
}

void D2DSupport::Push_DrawText(POINT _Pos, float _Width,
	float r , float g, float b, float a,
	float _Size, const wchar_t* _Input_String, ...)
{
	// ���� �غ� �ִ� ���ڼ� 128
	wchar_t* pStr = new wchar_t[128];

	va_list args;
	// ���������� ��ġ�� ó������ �����ϱ� ����.
	va_start(args, _Input_String);

	// �츮�� �غ��� ���ۿ� �ϼ��� ����� ����.
	vswprintf(pStr, 128, _Input_String, args);
	va_end(args);

	Text_Queue_Data* Queue_Data = Text_Data_Pool.GetObject();

	Queue_Data->Position_X = _Pos.x;
	Queue_Data->Position_Y = _Pos.y;
	Queue_Data->Text_Width = _Width;

	Queue_Data->Color_R = r;
	Queue_Data->Color_G = g;
	Queue_Data->Color_B = b;
	Queue_Data->Color_Alpha = a;

	Queue_Data->Text_Size = _Size;
	Queue_Data->Text_String = pStr;

	Msg_Queue.push(Queue_Data);
}

void D2DSupport::Draw_AllText()
{
	m_2D_RenderTarget->BeginDraw();

	while (!Msg_Queue.empty())
	{
		Text_Queue_Data* Queue_Data = Msg_Queue.front();
		Msg_Queue.pop();

		// ��Ʈ ���� ����.
		m_2D_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(Queue_Data->Color_R, Queue_Data->Color_G, Queue_Data->Color_B, Queue_Data->Color_Alpha), &m_TextColor);

		m_WriteFactory->CreateTextLayout(
			Queue_Data->Text_String,
			wcslen(Queue_Data->Text_String),
			m_TextFormat,
			Queue_Data->Text_Width,
			std::numeric_limits<float>::infinity(),
			&m_TextLayOut);

		DWRITE_TEXT_RANGE textRange;
		textRange.startPosition = 0;
		textRange.length = wcslen(Queue_Data->Text_String);

		m_TextLayOut->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		m_TextLayOut->SetFontSize(Queue_Data->Text_Size, textRange);

		// ��Ʈ�� �����ϴ� ���� ��� �ʿ�
		m_2D_RenderTarget->DrawTextLayout(D2D1::Point2F(Queue_Data->Position_X, Queue_Data->Position_Y),
			m_TextLayOut, m_TextColor);

		m_TextLayOut->Release();
		m_TextColor->Release();

		Text_Data_Pool.ResetObject(Queue_Data);
	}

	//m_2D_RenderTarget->EndDraw();
}

void D2DSupport::Draw_AllImage()
{
	m_2D_RenderTarget->BeginDraw();

	while (!Image_Queue.empty())
	{
		Image_Queue_Data* Queue_Data = Image_Queue.front();
		Image_Queue.pop();

		thDrawBitmap(Queue_Data->Img_Name, POINTF{ Queue_Data->Position_X, Queue_Data->Position_Y },
			Queue_Data->Alpha, Queue_Data->Scale_X, Queue_Data->Scale_Y, Queue_Data->Rotate_Angle);

		Image_Data_Pool.ResetObject(Queue_Data);
	}

	m_2D_RenderTarget->EndDraw();

}
