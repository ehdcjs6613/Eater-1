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
	//�̹� �ѹ� �÷��̰� ȣ��Ǹ� �׵ڷδ� ȣ��ȵ�
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
