#pragma once

/// <summary>
/// �ܺο��� ������ ���۳�Ʈ�� ����� ������ Ȯ���ϱ����� �׽�Ʈ ���۳�Ʈ 
/// </summary>

class Transform;
#include "Component.h"
class AI : public Component
{
public:
	AI();
	virtual ~AI();

	// Component��(��) ���� ��ӵ�
	virtual void Awake();
	virtual void Update();
private:
	Transform* trans;

};