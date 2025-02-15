#pragma once
#include "Engine_Defines.h"

BEGIN(Engine)

class CustomFont
{
public:
	HRESULT Initialize(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _deviceContext, const std::wstring& _fontFilePath);
	HRESULT Render(const std::wstring& _text, const _float2& _position, _fvector _color = XMVectorSet(1.f, 1.f, 1.f, 1.f), _float _rotation = 0.f, const _float2& _origin = _float2(0.f, 0.f), _float _scale = 1.f);

private:
	ComPtr<ID3D11Device>			mDevice;
	ComPtr<ID3D11DeviceContext>		mDeviceContext;
	std::unique_ptr<SpriteBatch>	mBatch;
	std::unique_ptr<SpriteFont>		mFont;

public:
	static std::shared_ptr<CustomFont> Create(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _deviceContext, const std::wstring& _fontFilePath);
};

END