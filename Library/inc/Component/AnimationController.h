#pragma once
#include "Component.h"
#include "EaterEngineDLL.h"
#include <string>
#include <vector>

/// <summary>
/// Animator���� �����ϴ� Ŭ����
/// �ֻ��� ������Ʈ���� �����ɰ�
/// </summary>

class ModelAnimationData;
class Animator;
class AnimationController : public Component
{
public:
	EATER_ENGINEDLL AnimationController();
	EATER_ENGINEDLL virtual ~AnimationController();

	void SetBoneList(std::vector<GameObject*>* mobjList);
	void SetAnimeList(ModelAnimationData* data);


	EATER_ENGINEDLL void Choice(std::string Name);		//�ִϸ��̼� ����
	EATER_ENGINEDLL void Play(float Speed, bool Loop);
	EATER_ENGINEDLL void Stop();
	
private:
	//������ �ִϸ����� ����Ʈ
	std::vector<Animator*> AnimatorList;

	//�Ѱ��� �𵨿� ����ִ� �ִϸ��̼� ����Ʈ
	ModelAnimationData* AnimationList;

	std::string NowAnimationName;
	bool isPlay;
};

