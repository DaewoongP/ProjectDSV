#include "CustomFont.h"
#include "GameInstance.h"

USING(Engine)

HRESULT CustomFont::Initialize(const std::wstring& _fontFilePath)
{
	m_pBatch = new SpriteBatch(GAME->GetDeviceContext().Get());
	m_pFont = new SpriteFont(GAME->GetDevice().Get(), _fontFilePath.c_str());

	return S_OK;
}

HRESULT CustomFont::Render(const std::wstring& _text, const _float2& _position, _fvector _color, _float _rotation, const _float2& _origin, _float _scale)
{
	GAME->GetDeviceContext()->GSSetShader(nullptr, nullptr, 0);

	m_pBatch->Begin();

	m_pFont->DrawString(m_pBatch, _text.c_str(), _position, _color, _rotation, _origin, _scale);

	m_pBatch->End();

	return S_OK;
}

CustomFont* CustomFont::Create(const std::wstring& _fontFilePath)
{
	auto instance = new CustomFont();
	FAILED_CHECK_RETURN_MSG(instance->Initialize(_fontFilePath), nullptr, TEXT("Failed"));
	return instance;
}

void CustomFont::Free()
{
	Utility::SafeDelete(m_pFont);
	Utility::SafeDelete(m_pBatch);
}
