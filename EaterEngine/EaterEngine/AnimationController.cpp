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

void AnimationController::Awake()
{


}

void AnimationController::Update()
{
	if (mKeyInputManger->GetKeyDown(VK_F3))
	{
		ChoiceAnime("Idle");
		
	}

	if (mKeyInputManger->GetKeyDown(VK_F4))
	{
		ChoiceAnime("Run");
	}
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


void AnimationController::ChoiceAnime(std::string Name)
{
	//���� �ִϸ��̼� ����Ʈ���� ������ �ִϸ��̼��� ������ �Ѱ��ش�

	int count = AnimationList->AnimList[Name]->size();
	std::vector<OneAnimation*>* data = AnimationList->AnimList[Name];
	for (int i = 0; i < count; i++)
	{
		if ((*data)[i] == nullptr) { continue; }
		if (AnimatorList[i] == nullptr) { continue; }

		AnimatorList[i]->SetAnimation((*data)[i]);
	}
}

void AnimationController::Play()
{



}
