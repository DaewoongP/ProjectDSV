#include "InputDevice.h"

USING(Engine)

IMPLEMENT_SINGLETON(InputDevice)

InputDevice::InputDevice()
	: mInputSDK(nullptr)
	, mKeyBoard(nullptr)
	, mMouse(nullptr)
{	
	ZeroMemory(mKeyState, sizeof(mKeyState));
	ZeroMemory(&mPreKeyState, sizeof(mPreKeyState));
	ZeroMemory(&mMouseState, sizeof(DIMOUSESTATE));
	ZeroMemory(&mPreMouseState, sizeof(DIMOUSESTATE));
}

_bool InputDevice::GetDIKeyState(_ubyte _keyID, KEYSTATE _state)
{
	switch (_state)
	{
	case KEY_DOWN:
		return KeyDown(_keyID);
	case KEY_PRESSING:
		return KeyPressing(_keyID);
	case KEY_UP:
		return KeyUp(_keyID);
	default:
		return false;
	}

	return false;
}

_bool InputDevice::GetDIMouseState(MOUSEKEYSTATE _mouseID, KEYSTATE _state)
{
	switch (_state)
	{
	case KEY_DOWN:
		return MouseDown(_mouseID);
	case KEY_PRESSING:
		return MousePressing(_mouseID);
	case KEY_UP:
		return MouseUp(_mouseID);
	default:
		return false;
	}

	return false;
}

_long InputDevice::GetDIMouseMove(MOUSEMOVESTATE _mouseMoveID)
{
	return *(((_long*)&mMouseState) + _mouseMoveID);
}

HRESULT InputDevice::Initialize(HINSTANCE _hInst, HWND _hWnd)
{
	FAILED_CHECK_RETURN(DirectInput8Create(_hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, reinterpret_cast<void**>(mInputSDK.GetAddressOf()), nullptr), E_FAIL);
	FAILED_CHECK_RETURN(mInputSDK->CreateDevice(GUID_SysKeyboard, &mKeyBoard, nullptr), E_FAIL);
	FAILED_CHECK_RETURN(mKeyBoard->SetDataFormat(&c_dfDIKeyboard), E_FAIL);
	FAILED_CHECK_RETURN(mKeyBoard->SetCooperativeLevel(_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE), E_FAIL);
	FAILED_CHECK_RETURN(mKeyBoard->Acquire(), E_FAIL);
	FAILED_CHECK_RETURN(mInputSDK->CreateDevice(GUID_SysMouse, &mMouse, nullptr), E_FAIL);
	FAILED_CHECK_RETURN(mMouse->SetDataFormat(&c_dfDIMouse), E_FAIL);
	FAILED_CHECK_RETURN(mMouse->SetCooperativeLevel(_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE), E_FAIL);
	FAILED_CHECK_RETURN(mMouse->Acquire(), E_FAIL);

	return S_OK;
}

void InputDevice::Tick()
{
	memcpy(mPreKeyState, mKeyState, sizeof(_byte) * MAX_DIK);
	memcpy(&mPreMouseState, &mMouseState, sizeof(DIMOUSESTATE));

	mKeyBoard->GetDeviceState(MAX_DIK, mKeyState);
	mMouse->GetDeviceState(sizeof(mMouseState), &mMouseState);
}

_bool InputDevice::KeyDown(const _ubyte& _key)
{
	if (!(mPreKeyState[_key] & 0x80) && (mKeyState[_key] & 0x80))
		return true;

	return false;
}

_bool InputDevice::KeyPressing(const _ubyte& _key)
{
	if ((mPreKeyState[_key] & 0x80) && (mKeyState[_key] & 0x80))
		return true;

	return false;
}

_bool InputDevice::KeyUp(const _ubyte& _key)
{
	if ((mPreKeyState[_key] & 0x80) && !(mKeyState[_key] & 0x80))
		return true;

	return false;
}

_bool InputDevice::MouseDown(MOUSEKEYSTATE _mouseID)
{
	if (!mPreMouseState.rgbButtons[_mouseID] && mMouseState.rgbButtons[_mouseID])
		return true;

	return false;
}

_bool InputDevice::MousePressing(MOUSEKEYSTATE _mouseID)
{
	if (mPreMouseState.rgbButtons[_mouseID] && mMouseState.rgbButtons[_mouseID])
		return true;

	return false;
}

_bool InputDevice::MouseUp(MOUSEKEYSTATE _mouseID)
{
	if (mPreMouseState.rgbButtons[_mouseID] && !mMouseState.rgbButtons[_mouseID])
		return true;

	return false;
}
