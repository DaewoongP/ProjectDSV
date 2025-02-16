#pragma once
#include "Engine_Defines.h"

BEGIN(Engine)

class InputDevice
{
	DECLARE_SINGLETON(InputDevice)
public:
	enum MOUSEKEYSTATE { DIMK_LBUTTON, DIMK_RBUTTON, DIMK_WHEEL, DIMK_END };
	enum MOUSEMOVESTATE { DIMM_X, DIMM_Y, DIMM_WHEEL, DIMM_END };
	enum KEYSTATE { KEY_DOWN, KEY_PRESSING, KEY_UP, KEY_END };

public:
	InputDevice();
	~InputDevice() = default;

public:
	_bool		GetDIKeyState(_ubyte _keyID, KEYSTATE _state = KEY_PRESSING);
	_bool		GetDIMouseState(MOUSEKEYSTATE _mouseID, KEYSTATE _state = KEY_PRESSING);
	_long		GetDIMouseMove(MOUSEMOVESTATE _mouseMoveID);

public:
	HRESULT		Initialize(HINSTANCE _hInst, HWND _hWnd);
	void		Update();

private:
	_bool    KeyDown(const _ubyte& _key);
	_bool    KeyPressing(const _ubyte& _key);
	_bool    KeyUp(const _ubyte& _key);

	_bool    MouseDown(MOUSEKEYSTATE _mouseID);
	_bool    MousePressing(MOUSEKEYSTATE _mouseID);
	_bool    MouseUp(MOUSEKEYSTATE _mouseID);

private:
	// 牢遣 按眉 积己侩 哪按眉
	ComPtr<IDirectInput8>			mInputSDK;
	ComPtr<IDirectInputDevice8>		mKeyBoard;
	ComPtr<IDirectInputDevice8>		mMouse;

private:
	_byte                   mKeyState[MAX_DIK];
	_byte                   mPreKeyState[MAX_DIK];
	DIMOUSESTATE            mMouseState;
	DIMOUSESTATE            mPreMouseState;
};

END

#define INPUT		GET_SINGLE(Engine::InputDevice)