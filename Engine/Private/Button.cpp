#include "Button.h"
#include "Texture.h"
#include "GameInstance.h"

USING(Engine)

Button::Button()
    : UI()
    , m_pNormalTexture(nullptr), m_pClickTexture(nullptr)
{
}

void Button::Initialize(const std::wstring& wstrTexturePath, const std::wstring& wstrClickTexturePath, _float2 vPos, _float fWidth, _float fHeight)
{
    UI::Initialize(wstrTexturePath, vPos, fWidth, fHeight);

    m_pNormalTexture = Texture::Create(wstrTexturePath);
    m_pClickTexture = Texture::Create(wstrClickTexturePath);

    AddComponent(TEXT("NormalTexture"), m_pNormalTexture);
    Utility::SafeAddRef(m_pNormalTexture);
    AddComponent(TEXT("ClickTexture"), m_pClickTexture);
    Utility::SafeAddRef(m_pClickTexture);
}

void Button::Update()
{
    if (GAME->GetDIMouseState(InputDevice::DIMK_LBUTTON, InputDevice::KEY_UP) &&
        IsOnMe())
    {
        Click();
        ChangeTexture(m_pNormalTexture);
    }
    else if (GAME->GetDIMouseState(InputDevice::DIMK_LBUTTON, InputDevice::KEY_DOWN) &&
        IsOnMe())
    {
        ChangeTexture(m_pClickTexture);
    }

    __super::Update();
}

Button* Button::Create(const std::wstring& wstrTexturePath, const std::wstring& wstrClickTexturePath, _float2 vPos, _float fWidth, _float fHeight)
{
    auto instance = new Button();
    instance->Initialize(wstrTexturePath, wstrClickTexturePath, vPos, fWidth, fHeight);
    return instance;
}

void Button::Free()
{
    Utility::SafeRelease(m_pNormalTexture);
    Utility::SafeRelease(m_pClickTexture);

    __super::Free();
}
