#pragma once
#include <string>

// �׷��� �ؽ�Ʈ�� �����.
struct Text_Queue_Data
{
	Text_Queue_Data()
	{
		Position_X = 0.f;
		Position_Y = 0.f;
		Text_Width = 0.f;
		Color_R = 0.f;
		Color_G = 0.f;
		Color_B = 0.f;
		Color_Alpha = 0.f;
		Text_Size = 0.f;
		Text_String = nullptr;
	}
	~Text_Queue_Data()
	{
		delete[] Text_String;
	}


	float Position_X;		// �ؽ�Ʈ �׸��� ������ X
	float Position_Y;		// �ؽ�Ʈ �׸��� ������ Y

	float Text_Width;		// �ؽ�Ʈ �ڽ� ũ��

	float Color_R;			// Color
	float Color_G;
	float Color_B;
	float Color_Alpha;

	float Text_Size;		// �ؽ�Ʈ ��Ʈ ũ��

	wchar_t* Text_String = nullptr;	// �ؽ�Ʈ ����
};

struct Image_Queue_Data
{
	std::wstring Img_Name = L"";	// �׸� �̹��� �̸�.

	float Position_X = 0.f;		// �̹��� �׸��� ������ X
	float Position_Y = 0.f;		// �̹��� �׸��� ������ Y

	float Scale_X = 1.f;		// �̹��� ������ ���� X
	float Scale_Y = 1.f;		// �̹��� ������ ���� Y

	float Rotate_Angle = 0.f;	// �̹��� ȸ�� ����

	float Alpha = 1.f;			// �̹��� ���İ�.


	//��������Ʈ�� �̹����� ���� �ڷ�
	int    Index = 0;				//�̹��� �ε���
	float  WidthDraw = 0.0f;			//��������Ʈ �̹����� ��ĭ�� ���� �̹���.
	float  HeightDraw = 0.0f;
};

// ������ ����.
template <class T> void SafeRelease(T** ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = nullptr;
	}
}