#include "Popup.h"

USING(Engine)

Popup::Popup()
    : UI()
{
}

void Popup::Update()
{
}

void Popup::Render()
{
}

Popup* Popup::Create(const std::wstring& wstrTexturePath, _float2 vPos, _float fWidth, _float fHeight)
{
    auto instance = new Popup();
    instance->Initialize(wstrTexturePath, vPos, fWidth, fHeight);
    return instance;
}

void Popup::Free()
{
    __super::Free();
}
