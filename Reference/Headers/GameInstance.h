#pragma once
#include "InputDevice.h"
#include "RenderManager.h"

BEGIN(Engine)

class ENGINE_DLL GameInstance
{
	DECLARE_SINGLETON(GameInstance)
public:
	GameInstance() = default;
	~GameInstance() = default;

public: /* Device & Context */
	ComPtr<ID3D11Device> GetDevice() const;
	ComPtr<ID3D11DeviceContext> GetDeviceContext() const;

public:
	HRESULT Initialize(HINSTANCE _hInst, _uint _numLevels, const GRAPHICDESC& _graphicDesc, _Inout_ ComPtr<ID3D11Device>& _device, _Inout_ ComPtr<ID3D11DeviceContext>& _deviceContext);
	void Tick(_float _timeDelta);
	HRESULT Render();

public: /* GraphicDevice */
	HRESULT RenderBegin(_float4 _clearColor);
	HRESULT RenderEnd();

public: /* TimerManager */
	// 타이머 Tick함수에 따라 처리된 이전 틱과 현재 틱의 TimeDelta를 반환하는 함수
	_float		GetTimeDelta(const std::wstring& _timerTag);
	// 타이머 태그에 해당하는 타이머를 찾아 Tick함수를 호출하게 하는 함수.
	void		TickTimeDelta(const std::wstring& _timerTag);
	HRESULT		AddTimer(const std::wstring& _timerTag);
	void		Invoke(std::function<void(void*)> _func, void* _arg, _float _callTime, _bool _loop = false);

public: /* InputDevice */
	_bool		GetDIKeyState(_ubyte _keyID, InputDevice::KEYSTATE _state = InputDevice::KEY_PRESSING);
	_bool		GetDIMouseState(InputDevice::MOUSEKEYSTATE _mouseID, InputDevice::KEYSTATE _state = InputDevice::KEY_PRESSING);
	_long		GetDIMouseMove(InputDevice::MOUSEMOVESTATE _mouseMoveID);

public: /* FontManager */
	HRESULT AddFont(const std::wstring& _fontTag, const std::wstring& _fontFilePath);
	HRESULT RenderFont(const std::wstring& _fontTag, const std::wstring& _text, const _float2& _position, _fvector _color = XMVectorSet(1.f, 1.f, 1.f, 1.f), _float _rotation = 0.f, const _float2& _origin = _float2(0.f, 0.f), _float _scale = 1.f);

public: /* ImguiManager */
	void ImguiBegin();
	void ImguiEnd();

public: /* RenderManager */
	void AddRenderGroup(RenderManager::RenderType _renderType, Component* _component);

private:
	HRESULT ClearLevelResources(_uint _preLevelIndex);

public:
	static void Release();
};

END

#define GAME		GET_SINGLE(Engine::GameInstance)