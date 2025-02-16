#include "MainApp.h"
#include "SceneLogo.h"

USING(Engine)

HRESULT Client::MainApp::Initialize()
{
	GRAPHICDESC		graphicDesc;
	ZeroMemory(&graphicDesc, sizeof(GRAPHICDESC));

	graphicDesc.hWnd = ghWnd;
	graphicDesc.ViewportSizeX = gWinSizeX;
	graphicDesc.ViewportSizeY = gWinSizeY;
	graphicDesc.WinMode = GRAPHICDESC::WINMODE::WM_WIN;

	FAILED_RETURN(GAME->Initialize(ghInst, static_cast<_uint>(SceneType::TYPEEND), graphicDesc), E_FAIL);
	GAME->StartScene(static_cast<_uint>(SceneType::LOGO), SceneLogo::Create());

#ifdef _DEBUG
	FAILED_RETURN(GAME->AddFont(TEXT("Font_135"), TEXT("../../Resource/Default/Fonts/135ex.spritefont")), E_FAIL);
#endif // _DEBUG

	return S_OK;
}

void Client::MainApp::Update(_float fTimeDelta)
{
	GAME->Update(fTimeDelta);
}

void Client::MainApp::Render()
{
	GAME->Render();
}

Client::MainApp* Client::MainApp::Create()
{
	auto instance = new Client::MainApp();
	FAILED_CHECK_RETURN_MSG(instance->Initialize(), nullptr, TEXT("Failed"));
	return instance;
}
