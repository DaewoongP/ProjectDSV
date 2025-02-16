#include "TimerManager.h"
#include "Timer.h"
USING(Engine)

IMPLEMENT_SINGLETON(TimerManager)

TimerManager::~TimerManager()
{
	for (auto& timer : mTimers)
		Utility::SafeRelease(timer.second);
}

_float TimerManager::GetTimeDelta(const std::wstring& _timerTag)
{
	Timer* timer = FindTimer(_timerTag);
	if (nullptr == timer)
		return 0.0;

	return timer->GetTimeDelta();
}

void TimerManager::TickTimeDelta(const std::wstring& _timerTag)
{
	Timer* timer = FindTimer(_timerTag);
	if (nullptr == timer)
		return;

	timer->Tick();
}

HRESULT TimerManager::AddTimer(const std::wstring& _timerTag)
{
	Timer* timer = FindTimer(_timerTag);

	if (nullptr != timer)
	{
		MSG_BOX("Already Have TimerTag");
		__debugbreak();
		return E_FAIL;
	}
	
	mTimers.emplace(_timerTag, Timer::Create());

	return S_OK;
}

void TimerManager::Invoke(std::function<void(void*)> _func, void* _arg, _float _callTime, _bool _loop)
{
	FUNCTIMER funcTimer;
	funcTimer.func = _func;
	funcTimer.arg = _arg;
	funcTimer.callTime = _callTime;
	funcTimer.loop = _loop;
	funcTimer.timeAcc = 0.f;

	mFunctionTimers.emplace_back(funcTimer);
}

void TimerManager::Update(_float _timeDelta)
{
	for (auto iter = mFunctionTimers.begin(); iter != mFunctionTimers.end();)
	{
		iter->timeAcc += _timeDelta;

		if (iter->timeAcc >= iter->callTime)
		{
			iter->func(iter->arg);
			iter->timeAcc = 0.f;

			if (true == iter->loop)
				++iter;
			else
				iter = mFunctionTimers.erase(iter);
		}
		else
			++iter;
	}
}

Timer* TimerManager::FindTimer(const std::wstring& _timerTag)
{
	auto		iter = mTimers.find(_timerTag);

	if (iter == mTimers.end())
		return nullptr;
	
	return iter->second;
}
