#pragma once
#include "Component.h"
#include "EaterEngineDLL.h"
#include <string>
#include <vector>

/// <summary>
/// Animator들을 관리하는 클래스
/// 최상위 오브젝트에만 생성될것
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


	EATER_ENGINEDLL void Choice(std::string Name);		//애니메이션 선택
	EATER_ENGINEDLL void Play(float Speed, bool Loop);
	EATER_ENGINEDLL void Stop();
	
private:
	//본들의 애니메이터 리스트
	std::vector<Animator*> AnimatorList;

	//한개의 모델에 들어있는 애니메이션 리스트
	ModelAnimationData* AnimationList;

	std::string NowAnimationName;
	bool isPlay;
};

