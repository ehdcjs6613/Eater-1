#pragma once
#include "Component.h"
#include "EaterEngineDLL.h"

/// <summary>
/// Animator���� �����ϴ� Ŭ����
/// �ֻ��� ������Ʈ���� �����ɰ�
/// </summary>

class AnimationController : public Component
{
public:
	EATER_ENGINEDLL AnimationController();
	virtual ~AnimationController();

	void Awake();
};

