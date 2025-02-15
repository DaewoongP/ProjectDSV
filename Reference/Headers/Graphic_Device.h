#pragma once
#include "Engine_Defines.h"

BEGIN(Engine)

class Graphic_Device
{
	DECLARE_SINGLETON(Graphic_Device)
public:
	Graphic_Device();
	~Graphic_Device();

public:
	HRESULT Initialize(HWND _hWnd, GRAPHICDESC::WINMODE _WinMode,
		_uint _WinCX, _uint _WinCY, _Inout_ ComPtr<ID3D11Device>& _Device,
		_Inout_ ComPtr<ID3D11DeviceContext>& _DeviceContext);
	HRESULT ClearBackBuffer(Engine::_float4 _ClearColor);
	HRESULT ClearDepthStencilView();
	HRESULT Present();

private:
	ComPtr<ID3D11Device>				mDevice;
	ComPtr<ID3D11DeviceContext>			mDeviceContext;
	ComPtr<IDXGISwapChain>				mSwapChain;
	ComPtr<ID3D11RenderTargetView>		mBackBufferRTV;
	ComPtr<ID3D11DepthStencilView>		mDepthStencilView;

private:
	HRESULT ReadySwapChain(HWND hWnd, GRAPHICDESC::WINMODE _WinMode, _uint _WinCX, _uint _WinCY);
	HRESULT ReadyBackBufferRenderTargetView();
	HRESULT ReadyDepthStencilRenderTargetView(_uint _WinCX, _uint _WinCY);
};

END

#define GRAPHIC		GET_SINGLE(Graphic_Device)