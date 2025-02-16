#include "GameInstance.h"
#include "GraphicDevice.h"
#include "TimerManager.h"
#include "FontManager.h"
#include "ImguiManager.h"
#include "TextureManager.h"

USING(Engine)

IMPLEMENT_SINGLETON(Engine::GameInstance)

ComPtr<ID3D11Device> GameInstance::GetDevice() const { return GRAPHIC->GetDevice(); }
ComPtr<ID3D11DeviceContext> GameInstance::GetDeviceContext() const { return GRAPHIC->GetDeviceContext(); }

HRESULT GameInstance::Initialize(HINSTANCE _hInst, _uint _numLevels, const GRAPHICDESC& _graphicDesc, _Inout_ ComPtr<ID3D11Device>& _device, _Inout_ ComPtr<ID3D11DeviceContext>& _deviceContext)
{
    FAILED_RETURN(GRAPHIC->Initialize(_graphicDesc.hWnd, _graphicDesc.WinMode, _graphicDesc.ViewportSizeX, _graphicDesc.ViewportSizeY, _device, _deviceContext), E_FAIL);
    FAILED_RETURN(INPUT->Initialize(_hInst, _graphicDesc.hWnd), E_FAIL);
    FAILED_RETURN(RENDER->Initialize(), E_FAIL);
    FAILED_RETURN(GUI->Initialize(_graphicDesc.hWnd, _device, _deviceContext), E_FAIL);

    return S_OK;
}

void GameInstance::Tick(_float _timeDelta)
{
    INPUT->Tick();
    
    TIMER->Tick(_timeDelta);
}

HRESULT GameInstance::Render()
{
    FAILED_RETURN(GRAPHIC->RenderBegin(_float4(0.f, 0.f, 1.f, 0.f)), E_FAIL);
    GUI->Begin();
    FAILED_RETURN(RENDER->Draw(), E_FAIL);
    GUI->End();
    FAILED_RETURN(GRAPHIC->RenderEnd(), E_FAIL);

    return S_OK;
}

#pragma region GraphicDevice
HRESULT GameInstance::RenderBegin(_float4 _clearColor) { return GRAPHIC->RenderBegin(_clearColor); }
HRESULT GameInstance::RenderEnd() { return GRAPHIC->RenderEnd(); }
#pragma endregion

#pragma region TimerManager
_float GameInstance::GetTimeDelta(const std::wstring& _timerTag) { return TIMER->GetTimeDelta(_timerTag); }
void GameInstance::TickTimeDelta(const std::wstring& _timerTag) { return TIMER->TickTimeDelta(_timerTag); }
HRESULT GameInstance::AddTimer(const std::wstring& _timerTag) { return TIMER->AddTimer(_timerTag); }
void GameInstance::Invoke(std::function<void(void*)> _func, void* _arg, _float _callTime, _bool _loop) { return TIMER->Invoke(_func, _arg, _callTime, _loop); }
#pragma endregion

#pragma region InputDevice
_bool GameInstance::GetDIKeyState(_ubyte _keyID, InputDevice::KEYSTATE _state) { return INPUT->GetDIKeyState(_keyID, _state); }
_bool GameInstance::GetDIMouseState(InputDevice::MOUSEKEYSTATE _mouseID, InputDevice::KEYSTATE _state) { return INPUT->GetDIMouseState(_mouseID, _state); }
_long GameInstance::GetDIMouseMove(InputDevice::MOUSEMOVESTATE _mouseMoveID) { return INPUT->GetDIMouseMove(_mouseMoveID); }
#pragma endregion

#pragma region FontManager
HRESULT GameInstance::AddFont(const std::wstring& _fontTag, const std::wstring& _fontFilePath) { return FONT->AddFont(_fontTag, _fontFilePath); }
HRESULT GameInstance::RenderFont(const std::wstring& _fontTag, const std::wstring& _text, const _float2& _position, _fvector _color, _float _rotation, const _float2& _origin, _float _scale) { return FONT->Render(_fontTag, _text, _position, _color, _rotation, _origin, _scale); }
#pragma endregion

#pragma region ImguiManager
void GameInstance::ImguiBegin() { GUI->Begin(); }
void GameInstance::ImguiEnd() { GUI->End(); }
#pragma endregion

#pragma region RenderManager
void GameInstance::AddRenderGroup(RenderManager::RenderType _renderType, Component* _component) { return RENDER->AddRenderGroup(_renderType, _component); }
#pragma endregion

HRESULT GameInstance::ClearLevelResources(_uint _preLevelIndex)
{
    TEXTURE->ClearLevelTextures();

    return S_OK;
}

void GameInstance::Release()
{
    GAME->DestroyInstance();

    GRAPHIC->DestroyInstance();

    RENDER->DestroyInstance();

    TIMER->DestroyInstance();

    INPUT->DestroyInstance();

    FONT->DestroyInstance();

    GUI->DestroyInstance();

    TEXTURE->DestroyInstance();
}
