#pragma once
#include "Base.h"
#include "Client_Defines.h"

BEGIN(Client)

class Loader : public Engine::Base
{
public:
	Loader() = default;
	~Loader() = default;
public:
	_bool IsFinished() const { return mFinished; }

public:
	HRESULT Initialize(SceneType _levelType);
	HRESULT Loading();

private:
	HRESULT LoadingForLogo();
	HRESULT LoadingForPlay1();

private:
	HANDLE				mhThread;
	CRITICAL_SECTION	mCriticalSection;

private:
	SceneType			m_eNextSceneType;
	_tchar				mLoading[MAX_PATH];
	_bool				mFinished;

public:
	static Loader* Create(SceneType _levelType);
	virtual void Free() override;
};

END