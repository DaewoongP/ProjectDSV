#pragma once
#include "Base.h"

BEGIN(Engine)

class CustomFont : public Base
{
public:
	HRESULT Initialize(const std::wstring& _fontFilePath);
	HRESULT Render(const std::wstring& _text, const _float2& _position, _fvector _color = XMVectorSet(1.f, 1.f, 1.f, 1.f), _float _rotation = 0.f, const _float2& _origin = _float2(0.f, 0.f), _float _scale = 1.f);

private:
	SpriteBatch*	m_pBatch;
	SpriteFont*		m_pFont;

public:
	static CustomFont* Create(const std::wstring& _fontFilePath);
	virtual void Free() override;
};

END