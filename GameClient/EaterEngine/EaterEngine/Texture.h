#pragma once

#include "Component.h"

/// <summary>
/// 텍스쳐 컴포넌트이다.
/// 3D매핑용, 보여지기위한 2D용의 이미지를 나타낼 정보클래스이다.
/// 우리가 쓰일 이미지의 정보만 들고있는 인터페이스이다.
/// </summary>
class Texture : public Component
{
public:
	Texture();
	virtual ~Texture();


};

