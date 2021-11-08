#pragma once


/// <summary>
/// �ؽ��� ������Ʈ�̴�.
/// 3D���ο�, ������������ 2D���� �̹����� ��Ÿ�� ����Ŭ�����̴�.
/// �츮�� ���� �̹����� ������ ����ִ� �������̽��̴�.
/// </summary>
/// 

class Grahpics2D;

#include "Component.h"

/// <summary>
/// ������ �̹����� '���� ��' ����ִ� Ŭ�����̴�.
/// �������� �׷��� Ư���� ���� �б⸦ ����� ����Ŭ������ �ۼ�
/// </summary>

/// <summary>
/// �ϴ� ������.. �̰� �̹����� �����ϰ� ����
/// </summary>
/// 	//#�κ��� ���߿�  Texture2D���
class  Texture : public Component
{
protected:
	std::wstring m_str;
	Grahpics2D* m_pD2DSupport;
public:
	Texture();
	//#
	Texture(Grahpics2D* _pGrahpics2D = nullptr);
	Texture(std::wstring _str, Grahpics2D* _pGrahpics2D = nullptr);
	virtual ~Texture();

public:
	void LoadTexture(std::wstring _str);


	//# ����Ŭ������ ���� �и����Ѽ� ����
	void Render();

public:
	//Component�迭�� ���� ��ȯ�Ǵ��Լ���
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update()override;
};

