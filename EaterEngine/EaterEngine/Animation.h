#pragma once

/// <summary>
/// ���� �ִϸ��̼��� ���������� ������ ����ִ� ���۳�Ʈ 
/// </summary>

namespace ParserData
{
	struct OneAnimation;
}


#include "Component.h"
class Animation : public Component
{
public:
	void Update();

	void SetAnimation(ParserData::OneAnimation*);
private:
	ParserData::OneAnimation* AnimationData;


};