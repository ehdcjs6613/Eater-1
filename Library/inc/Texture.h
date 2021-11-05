#pragma once
#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW

#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#include <atlstr.h>
/// <summary>
/// �ؽ��� ������Ʈ�̴�.
/// 3D���ο�, ������������ 2D���� �̹����� ��Ÿ�� ����Ŭ�����̴�.
/// �츮�� ���� �̹����� ������ ����ִ� �������̽��̴�.
/// </summary>

#include "Component.h"
class D2DSupport;


class  Texture : public Component
{
private:
	D2DSupport* m_pD2DSupport;
	ATL::CString m_str;
public:
	 Texture();
	 Texture(D2DSupport* _pD2DSupport = nullptr);
	 Texture(ATL::CString _str, D2DSupport* _pD2DSupport = nullptr );
	 virtual ~Texture();

public:
	void LoadTexture(ATL::CString _str);

public:

	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update()override;
};

