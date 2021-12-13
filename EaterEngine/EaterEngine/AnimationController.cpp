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
	//���ӿ�����Ʈ����Ʈ�� �ִϸ����� ����Ʈ�� ���������

	int AnimatorCount = (int)m_ObjList->size();
	if (AnimatorCount == 0) { return; }

	AnimatorList.resize(AnimatorCount);
	for (int i = 0; i < AnimatorCount; i++)
	{
		//������Ʈ�� ���°��
		GameObject* obj = (*m_ObjList)[i];
		if (obj == nullptr) { continue; }

		//���۳�Ʈ�� ���°��
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
	//���� �ִϸ��̼� ����Ʈ���� ������ �ִϸ��̼��� ������ �Ѱ��ش�
	NowAnimationName = Name;
	isChoice = true;
	std::vector<OneAnimation*>* data = AnimationList->AnimList[Name];
	

	//���� �ִϸ��̼��� �־��ش�
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
