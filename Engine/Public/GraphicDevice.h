#pragma once
#include "Engine_Defines.h"

BEGIN(Engine)

class GraphicDevice
{
	DECLARE_SINGLETON(GraphicDevice)
public:
	GraphicDevice() = default;
	~GraphicDevice() = default;

public:
	ComPtr<ID3D11Device> GetDevice() const { return mDevice; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() const { return mDeviceContext; }

public:
	HRESULT Initialize(HWND _hWnd, GRAPHICDESC::WINMODE _winMode,
		_uint _winCX, _uint _winCY, _Inout_ ComPtr<ID3D11Device>& _device,
		_Inout_ ComPtr<ID3D11DeviceContext>& _deviceContext);
	HRESULT RenderBegin(_float4 _clearColor);
	HRESULT RenderEnd();

private:
	ComPtr<ID3D11Device>				mDevice;
	ComPtr<ID3D11DeviceContext>			mDeviceContext;
	ComPtr<IDXGISwapChain>				mSwapChain;
	ComPtr<ID3D11RenderTargetView>		mBackBufferRTV;
	ComPtr<ID3D11DepthStencilView>		mDepthStencilView;

private:
	HRESULT ClearBackBuffer(_float4 _clearColor);
	HRESULT ClearDepthStencilView();
	HRESULT Present();

private:
	HRESULT ReadySwapChain(HWND hWnd, GRAPHICDESC::WINMODE _winMode, _uint _winCX, _uint _winCY);
	HRESULT ReadyBackBufferRenderTargetView();
	HRESULT ReadyDepthStencilRenderTargetView(_uint _winCX, _uint _winCY);
};

END

#define GRAPHIC		GET_SINGLE(Engine::GraphicDevice)