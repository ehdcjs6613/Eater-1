#pragma once

/// <summary>
/// �ܺο��� ������ ���۳�Ʈ�� ����� ������ Ȯ���ϱ����� �׽�Ʈ ���۳�Ʈ 
/// </summary>

#include "Component.h"
class AI : public Component
{
public:
	AI();
	virtual ~AI();

	// Component��(��) ���� ��ӵ�
	virtual void Awake();

	virtual void Start();

	virtual void Update();
private:


};