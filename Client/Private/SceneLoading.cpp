#include "SceneLoading.h"
#include "GameInstance.h"

#include "SceneLogo.h"

Client::SceneLoading::SceneLoading()
	: m_pLoader(nullptr), m_eNextSceneType(SceneType::TYPEEND)
{

}

Client::SceneLoading::~SceneLoading()
{
}

HRESULT Client::SceneLoading::Initialize(SceneType _sceneType)
{
	m_eNextSceneType = _sceneType;

	m_pLoader = Client::Loader::Create(_sceneType);

	return S_OK;
}

void Client::SceneLoading::Update()
{
	DebugFunc::Text("Loading...", GAME->GetTimeDelta(TEXT("MainTimer")));

	if (false == m_pLoader->IsFinished())
		return;

	Scene* pScene = nullptr;

	switch (m_eNextSceneType)
	{
	case SceneType::LOGO:
		pScene = Client::SceneLogo::Create();
		break;
	}
	if (nullptr == pScene)
		return;

	GAME->StartScene(static_cast<_uint>(m_eNextSceneType), pScene);
}

Client::SceneLoading* Client::SceneLoading::Create(SceneType _nextSceneType)
{
	auto instance = new Client::SceneLoading();
	FAILED_CHECK_RETURN_MSG(instance->Initialize(_nextSceneType), nullptr, TEXT("Failed"));
	return instance;
}

void Client::SceneLoading::Free()
{
	Utility::SafeRelease(m_pLoader);
	__super::Free();
}
