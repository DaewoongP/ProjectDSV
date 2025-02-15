#pragma once
#include "Level.h"

BEGIN(Engine)

class LevelManager
{
	DECLARE_SINGLETON(LevelManager)
public:
	LevelManager() = default;
	~LevelManager() = default;

public:
	_uint GetCurrentLevelIndex() const { return mLevelIndex; }

public:
	HRESULT OpenLevel(_uint _levelIndex, std::unique_ptr<Level>&& _newLevel);
	void Tick(_float _timeDelta);

private:
	std::unique_ptr<Level>		mCurrentLevel;
	_uint						mLevelIndex;
};

END

#define LEVEL		GET_SINGLE(Engine::LevelManager)