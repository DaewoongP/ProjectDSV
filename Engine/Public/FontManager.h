#pragma once
#include "Engine_Defines.h"

BEGIN(Engine)

class FontManager
{
	DECLARE_SINGLETON(FontManager)
public:
	FontManager() = default;
	~FontManager() = default;

public:
	HRESULT AddFont(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _deviceContext, const std::wstring& _fontTag, const std::wstring& _fontFilePath);
	HRESULT Render(const std::wstring& _fontTag, const std::wstring& _text, const _float2& _position, _fvector _color, _float _rotation, const _float2& _origin, _float _scale);

private:
	_umap<std::wstring, std::shared_ptr<class CustomFont>>			mFonts;

private:
	std::shared_ptr<class CustomFont> FindFont(const std::wstring& _fontTag);
};

END

#define FONT		GET_SINGLE(Engine::FontManager)