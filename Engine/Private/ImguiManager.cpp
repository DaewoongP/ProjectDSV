#include "ImguiManager.h"
using namespace Engine;

IMPLEMENT_SINGLETON(ImguiManager)

ImguiManager::~ImguiManager()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

HRESULT ImguiManager::Initialize(HWND hWnd, ComPtr<ID3D11Device> _device, ComPtr<ID3D11DeviceContext> _deviceContext)
{
	mDevice = _device;
	mDeviceContext = _deviceContext;
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();
	// Setup Platform/Renderer backends
	if (!ImGui_ImplWin32_Init(hWnd))
	{
		DISPLAY_ERROR(TEXT("Failed ImGui_ImplWin32_Init"));
		__debugbreak();
		return E_FAIL;
	}

	
	if (!ImGui_ImplDX11_Init(mDevice.Get(), mDeviceContext.Get()))
	{
		DISPLAY_ERROR(TEXT("Failed ImGui_ImplDX11_Init"));
		__debugbreak();
		return E_FAIL;
	}

	return S_OK;
}

void ImguiManager::Begin()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	//ImGui::ShowDemoWindow();
}

void ImguiManager::End()
{
	// Rendering
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}