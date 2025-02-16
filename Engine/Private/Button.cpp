#include "Button.h"
#include "Texture.h"
#include "GameInstance.h"

USING(Engine)

Button::Button()
    : UI()
    , m_pNormalTexture(nullptr), m_pClickTexture(nullptr), m_ClickFunc()
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

void Button::LButtonDown(_int x, _int y)
{
    ChangeTexture(m_pClickTexture);
    __super::LButtonDown(x, y);
}

void Button::RButtonDown(_int x, _int y)
{
    __super::RButtonDown(x, y);
}

void Button::LButtonUp(_int x, _int y)
{
    ChangeTexture(m_pNormalTexture);
    if (IsOnMe(x, y))
        m_ClickFunc();
    __super::LButtonUp(x, y);
}

void Button::RButtonUp(_int x, _int y)
{
    __super::RButtonUp(x, y);
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
