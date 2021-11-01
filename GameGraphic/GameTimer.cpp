
#include "GameTimer.h"
#include <windows.h>

GameTimer::GameTimer()
{
	__int64 Counts_Per_Sec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&Counts_Per_Sec);
	mSecondsPerCount = 1.0 / (double)Counts_Per_Sec;
}

// Reset()�� ȣ�� �� �������� ������ ��� �ð��� ���� �ȴ�.
// ���� �Ͻ����� ���¶�� �ϴ��� �Ͻ����� �ð��� ���ܵ� �� ��� �ð��� ���� �ȴ�.
float GameTimer::TotalTime() const
{
	/// ���� �Ͻ� ���� ���¶��..
	if (mStopped)
	{
		return (float)(((mStopTime - mPausedTime) - mBaseTime) * mSecondsPerCount);
	}
	/// �Ͻ� ���� ���°� �ƴ϶��..
	else
	{
		return (float)(((mCurrTime - mPausedTime) - mBaseTime) * mSecondsPerCount);
	}
}

// DTime�� ������ �ش�.
float GameTimer::DeltaTime() const
{
	return (float)mDeltaTime;
}

void GameTimer::Reset()
{
	__int64 Current_Time;
	QueryPerformanceCounter((LARGE_INTEGER*)&Current_Time);
	
	// Reset()�� ȣ�� �� ������ BaseTime�� ���� �صд�.
	mBaseTime = Current_Time;
	mPrevTime = Current_Time;
	// �Ͻ� ������ Ǯ�� ��.
	mStopTime = 0;
	mStopped = false;
}

void GameTimer::Start()
{
	__int64 Current_Time;
	QueryPerformanceCounter((LARGE_INTEGER*)&Current_Time);

	// ���� ���� �����϶� Start()�� ȣ�� �ϸ� ���� ���¸� ���� �����ش�.
	if (mStopped)
	{
		// ������ ���� ���� ���¶�� �Ͻ� ���� �� �ð��� ���� ���۽ð����� ���� �ð��� �� ���̴�.
		mPausedTime += (Current_Time - mStopTime);

		mPrevTime = Current_Time;
		mStopTime = 0;
		mStopped = false;
	}
}

void GameTimer::Stop()
{
	// ���� �������°� �ƴ� �� Stop()�� ȣ�� �ϰ� �ȴٸ�
	if (!mStopped)
	{
		__int64 Current_Time;
		QueryPerformanceCounter((LARGE_INTEGER*)&Current_Time);

		// ���� �� ������ �ð��� ���� �ð����� ������ �ΰ� �����Ǿ��ٴ� �÷��׸� �Ҵ�.
		mStopTime = Current_Time;
		mStopped = true;
	}
}

void GameTimer::Tick()
{
	// ���� �������� ��� DTime�� 0���� �����ϰ� �����Ѵ�.
	if (mStopped)
	{
		mDeltaTime = 0.0;
		return;
	}

	__int64 Current_Time;
	QueryPerformanceCounter((LARGE_INTEGER*)&Current_Time);
	
	mCurrTime = Current_Time;
	mDeltaTime = (mCurrTime - mPrevTime) * mSecondsPerCount;
	mPrevTime = mCurrTime;

	// ���� ��� �������� ���� �� ��츦 ����Ͽ�..
	if (mDeltaTime < 0.0)
	{
		mDeltaTime = 0.0;
	}
}
