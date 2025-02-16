#pragma once
#include "Scene.h"
#include "Client_Defines.h"

BEGIN(Client)

class ScenePlay1 : public Engine::Scene
{
public:
	ScenePlay1() = default;
	~ScenePlay1() = default;

public:
	HRESULT Initialize();
	virtual void Update() override;

public:
	static ScenePlay1* Create();
	virtual void Free() override { __super::Free(); }
};

END