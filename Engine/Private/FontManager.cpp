#include "FontManager.h"
#include "CustomFont.h"

USING(Engine)

IMPLEMENT_SINGLETON(FontManager)

HRESULT FontManager::AddFont(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _deviceContext, const std::wstring& _fontTag, const std::wstring& _fontFilePath)
{
	if (nullptr != FindFont(_fontTag))
	{
		DISPLAY_ERROR(TEXT("Already Have FontTag"));
		__debugbreak();
		return E_FAIL;
	}
	
	mFonts.emplace(_fontTag, CustomFont::Create(_device, _deviceContext, _fontFilePath));

	return S_OK;
}

HRESULT FontManager::Render(const std::wstring& _fontTag, const std::wstring& _text, const _float2& _position, _fvector _color, _float _rotation, const _float2& _origin, _float _scale)
{
	auto	font = FindFont(_fontTag);

	NULL_CHECK_RETURN_MSG(font, E_FAIL, TEXT("Failed Find Custom Font"));

	return font->Render(_text, _position, _color, _rotation, _origin, _scale);
}

std::shared_ptr<class CustomFont> FontManager::FindFont(const std::wstring& _fontTag)
{
	auto	iter = mFonts.find(_fontTag);

	if (iter == mFonts.end())
		return nullptr;

	return iter->second;
}
