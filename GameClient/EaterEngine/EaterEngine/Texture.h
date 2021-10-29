#pragma once


/// <summary>
/// 텍스쳐 컴포넌트이다.
/// 3D매핑용, 보여지기위한 2D용의 이미지를 나타낼 정보클래스이다.
/// 우리가 쓰일 이미지의 정보만 들고있는 인터페이스이다.
/// </summary>
/// 

class D2DSupport;

#include "Component.h"

/// <summary>
/// 보여질 이미지의 '정보 만' 담고있는 클래스이다.
/// 나머지는 그려질 특성에 따라 분기를 나누어서 하위클래스로 작성
/// </summary>

/// <summary>
/// 일단 지금은.. 이걸 이미지라 생각하고 띄어보자
/// </summary>
/// 	//#부분은 나중에  Texture2D라는
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


	//# 하위클래스로 따로 분리시켜서 적용
	void Render();
	
public:
	//Component계열의 공통 순환되는함수들
	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update()override;
};

