#pragma once
#include "Base.h"

BEGIN(Engine)

class Timer : public Base
{
public:
	_float	GetTimeDelta() const { return mTimeDelta; }

public:
	HRESULT		Initialize();
	void		Tick();

private:
	LARGE_INTEGER			mFrameTime;
	LARGE_INTEGER			mFixTime;
	LARGE_INTEGER			mLastTime;
	LARGE_INTEGER			mCpuTick;

	_float					mTimeDelta;

public:
	static Timer* Create();
	virtual void Free() override {}
};

END
