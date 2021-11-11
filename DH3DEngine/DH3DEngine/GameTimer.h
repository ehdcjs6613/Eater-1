#pragma once

class GameTimer
{
public:
	GameTimer();

	float TotalTime() const;	// �� ������ ��ȯ.
	float DeltaTime() const;	// �� ������ ��ȯ.

	void Reset();	// �޼��� ������ ȣ�� �Ǳ� ���� ȣ���ؾ� �Ѵ�.
	void Start();	// ���� �ɶ� ȣ��
	void Stop();	// ���� �� ȣ��.
	void Tick();	// �� ������ ���� ȣ��.

private:
	double mSecondsPerCount = 0.0f;	// �ð����� �������ֱ� ���� ���� (�ʴ� Ƚ���� ����)
	double mDeltaTime = -1.0f;		// ���� �����Ӱ��� �ð� ����.

	__int64 mBaseTime = 0;			// �Ͻ����� �� ���� �ð��� �����ϰ� �� �ð��� ��ȯ���ֱ� ���ؼ� ����. (Ÿ�̸Ӱ� ������ �� ������ �ð��� ����)
	__int64 mPausedTime = 0;		// �Ͻ����� �� �ð�.
	__int64 mStopTime = 0;			// ���߱� ������ �ð�.
	__int64 mPrevTime = 0;			// ���� �������� �ð��� ����.
	__int64 mCurrTime = 0;			// ���� �������� �����صα� ���� ����.

	bool mStopped = false;			// ���� �Ͻ������� �Ǿ��ִ� 
};

