#pragma once
#include "Component.h"
#include "EngineData.h"
#include <vector>
/// <summary>
/// ���� �ִϸ��̼��� ���������� ������ ����ִ� ���۳�Ʈ 
/// </summary>

namespace ParserData
{
	struct OneAnimation;
}

class Transform;
class Animator : public Component
{
public:
	Animator();
	virtual ~Animator();

	void Start();
	void Update();

	//�ִϸ��̼��� �־��ش�
	void SetAnimation(ParserData::OneAnimation*);

	//�Ű������� ���� �ð���ŭ �ִϸ��̼��Ѱ��� �����Ŵ
	void SetPlayTime(float time,bool Loop);
	void Stop();
	void ReStart();


	//�ִϸ��̼��� �����Ӽ��� ������Ų��
	void CreateFrame(int CreateCount);

	void ChoiceAnime(int index);
private:
	//1�ʿ� �ִϸ��̼� �Ѱ��� ���ư����ҋ� �����ӽð�
	float GetOnePlayTime(float mPlayTime,int EndFrameCount);
	void AnimeFrameIndex();

	//�ִϸ��̼� ��� ����Ʈ
	std::vector<ParserData::OneAnimation*> AnimeData;

	//���� �ִϸ��̼� 
	ParserData::OneAnimation* NowAnimationData;


	DirectX::XMMATRIX XM_ROT;
	DirectX::XMMATRIX XM_POS;
	DirectX::XMMATRIX XM_SCL;

	float	mTime;			//���� ���Ÿ��
	float	PlayTime;		//�ִϸ��̼��� �ѹ��� ���� �ð� 
	int		AnimeIndex;		//�ִϸ��̼� �ε�����
	bool	mLoop;			//�ݺ� ��� ����
	bool	mStop;


	Transform* transfrom;
};