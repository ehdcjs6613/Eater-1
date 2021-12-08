#include "AnimationController.h"
#include "Animator.h"
#include "GameObject.h"
#include "KeyinputManager.h"
#include "MeshFilter.h"

AnimationController::AnimationController()
{

}

AnimationController::~AnimationController()
{

}

void AnimationController::SetBoneList(std::vector<GameObject*>* m_ObjList)
{
	//���ӿ�����Ʈ����Ʈ�� �ִϸ����� ����Ʈ�� ���������
	int AnimatorCount = (int)m_ObjList->size();
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
	AnimationList = data;
}

void AnimationController::Choice(std::string Name)
{
	//���� �ִϸ��̼� ����Ʈ���� ������ �ִϸ��̼��� ������ �Ѱ��ش�
	NowAnimationName = Name;
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
	//Animator ���۳�Ʈ���� Play�Լ��� �����Ų��
	std::vector<Animator*>::iterator it = AnimatorList.begin();
	for (it; it != AnimatorList.end(); it++)
	{
		if ((*it) == nullptr) { continue; }

		(*it)->Play(Speed, Loop);
	}
}

void AnimationController::Stop()
{
	//Animator ���۳�Ʈ���� Play�Լ��� �����Ų��
	std::vector<Animator*>::iterator it = AnimatorList.begin();
	for (it; it != AnimatorList.end(); it++)
	{
		if ((*it) == nullptr) { continue; }
		(*it)->Stop();
	}
}

int AnimationController::GetNowFrame()
{
	if (AnimatorList[0] == nullptr)
	{
		return 0;
	}
	return AnimatorList[0]->GetNowFrame();
}

int AnimationController::GetEndFrame()
{
	if (AnimatorList[0] == nullptr)
	{
		return 0;
	}
	return AnimatorList[0]->GetEndFrame()-1;
}
