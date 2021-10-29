#pragma once


/// <summary>
/// �ؽ��� ������Ʈ�̴�.
/// 3D���ο�, ������������ 2D���� �̹����� ��Ÿ�� ����Ŭ�����̴�.
/// �츮�� ���� �̹����� ������ ����ִ� �������̽��̴�.
/// </summary>
/// 

class D2DSupport;

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
	D2DSupport* m_pD2DSupport;
public:
	 Texture();
	 //#
	 Texture(D2DSupport* _pD2DSupport = nullptr);
	 Texture(std::wstring _str, D2DSupport* _pD2DSupport = nullptr );
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

