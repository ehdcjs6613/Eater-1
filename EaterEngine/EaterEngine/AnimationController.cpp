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

void AnimationController::Update()
{
	if (mKeyInputManger->GetKeyDown(VK_F3))
	{
		Choice("Roll");	
	}

	if (mKeyInputManger->GetKeyDown(VK_F4))
	{
		Choice("Run");
	}
}

void AnimationController::SetBoneList(std::vector<GameObject*>* m_ObjList)
{
	//게임오브젝트리스트를 애니메이터 리스트로 변경시켜줌

	int AnimatorCount = (int)m_ObjList->size();
	if (AnimatorCount == 0) { return; }

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
	if (nullptr == data) { return; }
	AnimationList = data;
}

void AnimationController::Choice(std::string Name)
{
	//나의 애니메이션 리스트에서 선택한 애니메이션을 본에게 넘겨준다
	NowAnimationName = Name;
	isChoice = true;
	std::vector<OneAnimation*>* data = AnimationList->AnimList[Name];
	

	//본의 애니메이션을 넣어준다
	int Count = (int)AnimatorList.size();
	for (int i = 0; i < Count; i++)
	{
		if (AnimatorList[i] == nullptr) { continue; }
		
		AnimatorList[i]->SetAnimation((*data)[i]);
	}
}

void AnimationController::Play(float Speed, bool Loop)
{



}

void AnimationController::Stop()
{

}
