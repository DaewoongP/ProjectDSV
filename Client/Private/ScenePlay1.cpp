#include "ScenePlay1.h"
#include "GameInstance.h"

HRESULT Client::ScenePlay1::Initialize()
{
	//GAME->Invoke(std::bind(&Client::ScenePlay1::Test, this, std::placeholders::_1), nullptr, 0.3f);
	
	return S_OK;
}

void Client::ScenePlay1::Update()
{
	DebugFunc::Text("Scene : Play1", GAME->GetTimeDelta(TEXT("MainTimer")));
	__super::Update();
}

Client::ScenePlay1* Client::ScenePlay1::Create()
{
	auto instance = new Client::ScenePlay1();
	FAILED_CHECK_RETURN_MSG(instance->Initialize(), nullptr, TEXT("Failed"));
	return instance;
}
