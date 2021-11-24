#pragma once
#include "Component.h"
#include "EaterEngineDLL.h"
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

	void Awake();
	void Update();

	void SetBoneList(std::vector<GameObject*>* mobjList);
	void SetAnimeList(ModelAnimationData* data);
	void ChoiceAnime(std::string Name);
	void Play();
	
	//������ �ִϸ����� ����Ʈ
	std::vector<Animator*> AnimatorList;

	//�Ѱ��� �𵨿� ����ִ� �ִϸ��̼� ����Ʈ
	ModelAnimationData* AnimationList;
};

