#pragma once
#include "Engine_Defines.h"

BEGIN(Engine)
class Timer;

class TimerManager
{
	typedef struct tagFuncTimer
	{
		_float timeAcc;
		_float callTime;
		std::function<void(void*)> func;
		void* arg;
		_bool loop;
	}FUNCTIMER;

	DECLARE_SINGLETON(TimerManager)
public:
	TimerManager() = default;
	~TimerManager() = default;

public:
	_float		GetTimeDelta(const std::wstring& _timerTag);
	void		TickTimeDelta(const std::wstring& _timerTag);

public:
	HRESULT		AddTimer(const std::wstring& _timerTag);
	void		Invoke(std::function<void(void*)> _func, void* _arg, _float _callTime, _bool _loop = false);
	void		Tick(_float _timeDelta);

private:
	std::shared_ptr<Timer> FindTimer(const std::wstring& _timerTag);

private:
	_umap<std::wstring, std::shared_ptr<Timer>>	mTimers;

private:
	std::vector<FUNCTIMER>			mFunctionTimers;
};

END

#define TIMER		GET_SINGLE(Engine::TimerManager)