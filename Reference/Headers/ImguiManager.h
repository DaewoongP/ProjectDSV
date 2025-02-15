#pragma once

#include "Engine_Defines.h"

BEGIN(Engine)
class ImguiManager
{
	DECLARE_SINGLETON(ImguiManager)
public:
	ImguiManager() = default;
	~ImguiManager();

public:
	HRESULT Initialize(HWND hWnd, ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _deviceContext);
	void Begin();
	void End();

private:
	ComPtr<ID3D11Device> mDevice;
	ComPtr<ID3D11DeviceContext> mDeviceContext;
};

END

#define GUI		GET_SINGLE(Engine::ImguiManager)