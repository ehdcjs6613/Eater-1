#include "AnimationController.h"
#include "Animator.h"
#include "GameObject.h"
#include "KeyinputManager.h";

AnimationController::AnimationController()
{

}

AnimationController::~AnimationController()
{

}

void AnimationController::SetBoneList(std::vector<GameObject*>* m_ObjList)
{
	//게임오브젝트리스트를 애니메이터 리스트로 변경시켜줌

	int AnimatorCount = (int)m_ObjList->size();
	AnimatorList.resize(AnimatorCount);
	for (int i = 0; i < AnimatorCount; i++)
	{
		//오브젝트가 없는경우
		GameObject* obj = (*m_ObjList)[i];
		if (obj == nullptr) { continue; }

		//컨퍼넌트가 없는경우
		Animator* anime = obj->GetComponent<Animator>();
		if (anime == nullptr) { continue; }

		AnimatorList[i] = anime;
	}
}

void AnimationController::SetAnimeList(ModelAnimationData* data)
{
	AnimationList = data;
}


void AnimationController::Choice(std::string Name)
{
	//나의 애니메이션 리스트에서 선택한 애니메이션을 본에게 넘겨준다
	NowAnimationName = Name;
	//int count = (int)AnimationList->AnimList[Name]->size();
	std::vector<OneAnimation*>* data = AnimationList->AnimList[Name];

	std::vector<Animator*>::iterator it = AnimatorList.begin();
	int count = 0;
	for (it;it!= AnimatorList.end();it++)
	{
		if ((*it) == nullptr) { continue; }

		(*it)->SetAnimation((*data)[count]);
		count++;
	}
}

void AnimationController::Play(float Speed, bool Loop)
{
	//이미 한번 플레이가 호출되면 그뒤로는 호출안됨
	if (isPlay == true) { return; }

	std::vector<OneAnimation*>* data = AnimationList->AnimList[NowAnimationName];
	int count = (int)data->size();

	for (int i = 0; i < count; i++)
	{
		if ((*data)[i] == nullptr) { continue; }
		if (AnimatorList[i] == nullptr) { continue; }

		AnimatorList[i]->Play();
	}
	isPlay = true;
}

void AnimationController::Stop()
{

}
