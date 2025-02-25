#include "SceneLogo.h"
#include "GameInstance.h"
#include "SceneLoading.h"
#include "Button.h"

USING(Client)

SceneLogo::SceneLogo()
	: Scene()
	, m_pMainLogo(nullptr), m_pStartButton(nullptr), m_pEndButton(nullptr)
{
}

void Client::SceneLogo::Initialize()
{
	m_pMainLogo = Engine::UI::Create(TEXT("../../Resource/Interface/Logo/MainLogo.png"), 
		{ gWinSizeX * 0.5f, gWinSizeY * 0.5f }, gWinSizeX, gWinSizeY);
	Utility::SafeAddRef(m_pMainLogo);
	AddComponent(TEXT("MainLogo"), m_pMainLogo);

	m_pStartButton = Engine::Button::Create(TEXT("../../Resource/Interface/Logo/start.png"), TEXT("../../Resource/Interface/Logo/start_click.png"), 
		{ 1000.f, 500.f }, 128, 64);
	Utility::SafeAddRef(m_pStartButton);
	AddComponent(TEXT("StartButton"), m_pStartButton);
	m_pStartButton->SetClickFunc([]() {
		DebugFunc::Text("Enter!");
		//GAME->StartScene(static_cast<_uint>(SceneType::LOADING), Client::SceneLoading::Create(SceneType::PLAY1));
		});

	m_pEndButton = Engine::Button::Create(TEXT("../../Resource/Interface/Logo/end.png"), TEXT("../../Resource/Interface/Logo/end_click.png"),
		{ 1000.f, 628.f }, 128, 64);
	Utility::SafeAddRef(m_pEndButton);
	AddComponent(TEXT("EndButton"), m_pEndButton);
	m_pEndButton->SetClickFunc([]() {
		PostQuitMessage(0);
		});
}

void SceneLogo::Update()
{
	DebugFunc::Text("Scene : Logo", GAME->GetTimeDelta(TEXT("MainTimer")));

	RenderSequence();

	__super::Update();
}

void SceneLogo::RenderSequence()
{
	GAME->AddRenderGroup(Engine::RenderManager::RenderType::PRIORITY, m_pMainLogo);
	GAME->AddRenderGroup(Engine::RenderManager::RenderType::PRIORITY, m_pStartButton);
	GAME->AddRenderGroup(Engine::RenderManager::RenderType::PRIORITY, m_pEndButton);
}

SceneLogo* Client::SceneLogo::Create()
{
	auto instance = new Client::SceneLogo();
	instance->Initialize();
	return instance;
}

void SceneLogo::Free()
{
	Utility::SafeRelease(m_pMainLogo);
	Utility::SafeRelease(m_pStartButton);
	Utility::SafeRelease(m_pEndButton);

	__super::Free();
}
