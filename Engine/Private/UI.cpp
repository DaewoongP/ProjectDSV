#include "UI.h"

USING(Engine)

UI::UI()
	: Component()
	, mShader(nullptr), mTexture(nullptr), mRectBuffer(nullptr)
{
}

UI::UI(const UI& rhs)
	: Component(rhs)
	, mShader(rhs.mShader), mTexture(rhs.mTexture), mRectBuffer(rhs.mRectBuffer)
{
}

HRESULT UI::Initialize()
{
	return E_NOTIMPL;
}

void UI::Tick(_float _timeDelta)
{
}

void UI::LateTick(_float _timeDelta)
{
}

HRESULT UI::Render()
{
	return S_OK;
}

HRESULT UI::InitializePrototype()
{
	return E_NOTIMPL;
}

std::shared_ptr<UI> UI::Create()
{
	return std::shared_ptr<UI>();
}

std::shared_ptr<Component> UI::Clone(void* _arg)
{
	return std::shared_ptr<Component>();
}
