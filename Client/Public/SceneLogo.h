#pragma once
#include "Scene.h"
#include "Client_Defines.h"

BEGIN(Engine)
class UI;
class Button;
END

BEGIN(Client)

class SceneLogo : public Engine::Scene
{
public:
	SceneLogo();
	~SceneLogo() = default;

public:
	void Initialize();
	virtual void Update() override;
	void RenderSequence();

private:
	Engine::UI*			m_pMainLogo;
	Engine::Button*		m_pStartButton;

public:
	static SceneLogo* Create();
	virtual void Free() override;
};

END