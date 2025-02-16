#pragma once
#include "Scene.h"
#include "Loader.h"

BEGIN(Client)

class SceneLoading : public Engine::Scene
{
public:
	SceneLoading();
	~SceneLoading();

public:
	HRESULT Initialize(SceneType _SceneType);
	virtual void Update() override;

private:
	Loader*			m_pLoader;
	SceneType		m_eNextSceneType;

public:
	static SceneLoading* Create(SceneType _nextSceneType);
	virtual void Free() override;
};

END