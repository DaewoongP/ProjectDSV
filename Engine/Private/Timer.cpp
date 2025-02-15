#include "Timer.h"

USING(Engine)

HRESULT Timer::Initialize()
{
	QueryPerformanceCounter(&mFrameTime);
	QueryPerformanceCounter(&mLastTime);
	QueryPerformanceCounter(&mFixTime);
	QueryPerformanceFrequency(&mCpuTick);

	mTimeDelta = 0.f;

	return S_OK;
}

void Timer::Tick()
{
	QueryPerformanceCounter(&mFrameTime);

	if (mFrameTime.QuadPart - mFixTime.QuadPart >= mCpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&mCpuTick);
		mFixTime = mFrameTime;
	}

	mTimeDelta = ((mFrameTime.QuadPart) - (mLastTime.QuadPart)) / _float(mCpuTick.QuadPart);

	mLastTime = mFrameTime;
}

std::shared_ptr<Timer> Timer::Create()
{
	auto instance = std::make_shared<Timer>();
	FAILED_CHECK_RETURN_MSG(instance->Initialize(), nullptr, TEXT("Failed"));
	return instance;
}
