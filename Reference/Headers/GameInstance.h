#pragma once
#include "InputDevice.h"
#include "RenderManager.h"

BEGIN(Engine)

class ENGINE_DLL GameInstance
{
	DECLARE_SINGLETON(GameInstance)
public:
	GameInstance();
	~GameInstance();

public: /* Device & Context */
	ComPtr<ID3D11Device> GetDevice() const;
	ComPtr<ID3D11DeviceContext> GetDeviceContext() const;
	const D3D11_VIEWPORT& GetViewPort() const;

public:
	void SetMousePos(_int2 vPos) { m_vMousePos = vPos; }
	_int2 GetMousePos() const { return m_vMousePos; }

public:
	HRESULT Initialize(HINSTANCE _hInst, _uint _numLevels, const GRAPHICDESC& _graphicDesc);
	void Update(_float fTimeDelta);
	HRESULT Render();

public: /* GraphicDevice */
	HRESULT RenderBegin(_float4 _clearColor);
	HRESULT RenderEnd();

public: /* TimerManager */
	// Ÿ�̸� Tick�Լ��� ���� ó���� ���� ƽ�� ���� ƽ�� TimeDelta�� ��ȯ�ϴ� �Լ�
	_float		GetTimeDelta(const std::wstring& _timerTag);
	// Ÿ�̸� �±׿� �ش��ϴ� Ÿ�̸Ӹ� ã�� Tick�Լ��� ȣ���ϰ� �ϴ� �Լ�.
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

public:
	void StartScene(_uint nSceneIndex, class Scene* pScene);

private:
	void ChangeScene();
	HRESULT ClearSceneResources();

private: // Engine Data
	_int				m_nCurrentSceneIndex;
	class Scene*		m_pCurrentScene;

	bool				m_bSceneChanged;
	_int				m_nNextSceneIndex;
	class Scene*		m_pNextScene;

private:
	_int2 m_vMousePos;

public:
	static void Release();
};

END

#define GAME		GET_SINGLE(Engine::GameInstance)