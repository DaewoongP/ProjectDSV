#include "CustomFont.h"

USING(Engine)

HRESULT CustomFont::Initialize(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _deviceContext, const std::wstring& _fontFilePath)
{
	mDevice = _device;
	mDeviceContext = _deviceContext;
	
	mBatch = std::make_unique<SpriteBatch>(mDeviceContext.Get());
	mFont = std::make_unique<SpriteFont>(mDevice.Get(), _fontFilePath.c_str());

	return S_OK;
}

HRESULT CustomFont::Render(const std::wstring& _text, const _float2& _position, _fvector _color, _float _rotation, const _float2& _origin, _float _scale)
{
	mDeviceContext->GSSetShader(nullptr, nullptr, 0);

	mBatch->Begin();

	mFont->DrawString(mBatch.get(), _text.c_str(), _position, _color, _rotation, _origin, _scale);

	mBatch->End();

	return S_OK;
}

std::shared_ptr<CustomFont> CustomFont::Create(ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _deviceContext, const std::wstring& _fontFilePath)
{
	auto instance = std::make_shared<CustomFont>();
	FAILED_CHECK_RETURN_MSG(instance->Initialize(_device, _deviceContext, _fontFilePath), nullptr, TEXT("Failed"));
	return instance;
}
