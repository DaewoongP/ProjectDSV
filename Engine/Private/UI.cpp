#include "UI.h"

USING(Engine)

UI::UI()
	: Component()
	, m_pShader(nullptr), m_pTexture(nullptr), m_pRectBuffer(nullptr)
	, m_vPos({0.f, 0.f}), m_fWidth(0.f), m_fHeight(0.f)
{
}

void UI::Initialize()
{

}

void UI::Update()
{
}

void UI::Render()
{
}

UI* UI::Create()
{
	return nullptr;
}

void UI::Free()
{
}
