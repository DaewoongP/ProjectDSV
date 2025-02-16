#include "Button.h"
#include "Texture.h"
#include "GameInstance.h"

USING(Engine)

Button::Button()
    : UI()
    , m_pNormalTexture(nullptr), m_pClickTexture(nullptr), m_ClickFunc(), m_bClicked(false)
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

void Button::SetClickFunc(std::function<void()>&& func)
{
    m_ClickFunc = std::move(func);
}

void Button::Update()
{
    if (GAME->GetDIMouseState(InputDevice::DIMK_LBUTTON, InputDevice::KEY_UP) &&
        m_bClicked)
    {
        ChangeTexture(m_pNormalTexture);

        if (IsOnMe())
            Click();

        m_bClicked = false;
    }
    else if (GAME->GetDIMouseState(InputDevice::DIMK_LBUTTON, InputDevice::KEY_DOWN) &&
        IsOnMe())
    {
        m_bClicked = true;
        ChangeTexture(m_pClickTexture);
    }

    __super::Update();
}

void Button::Click()
{
    m_ClickFunc();
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
