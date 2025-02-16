#include "GraphicDevice.h"

IMPLEMENT_SINGLETON(Engine::GraphicDevice)
USING(Engine)
HRESULT Engine::GraphicDevice::Initialize(HWND _hWnd, GRAPHICDESC::WINMODE _winMode, _uint _winCX, _uint _winCY)
{
	_uint		flag = 0;

#ifdef _DEBUG
	flag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL		featureLV;
	FAILED_CHECK_RETURN_MSG(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, flag, nullptr, 0, D3D11_SDK_VERSION,
		&mDevice, &featureLV, &mDeviceContext), E_FAIL, TEXT("Failed Create Device"));

	FAILED_RETURN(ReadySwapChain(_hWnd, _winMode, _winCX, _winCY), E_FAIL);
	FAILED_RETURN(ReadyBackBufferRenderTargetView(), E_FAIL);
	FAILED_RETURN(ReadyDepthStencilRenderTargetView(_winCX, _winCY), E_FAIL);

	ComPtr<ID3D11RenderTargetView> rtv[1] = {
		mBackBufferRTV.Get(),
	};

	mDeviceContext->OMSetRenderTargets(1, rtv->GetAddressOf(), mDepthStencilView.Get());

	ZeroMemory(&mViewPort, sizeof(D3D11_VIEWPORT));

	mViewPort.TopLeftX = 0.f;
	mViewPort.TopLeftY = 0.f;
	mViewPort.Width = _float(_winCX);
	mViewPort.Height = _float(_winCY);
	mViewPort.MinDepth = 0.f;
	mViewPort.MaxDepth = 1.f;

	mDeviceContext->RSSetViewports(1, &mViewPort);

	return S_OK;
}

HRESULT GraphicDevice::RenderBegin(_float4 _clearColor)
{
	mDeviceContext->OMSetRenderTargets(1, mBackBufferRTV.GetAddressOf(), mDepthStencilView.Get());
	ClearBackBuffer(_clearColor);
	ClearDepthStencilView();

	return S_OK;
}

HRESULT GraphicDevice::RenderEnd()
{
	Present();

	return S_OK;
}

HRESULT Engine::GraphicDevice::ClearBackBuffer(_float4 _clearColor)
{
	NULL_CHECK_RETURN_MSG(mDeviceContext, E_FAIL, TEXT("DeviceContext NULL"));

	mDeviceContext->ClearRenderTargetView(mBackBufferRTV.Get(), (_float*)&_clearColor);

	return S_OK;
}

HRESULT Engine::GraphicDevice::ClearDepthStencilView()
{
	NULL_CHECK_RETURN_MSG(mDeviceContext, E_FAIL, TEXT("DeviceContext NULL"));

	mDeviceContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);

	return S_OK;
}

HRESULT Engine::GraphicDevice::Present()
{
	NULL_CHECK_RETURN_MSG(mSwapChain, E_FAIL, TEXT("SwapChain NULL"));

	FAILED_CHECK_RETURN_MSG(mSwapChain->Present(0, 0), E_FAIL, TEXT("Failed Present"));

	return S_OK;
}

HRESULT Engine::GraphicDevice::ReadySwapChain(HWND _hWnd, GRAPHICDESC::WINMODE _winMode, _uint _winCX, _uint _winCY)
{
	ComPtr<IDXGIDevice> device;
	mDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(device.GetAddressOf()));

	ComPtr<IDXGIAdapter> adapter;
	device->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(adapter.GetAddressOf()));

	ComPtr<IDXGIFactory> factory;
	adapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(factory.GetAddressOf()));

	DXGI_SWAP_CHAIN_DESC	swapChain;
	ZeroMemory(&swapChain, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChain.BufferDesc.Width = _winCX;
	swapChain.BufferDesc.Height = _winCY;
	swapChain.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChain.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChain.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChain.BufferCount = 1;

	swapChain.BufferDesc.RefreshRate.Numerator = 60;
	swapChain.BufferDesc.RefreshRate.Denominator = 1;
	swapChain.SampleDesc.Quality = 0;
	swapChain.SampleDesc.Count = 1;

	swapChain.OutputWindow = _hWnd;
	swapChain.Windowed = static_cast<_bool>(_winMode);
	swapChain.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	FAILED_CHECK_RETURN_MSG(factory->CreateSwapChain(mDevice.Get(), &swapChain, mSwapChain.GetAddressOf()), E_FAIL, TEXT("Failed CreateSwapChain"));

	return S_OK;
}

HRESULT Engine::GraphicDevice::ReadyBackBufferRenderTargetView()
{
	NULL_CHECK_RETURN_MSG(mDevice, E_FAIL, TEXT("Device NULL"));

	ComPtr<ID3D11Texture2D> BackBufferTexture = nullptr;

	FAILED_CHECK_RETURN_MSG(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(BackBufferTexture.GetAddressOf())), E_FAIL,
		TEXT("ailed GetBuffer"));

	FAILED_CHECK_RETURN_MSG(mDevice->CreateRenderTargetView(BackBufferTexture.Get(), nullptr, mBackBufferRTV.GetAddressOf()), E_FAIL,
		TEXT("Failed Create RenderTarget"));

	return S_OK;
}

HRESULT Engine::GraphicDevice::ReadyDepthStencilRenderTargetView(_uint _winCX, _uint _winCY)
{
	NULL_CHECK_RETURN_MSG(mDevice, E_FAIL, TEXT("Device NULL"));

	ComPtr<ID3D11Texture2D> DepthStencilTexture = nullptr;
	D3D11_TEXTURE2D_DESC	TextureDesc;
	ZeroMemory(&TextureDesc, sizeof(D3D11_TEXTURE2D_DESC));

	TextureDesc.Width = _winCX;
	TextureDesc.Height = _winCY;
	TextureDesc.MipLevels = 1;
	TextureDesc.ArraySize = 1;
	TextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	TextureDesc.SampleDesc.Quality = 0;
	TextureDesc.SampleDesc.Count = 1;
	TextureDesc.Usage = D3D11_USAGE_DEFAULT;

	TextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	TextureDesc.CPUAccessFlags = 0;
	TextureDesc.MiscFlags = 0;

	FAILED_CHECK_RETURN_MSG(mDevice->CreateTexture2D(&TextureDesc, nullptr, DepthStencilTexture.GetAddressOf()), E_FAIL, TEXT("Failed Create Texture2D"));
	FAILED_CHECK_RETURN_MSG(mDevice->CreateDepthStencilView(DepthStencilTexture.Get(), nullptr, mDepthStencilView.GetAddressOf()), E_FAIL,
		TEXT("Failed CreateDepthStencilView"));

	return S_OK;
}
